#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define WINDOW_SIZE 500 /* In segments */
#define SEGMENT_SIZE 1000 /* In bytes */
#define WAIT_TIME_SEC 0 /* Seconds */
#define WAIT_TIME_USEC 300000 /* Milliseconds */

struct sliding_window {
  u_int32_t filesize; /* Amount of bytes to write */
  u_int32_t seg_file; /* Amount of segments necessary to fill the file */
  u_int32_t seg_wrtn; /* Amount of segments already written to file */
  u_int8_t  seg_rcvd[WINDOW_SIZE]; /* Numbers on indexes of segments received from server have positive value */
  char      segments[WINDOW_SIZE][SEGMENT_SIZE]; /* Content of segments */
};

/* Initialize sliding window structure */
void swin_init(struct sliding_window *swin, u_int32_t const filesize);

/* Send requests for segments not yet received to the server */
int swin_reqall(int sockfd, struct sliding_window swin);

/* Receive segments that come from the server in WAIT_TIME* and save them in sliding window */
int swin_recvall(int sockfd, struct sliding_window *swin);

/* Write segments from sliding window to file until first not received */
int swin_write(int filefd, struct sliding_window *swin);
