#include "icmp_receive.h"

void print_as_bytes(unsigned char* buff, ssize_t length)
{
  for (ssize_t i = 0; i < length; i++, buff++)
    printf("%.2x ", *buff);	
}

struct icmp_packet
{
  struct icmp* header;
  double rtt;
  char sender_ip[20];
};

double calc_avg_rtt(struct icmp_packet* packets)
{
  double total_rtt = 0.0;
  for (int i = 0; i < MAX_PACKETS; i++) {
    struct icmp_packet packet = packets[i];
    total_rtt += packet.rtt;
  }

  return total_rtt / (double)MAX_PACKETS;
}

void print_packets_info(struct icmp_packet* packets, ssize_t n_packets)
{
  char prev[20] = "";

  for (int i = 0; i < n_packets; i++) {
    struct icmp_packet packet = packets[i];

    if (strcmp(packet.sender_ip, prev)) {
      printf("%s ", packet.sender_ip);
      memcpy(prev, packet.sender_ip, 20);
    }
  }

  if (n_packets == MAX_PACKETS) {
    double avg_rtt = calc_avg_rtt(packets);
    printf("%lf\n", avg_rtt);
  } else
    printf("???\n");
}


int icmp_receive(int sockfd, char* dest_ip, int ttl)
{
  fd_set descriptors;
  FD_ZERO(&descriptors);
  FD_SET(sockfd, &descriptors);

  struct timeval tv;
  tv.tv_sec = MAX_RECV_TIME;
  tv.tv_usec = 0;

  int n_packets = 0;
  struct icmp_packet packets[3];

  clock_t start_time = clock();

  while (n_packets < MAX_PACKETS) {
    int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
    if (ready < 0) {
      fprintf(stderr, "select error: %s\n", strerror(errno)); 
      return -1;
    }

    if (ready == 0) {
      if (n_packets == 0) {
        printf("*\n");
        return 0;
      }

      printf("%d. ", ttl);
      print_packets_info(packets, n_packets);

      struct icmp_packet first_packet = packets[0];
      if (strcmp(first_packet.sender_ip, dest_ip) == 0)
        return 1;
      else
        return 0;
    }

    /*
      1. Wait for packet +
      2. If waiting time was exceeded:
        2.1. If any packets were received - Return if sender ip is destination ip (???) +
        2.2. Return false (*) +
      3. If packet has different id (pid) or seq (ttl) ignore it
      4. Add packet to array of received packets and increment packets count
      5. Get all senders ips and calculate average waiting time 
      6. Print senders ips and average waiting time
    */
		
    struct sockaddr_in sender;	
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
    if (packet_len < 0) {
      fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
      return -1;
    }

    time_t rec_time = clock();
    double rtt = 1000.0 * ((double)(rec_time - start_time) / CLOCKS_PER_SEC);

    char sender_ip[20]; 
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip));

    struct ip* ip_header = (struct ip*) buffer;
    ssize_t	ip_header_len = 4 * ip_header->ip_hl;
    u_int8_t* icmp_packet = buffer + ip_header_len;
    struct icmp* icmp_header = (struct icmp*) icmp_packet;
    int packet_id = icmp_header->icmp_hun.ih_idseq.icd_id;
    int packet_seq = icmp_header->icmp_hun.ih_idseq.icd_seq;

    if (strcmp(dest_ip, sender_ip) != 0 || packet_id != getpid() || packet_seq != ttl)
      continue;

    struct icmp_packet packet;
    packet.header = icmp_header;
    packet.rtt = rtt;
    memcpy(packet.sender_ip, sender_ip, 20);

    memcpy(&packets[n_packets], &packet, sizeof(packet));
    n_packets++;

    // printf("Received IP packet with ICMP content from: %s\n", sender_ip);
    // printf("IP header: "); 
    // print_as_bytes (buffer, ip_header_len);
    // printf("\n");

    // printf("IP data:   ");
    // print_as_bytes (buffer + ip_header_len, packet_len - ip_header_len);
    // printf("\n");

    // printf("ICMP data:\n");
    // printf("Type: %d\n", icmp_header->icmp_type);
    // printf("Code: %d\n", icmp_header->icmp_code);
    // printf("ID: %d\n", icmp_header->icmp_hun.ih_idseq.icd_id);
    // printf("Seq: %d\n", icmp_header->icmp_hun.ih_idseq.icd_seq);
    // printf("Pid: %d\n", getpid());
    // printf("\n");
  }

  printf("%d. ", ttl);
  print_packets_info(packets, n_packets);

  struct icmp_packet first_packet = packets[0];
  if (strcmp(first_packet.sender_ip, dest_ip) == 0)
    return 1;
  else
    return 0;
}
