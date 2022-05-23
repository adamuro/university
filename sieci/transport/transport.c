#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#define WINDOW_SIZE 1000
#define SEGMENT_SIZE 1000
#define WAIT_TIME_SEC 0
#define WAIT_TIME_USEC 300000

#define DEBUG 0

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "Usage: transport <ip> <port> <file> <size>\n");
    return EXIT_FAILURE;
  }

  /* parse args */
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

  /* open file and socket, connect to server */
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

  /* prepare window */
  int segments_needed = size / SEGMENT_SIZE + (size % SEGMENT_SIZE != 0);
  int segments_written = 0;
  char segments[WINDOW_SIZE][SEGMENT_SIZE];
  u_int8_t segments_recvd[WINDOW_SIZE];
  bzero(segments_recvd, sizeof(segments_recvd));

  while(segments_written != segments_needed) {
    /* request segments within window that have not beed received yet */
    for (int i = segments_written; i < segments_needed && i < segments_written + WINDOW_SIZE; i++) {
      if (segments_recvd[i - segments_written]) continue;

      char send_buf[64];
      int segment_start = i * SEGMENT_SIZE;
      int segment_len = (i != segments_needed - 1) ? SEGMENT_SIZE : size % SEGMENT_SIZE;
      int send_bufsize = sprintf(send_buf, "GET %d %d\n", segment_start, segment_len);
      
      if (DEBUG)
        printf("%s", send_buf);

      if(send(sockfd, send_buf, send_bufsize, 0) < 0) {
        fprintf(stderr, "send error: %s\n", strerror(errno));
        return EXIT_FAILURE;
      }
    }

    /* prepare select */
    struct timeval tv;
    tv.tv_sec  = WAIT_TIME_SEC;
    tv.tv_usec = WAIT_TIME_USEC;

    fd_set descriptors;
    FD_ZERO(&descriptors);
    FD_SET(sockfd, &descriptors);

    /* wait for segments */
    for (;;) {
      int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
      if (ready < 0) {
        fprintf(stderr, "select error: %s\n", strerror(errno)); 
        return EXIT_FAILURE;
      }

      if (!ready) break;

      /* receive segment */
      char recv_buf[2048];
      recv(sockfd, recv_buf, sizeof(recv_buf), 0);

      /* read segment */
      int segment_start, segment_len;
      sscanf(recv_buf, "DATA %u %u\n", &segment_start, &segment_len);
      char* data = strchr(recv_buf, '\n') + 1;

      /* check if segment was not received before */
      int segment_index = segment_start / SEGMENT_SIZE;
      if (segment_index < segments_written) continue;
      if (segments_recvd[segment_index - segments_written]) continue;

      if (DEBUG)
        printf("%d - %d\n", segment_index, segment_len);

      /* save segment in segments array and mark it as received */
      segments_recvd[segment_index - segments_written] = 1;
      memcpy(segments[segment_index - segments_written], data, segment_len);
    }


    /* if first segment in window was received in this iteration */
    if (segments_recvd[0]) {
      /* write segments to file till first one that was not received */
      int written = 0;
      while(segments_recvd[written]) {
        int len = (written + segments_written != segments_needed - 1) ? SEGMENT_SIZE : size % SEGMENT_SIZE;

        if (DEBUG) {
          printf("len: %d\n", len);
          printf("%s\n", segments[written]);
        }

        write(filefd, segments[written++], len);
      }

      /* move move segments and received arrays to override written segments and set the moved part to zero */
      memcpy(segments_recvd, segments_recvd + written, (WINDOW_SIZE - written) * sizeof(u_int8_t));
      bzero(segments_recvd + WINDOW_SIZE - written, written * sizeof(u_int8_t));
      memcpy(segments, segments + written, (WINDOW_SIZE - written) * SEGMENT_SIZE * sizeof(char));
      bzero(segments + WINDOW_SIZE - written, written * SEGMENT_SIZE * sizeof(char));
      segments_written += written;
    }

    if (DEBUG) {
      printf("written: %d\n", segments_written);
      printf("received:\n");
      for (int i = 0; i < WINDOW_SIZE; i++)
        printf("%d - %d\n", segments_written + i, segments_recvd[i]);
      printf("\n");
    }
  }

  close(filefd);

  return 0;
}
