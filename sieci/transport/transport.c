#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "Usage: transport <ip> <port> <file> <size>\n");
    return EXIT_FAILURE;
  }
  
  struct in_addr ip;
  const int port = atoi(argv[2]);
  const int size = atoi(argv[4]);
  const char* file = argv[3];

  if (inet_aton(argv[1], &ip) <= 0) {
    fprintf(stderr, "Invalid ip address\n");
    return EXIT_FAILURE;
  }

  if (port <= 0) {
    fprintf(stderr, "Invalid port\n");
    return EXIT_FAILURE;
  }

  if (size <= 0) {
    fprintf(stderr, "Invalid size\n");
    return EXIT_FAILURE;
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htonl(port);
  addr.sin_addr = ip;
  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    fprintf(stderr, "connect error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  char send_buf[64];
  int send_bufsize = sprintf(send_buf, "GET %d %d\n", 0, 10);
  send(sockfd, send_buf, send_bufsize, 0);

  struct timeval tv;
  tv.tv_sec  = 2;
  tv.tv_usec = 0;

  fd_set descriptors;
  FD_ZERO(&descriptors);
  FD_SET(sockfd, &descriptors);

  int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
  if (ready < 0) {
    fprintf(stderr, "select error: %s\n", strerror(errno)); 
    return EXIT_FAILURE;
  }

  if (ready == 0) {
    fprintf(stderr, "no response\n");
    return -1;
  }

  char recv_buf[2048];
  recv(sockfd, recv_buf, sizeof(recv_buf), 0);
  printf("%c\n", recv_buf[0]);

  uint32_t start, len;
  sscanf(recv_buf, "DATA %u %u\n", &start, &len);

  return 0;
}
