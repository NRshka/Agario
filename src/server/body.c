#include <stdio.h>
#include <linux/udp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../libproto/protocol.h"

int init_udp();

int main(int argc, char **argv)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);//UDP
	if(fd == -1){
		printf("socket crash\n");
		return 2;
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(2591);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int c = connect(fd, &serv_addr, sizeof(serv_addr));
	if(c < 0){
		printf("Connect crash\n");
		return 2;
	}

    char buf[2000];
    int con = REQ_CONNECT;
    send(fd, &con, sizeof(int), 0);
    printf("signed\n");
    #define NULL ((void*)0)
	int bytes_read = recvfrom(fd, buf, 20000, 0, NULL, NULL);
	ANNOUNCE_MESSAGE mes;
	mes.count = buf;
	mes.circles = buf + sizeof(uint16_t);
	
    printf("Count: %d\n", *mes.count);
    #define ITER mes.circles[i]
    for(int i = 0; i < 2; i++)
    {
        printf("X: %d\nY: %d\nRadius: %d\nNickname: %s\n", ITER.position.x, ITER.position.y, ITER.radius, ITER.nickname);
    }
    

	close(fd);
	printf("%s\n", buf);
	return 0;
}
