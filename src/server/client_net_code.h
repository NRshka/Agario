#include <stdio.h>
#include <linux/udp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../libproto/protocol.h"

extern int init_udp(char* serv_address);
extern int try_connect(int fd);
extern void catch_message(int fd, char* buf, int size);
extern int main_loop(int is_default, char *serv_addr);