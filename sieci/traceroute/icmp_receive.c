#include "icmp_receive.h"

/* TODO:
 * Don't use auxillary struct, store and print ips after receiving responses instead
 */

void print_as_bytes(unsigned char* buff, ssize_t length)
{
  for (ssize_t i = 0; i < length; i++, buff++)
    printf("%.2x ", *buff);	
}

struct icmp_packet
{
  struct icmp* header;
  char sender_ip[20];
};

int calc_rtt(struct timeval* start_time)
{
  struct timeval recv_time, diff_time;
  gettimeofday(&recv_time, NULL);
  timersub(&recv_time, start_time, &diff_time);
  return (diff_time.tv_sec * 1000 + diff_time.tv_usec / 1000) / MAX_PACKETS;
}

void print_packets_info(struct icmp_packet* packets, ssize_t n_packets)
{
  char ip_addrs[n_packets][20];
  int n_ip_addrs = 0;

  for (int i = 0; i < n_packets; i++) {
    struct icmp_packet packet = packets[i];
    int is_new = 1;

    for (int j = 0; j < n_ip_addrs; j++)
      if (strcmp(packet.sender_ip, ip_addrs[j]) == 0)
        is_new = 0;

    if (is_new) {
      printf("%s ", packet.sender_ip);
      strcpy(ip_addrs[n_ip_addrs], packet.sender_ip);
      n_ip_addrs++;
    }
  }
}


int icmp_receive(int sockfd, char* dest_ip, int ttl)
{
  fd_set descriptors;
  FD_ZERO(&descriptors);
  FD_SET(sockfd, &descriptors);

  struct timeval tv;
  tv.tv_sec = MAX_RECV_TIME;
  tv.tv_usec = 0;

  ssize_t n_packets = 0;
  struct icmp_packet packets[MAX_PACKETS];

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  while (n_packets < MAX_PACKETS) {
    int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
    if (ready < 0) {
      fprintf(stderr, "select error: %s\n", strerror(errno)); 
      return -1;
    }

    if (ready == 0) {
      if (n_packets == 0) {
        printf("%d. *\n", ttl);
        return 0;
      }

      printf("%d. ", ttl);
      print_packets_info(packets, n_packets);
      printf("???\n");

      struct icmp_packet first_packet = packets[0];
      return strcmp(first_packet.sender_ip, dest_ip) ? 0 : 1;
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

    ssize_t packet_len = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
    if (packet_len < 0) {
      fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
      return -1;
    }


    char sender_ip[20]; 
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip));

    int packet_id, packet_seq;
    struct ip* ip_header = (struct ip*) buffer;
    ssize_t	ip_header_len = 4 * ip_header->ip_hl;
    u_int8_t* icmp_packet = buffer + ip_header_len;
    struct icmp* icmp_header = (struct icmp*) icmp_packet;
    if (icmp_header->icmp_type == ICMP_ECHOREPLY) {
      packet_id = icmp_header->icmp_hun.ih_idseq.icd_id;
      packet_seq = icmp_header->icmp_hun.ih_idseq.icd_seq;
    } else if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED) {
      icmp_header = (void*)icmp_header + 8 + ip_header_len;
      packet_id = icmp_header->icmp_hun.ih_idseq.icd_id;
      packet_seq = icmp_header->icmp_hun.ih_idseq.icd_seq;
    } else {
      return -1;
    }

    if (packet_id != getpid() || packet_seq != ttl) {
      continue;
    }

    struct icmp_packet packet;
    packet.header = icmp_header;
    strcpy(packet.sender_ip, sender_ip);

    memcpy(&packets[n_packets], &packet, sizeof(packet));
    n_packets++;
  }

  int rtt = calc_rtt(&start_time);

  printf("%d. ", ttl);
  print_packets_info(packets, n_packets);
  printf("%dms\n", rtt);

  struct icmp_packet first_packet = packets[0];
  if (strcmp(first_packet.sender_ip, dest_ip) == 0)
    return 1;
  else
    return 0;
}
