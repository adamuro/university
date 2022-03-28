#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>

#include "common.h"

#define MAX_RECV_TIME 1
#define SEC_TO_MS 1000
#define MS_TO_MICROSEC 1000

int icmp_receive(int sockfd, char* dest_ip, int ttl);
