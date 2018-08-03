#include <stdio.h>
#include <linux/udp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include "../libproto/protocol.h"

#define NULL ((void*)0)

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
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
	char buf[2000];
	struct sockaddr_in new_client;
	int s = sizeof(new_client);
	int state = -1;
	int bytes_read = recvfrom(fd, &state, sizeof(int), 0, &new_client, &s);
	int port = htons(new_client.sin_port);
	uint32_t a = htonl(new_client.sin_addr.s_addr);
	char* addr = &a;
	printf("port: %d, ip: %d.%d.%d.%d\n", port, addr[0], addr[1], addr[2], addr[3]);


	if(state == REQ_CONNECT){
		ANNOUNCE_MESSAGE* msg = create_announce_message(2);
		char nick1[] = "player1";
		char nick2[] = "player2";
		msg->circles[0].position.x = 5;
		msg->circles[0].position.y = 3;
		msg->circles[0].radius = 18;
		strcpy(msg->circles[0].nickname, nick1);

		msg->circles[1].position.x = 9;
		msg->circles[1].position.y = 14;
		msg->circles[1].radius = 16;
		strcpy(msg->circles[1].nickname, nick2);
		
		size_t sz =  2 * sizeof(CIRCLE) + sizeof(uint16_t);
		int code = sendto(fd, msg->count, sz, 0, (struct sockaddr*)&new_client, s);
		printf("SENT %d bytes with code: %d\n", sz, code);
		if(code < 0)
			perror("BLYAT");
	}
	else
	{
		printf("OOpes\n");
	}
	close(fd);
	return 0;
}
