#include "icmp_receive.h"

char** alloc_ip_addrs()
{
  char** ip_addrs;
  ip_addrs = malloc(PACKETS_SENT * sizeof(char*));
  for (int i = 0; i < PACKETS_SENT; i++)
    ip_addrs[i] = malloc(20 * sizeof(char));
  return ip_addrs;
}

void print_ip_addrs(char** ip_addrs, ssize_t n)
{
  for (int i = 0; i < n; i++)
    printf("%s ", ip_addrs[i]);
}

void print_noresp(u_int16_t ttl)
{
  printf("%d. *\n", ttl);
}

void print_packetloss(u_int16_t ttl, char** ip_addrs, ssize_t n)
{
  printf("%d. ", ttl);
  print_ip_addrs(ip_addrs, n);
  printf("???\n");
}

void print_allrecvd(uint16_t ttl, char** ip_addrs, ssize_t n, u_int32_t rtt)
{
  printf("%d. ", ttl);
  print_ip_addrs(ip_addrs, n);
  printf("%dms\n", rtt);
}

u_int8_t recvd_from(char** ip_addrs, ssize_t n, char* ip)
{
  for (int i = 0; i < n; i++)
    if (!strcmp(ip_addrs[i], ip))
      return 1;
  return 0;
}

u_int32_t calc_rtt(struct timeval* sent)
{
  struct timeval recvd, rtt;
  gettimeofday(&recvd, NULL);
  timersub(&recvd, sent, &rtt);
  return rtt.tv_sec * SEC_TO_MS + rtt.tv_usec / MS_TO_MICROSEC;
}

ssize_t ip_header_len(struct ip* ip_header)
{
  return 4 * ip_header->ip_hl;
}

int16_t icmp_id_seq(u_int8_t* buffer, uint16_t* id, uint16_t* seq)
{
  struct ip* ip_header     = (struct ip*) buffer;
  struct icmp* icmp_header = (struct icmp*) (buffer + ip_header_len(ip_header));

  if (icmp_header->icmp_type != ICMP_ECHOREPLY && icmp_header->icmp_type != ICMP_TIME_EXCEEDED)
    return -1;

  /* ICMP packets with type ICMP_TIME_EXCEEDED contain original IP header and 8 bytes of original IP packet */
  if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED)
    icmp_header = (void*)icmp_header + ip_header_len(ip_header) + 8;

  *id  = icmp_header->icmp_id;
  *seq = icmp_header->icmp_seq;

  return icmp_header->icmp_type;
}

int icmp_receive(int sockfd, char* dest_ip, int ttl)
{
  fd_set descriptors;
  FD_ZERO(&descriptors);
  FD_SET(sockfd, &descriptors);

  struct timeval tv;
  tv.tv_sec  = MAX_RECV_TIME;
  tv.tv_usec = 0;

  ssize_t packets_recvd = 0;
  ssize_t ip_addrs_size = 0;
  char**  ip_addrs      = alloc_ip_addrs();

  u_int32_t total_rtt = 0;
  struct timeval sent_time;
  gettimeofday(&sent_time, NULL);

  while (packets_recvd < PACKETS_SENT) {
    int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
    if (ready < 0) {
      fprintf(stderr, "select error: %s\n", strerror(errno)); 
      return -1;
    }

    if (!ready && !packets_recvd) {
      print_noresp(ttl);
      return 0;
    }

    if (!ready) {
      print_packetloss(ttl, ip_addrs, ip_addrs_size);
      return recvd_from(ip_addrs, ip_addrs_size, dest_ip);
    }
		
    struct sockaddr_in sender;	
    char               sender_ip[20]; 
    socklen_t          sender_len = sizeof(sender);
    u_int8_t           buffer[IP_MAXPACKET];
    u_int16_t          id, seq;

    ssize_t packet_len = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
    if (packet_len < 0) {
      fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
      return -1;
    }

    const char* dst = inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip));
    if (dst == NULL) {
      fprintf(stderr, "inet_ntop error: %s\n", strerror(errno)); 
      return -1;
    }

    int16_t icmp_type = icmp_id_seq(buffer, &id, &seq);
    if (icmp_type < 0)
      continue;

    pid_t pid = getpid();
    if (id != pid || seq != ttl)
      continue;

    if (!recvd_from(ip_addrs, ip_addrs_size, sender_ip))
      strcpy(ip_addrs[ip_addrs_size++], sender_ip);

    total_rtt += calc_rtt(&sent_time);
    packets_recvd++;
  }

  u_int32_t avg_rtt = total_rtt / PACKETS_SENT;
  print_allrecvd(ttl, ip_addrs, ip_addrs_size, avg_rtt);
  return recvd_from(ip_addrs, ip_addrs_size, dest_ip);
}
