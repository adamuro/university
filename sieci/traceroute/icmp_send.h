#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PACKETS 3

u_int16_t icmp_send(int sockfd, char* dest_ip, int ttl);
