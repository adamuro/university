#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "icmp_send.h"
#include "icmp_receive.h"

#define MAX_TTL 20

int main(int argc, char *argv[])
{
  if (argc != 2) {
      fprintf(stderr, "No destination IP address specified\n"); 
      return EXIT_FAILURE;
  }

  char* dest_ip = argv[1];

  int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sockfd < 0) {
    fprintf(stderr, "socket error: %s\n", strerror(errno)); 
    return EXIT_FAILURE;
  }

  for (int ttl = 1; ttl < MAX_TTL; ttl++)
  {
    int packets_sent = icmp_send(sockfd, dest_ip, ttl);
    if (packets_sent < 0) {
      fprintf(stderr, "icmp_send error: %s\n", strerror(errno)); 
      return EXIT_FAILURE;
    }
  
    int dest_reached = icmp_receive(sockfd, dest_ip, ttl);
    if (dest_reached < 0) {
      fprintf(stderr, "icmp_receive error: %s\n", strerror(errno)); 
      return EXIT_FAILURE;
    }

    if (dest_reached)
      return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
