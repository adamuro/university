#include "sliding_window.h"

/* Auxiliary functions */

u_int32_t min(u_int32_t const a, u_int32_t const b) {
  return a < b ? a : b;
}

u_int8_t swin_segrcvd(struct sliding_window swin, u_int32_t const id) {
  return id < swin.seg_wrtn || swin.seg_rcvd[id - swin.seg_wrtn];
}

u_int32_t swin_maxiter(struct sliding_window swin) {
  return min(swin.seg_file, swin.seg_wrtn + WINDOW_SIZE);
}

u_int32_t seg_file(u_int32_t const filesize) {
  return filesize / SEGMENT_SIZE + (filesize % SEGMENT_SIZE != 0);
}

u_int32_t seg_itos(u_int32_t const id) {
  return id * SEGMENT_SIZE;
}

u_int32_t seg_len(u_int32_t const id, struct sliding_window swin) {
  return (id != swin.seg_file - 1) ? SEGMENT_SIZE : swin.filesize % SEGMENT_SIZE;
}

uint32_t seg_stoi(u_int32_t start) {
  return start / SEGMENT_SIZE;
}

char* seg_content(char* buf) {
  return strchr(buf, '\n') + 1;
}

void swin_segrcv(struct sliding_window *swin, u_int32_t id, char* content, u_int32_t len) {
  swin->seg_rcvd[id - swin->seg_wrtn] = 1;
  memcpy(swin->segments[id - swin->seg_wrtn], content, len);
}

void seg_parsebuf(char *buf, u_int32_t *start, u_int32_t *len, u_int32_t *id) {
  sscanf(buf, "DATA %u %u\n", start, len);
  *id = seg_stoi(*start);
}

/* Main functions */

int swin_req(int sockfd, u_int32_t const id, struct sliding_window swin) {
  if (swin_segrcvd(swin, id))
    return 0;

  char buf[64];
  u_int32_t start = seg_itos(id);
  u_int32_t len = seg_len(id, swin);
  size_t buflen = sprintf(buf, "GET %d %d\n", start, len);

  return send(sockfd, buf, buflen, 0);
}

int swin_recv(int sockfd, struct sliding_window *swin) {
  u_int32_t start, len, id;
  char buf[2048];

  int recvd = recv(sockfd, buf, sizeof(buf), 0);
  if (recvd < 0)
    return recvd;

  seg_parsebuf(buf, &start, &len, &id);
  if (swin_segrcvd(*swin, id))
    return recvd;

  char* content = seg_content(buf);
  swin_segrcv(swin, id, content, len);

  return recvd;
}


/* Test comment */
void swin_init(struct sliding_window *swin, u_int32_t const filesize) {
  swin->seg_file = seg_file(filesize);
  swin->filesize = filesize;
  swin->seg_wrtn = 0;

  bzero(swin->seg_rcvd, sizeof(swin->seg_rcvd));
  bzero(swin->segments, sizeof(swin->segments));
}

int swin_reqall(int sockfd, struct sliding_window swin) {
  for (u_int32_t id = swin.seg_wrtn; id < swin_maxiter(swin); id++) {
    int sent = swin_req(sockfd, id, swin);
    if (sent < 0) {
      fprintf(stderr, "send error: %s\n", strerror(errno));
      return sent;
    }
  }

  return 0;
}

int swin_recvall(int sockfd, struct sliding_window *swin) {
  struct timeval tv;
  tv.tv_sec  = WAIT_TIME_SEC;
  tv.tv_usec = WAIT_TIME_USEC;

  fd_set descriptors;
  FD_ZERO(&descriptors);
  FD_SET(sockfd, &descriptors);

  for (;;) {
    int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
    if (ready == 0)
      return ready;

    if (ready < 0) {
      fprintf(stderr, "select error: %s\n", strerror(errno)); 
      return ready;
    }

    int recvd = swin_recv(sockfd, swin);
    if (recvd < 0) {
      fprintf(stderr, "recv error: %s\n", strerror(errno)); 
      return recvd;
    }
  }
}

int swin_write(int filefd, struct sliding_window *swin) {
  u_int32_t seg_wrtn = 0;
  while(swin_segrcvd(*swin, seg_wrtn + swin->seg_wrtn)) {
    u_int32_t len = seg_len(seg_wrtn + swin->seg_wrtn, *swin);
    ssize_t written = write(filefd, swin->segments[seg_wrtn++], len);
    if (written < 0) {
      fprintf(stderr, "write error: %s\n", strerror(errno)); 
      return written;
    }
  }

  memcpy(swin->seg_rcvd, swin->seg_rcvd + seg_wrtn, (WINDOW_SIZE - seg_wrtn) * sizeof(u_int8_t));
  bzero(swin->seg_rcvd + WINDOW_SIZE - seg_wrtn, seg_wrtn * sizeof(u_int8_t));
  memcpy(swin->segments, swin->segments + seg_wrtn, (WINDOW_SIZE - seg_wrtn) * SEGMENT_SIZE * sizeof(char));
  bzero(swin->segments + WINDOW_SIZE - seg_wrtn, seg_wrtn * SEGMENT_SIZE * sizeof(char));
  swin->seg_wrtn += seg_wrtn;

  return seg_wrtn;
}
