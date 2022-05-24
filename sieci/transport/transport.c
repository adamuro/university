#include "sliding_window.h"

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "Usage: transport <ip> <port> <file> <size>\n");
    return EXIT_FAILURE;
  }

  const char* ip   = argv[1];
  const char* file = argv[3];
  const int   port = atoi(argv[2]);
  const int   size = atoi(argv[4]);

  if (port <= 0) {
    fprintf(stderr, "Invalid port\n");
    return EXIT_FAILURE;
  }

  if (size <= 0) {
    fprintf(stderr, "Invalid size\n");
    return EXIT_FAILURE;
  }

  int filefd = creat(file, 00644);
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (filefd < 0) {
    fprintf(stderr, "creat error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  if (sockfd < 0) {
    fprintf(stderr, "socket error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
    fprintf(stderr, "Invalid ip address\n");
    return EXIT_FAILURE;
  }

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    fprintf(stderr, "connect error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  struct sliding_window swin;
  swin_init(&swin, size);

  while(swin.seg_wrtn != swin.seg_file) {
    if (swin_reqall(sockfd, swin) < 0)
      return EXIT_FAILURE;
    if (swin_recvall(sockfd, &swin) < 0)
      return EXIT_FAILURE;
    if (swin_write(filefd, &swin) < 0)
      return EXIT_FAILURE;
  }

  close(filefd);
  return 0;
}
