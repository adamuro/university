#include "traceroute.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
      fprintf(stderr, "proper usage: ./traceroute <ip_address>\n"); 
      return EXIT_FAILURE;
  }

  char* dest_ip = argv[1];

  int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sockfd < 0) {
    fprintf(stderr, "socket error: %s\n", strerror(errno)); 
    return EXIT_FAILURE;
  }

  for (int ttl = 1; ttl <= MAX_TTL; ttl++)
  {
    ssize_t packets_sent = icmp_send(sockfd, dest_ip, ttl);
    if (packets_sent < 0) {
      return EXIT_FAILURE;
    }
  
    int dest_reached = icmp_receive(sockfd, dest_ip, ttl);
    if (dest_reached < 0) {
      return EXIT_FAILURE;
    }

    if (dest_reached)
      return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
