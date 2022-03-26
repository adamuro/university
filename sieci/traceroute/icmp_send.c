#include "icmp_send.h"

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
  u_int32_t sum;
  const u_int16_t* ptr = buff;
  assert (length % 2 == 0);
  for (sum = 0; length > 0; length -= 2)
    sum += *ptr++;
  sum = (sum >> 16) + (sum & 0xffff);
  return (u_int16_t)(~(sum + (sum >> 16)));
}

u_int16_t icmp_send(int sockfd, char* dest_ip, int ttl)
{
  pid_t pid = getpid();
  struct icmp header;
  header.icmp_type = ICMP_ECHO;
  header.icmp_code = 0;
  header.icmp_hun.ih_idseq.icd_id = pid;
  header.icmp_hun.ih_idseq.icd_seq = ttl;
  header.icmp_cksum = 0;
  header.icmp_cksum = compute_icmp_checksum((uint16_t*) &header, sizeof(header));

  struct sockaddr_in recipent;
  bzero(&recipent, sizeof(recipent));
  recipent.sin_family = AF_INET;
  inet_pton(AF_INET, dest_ip, &recipent.sin_addr);

  if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int))) {
    fprintf(stderr, "select error: %s\n", strerror(errno)); 
    return EXIT_FAILURE;
  }

  int packets_sent = 0;
  for (int i = 0; i < PACKETS; i++) {
    ssize_t bytes_sent = sendto(sockfd, &header, sizeof(header), 0, (struct sockaddr*) &recipent, sizeof(recipent));
    packets_sent++;
    if (bytes_sent < 0) {
      fprintf(stderr, "select error: %s\n", strerror(errno)); 
      return EXIT_FAILURE;
    }
  }

  return packets_sent;
}