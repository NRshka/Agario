#include "client_net_code.h"

//if client wants to leave game he switch on this flag in another thread:
char is_break_now;

int init_udp(char* serv_address){
	int fd = socket(AF_INET, SOCK_DGRAM, 0);//UDP
	if(fd == -1){
		perror("socket crash\n");
		return -1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(2591);
	serv_addr.sin_addr.s_addr = inet_addr(serv_address);
	int c = connect(fd, &serv_addr, sizeof(serv_addr));
	if(c < 0){
		perror("Connect crash\n");
		return c;
	}
}

int try_connect(int fd){
	int con = REQ_CONNECT;
	send(fd, &con, sizeof(int), 0);
	int resp = -1;
	resp = recvfrom(fd, &resp, sizeof(int), 0, NULL, NULL);
	return resp;
}

void catch_message(int fd, char* buf, int size){
	memset(buf, 0, size);
	recvfrom(fd, buf, size, 0, NULL, NULL);
}

int main_loop(int is_default, char *serv_addr)
{
	is_break_now = 0;
	char default_addr[] = "127.0.0.1";
	int fd = -1;
	if(is_default)
		fd = init_udp(default_addr);
	else
		fd = init_udp(serv_addr);
	
	int is_connected = try_connect(fd);

	char* buf = (char*)malloc(BUFSIZ);
	while(1){
		if(is_break_now)
			break;
		
		catch_message(fd, buf, BUFSIZ);
	}

	close(fd);
	printf("%s\n", buf);
	return 0;
}
