#ifndef _GAME_NET_PROTOCOL_H_
#define _GAME_NET_PROTOCOL_H_
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	uint32_t x;
	uint32_t y;
} POINT;

typedef struct{
	POINT position;
	uint16_t radius;
	//0 is sign of client's character,
	//another signs for other teams:
	unsigned char team_flag;
	char nickname[20];
} CIRCLE;

typedef struct{
	uint16_t* count;//also, head
	CIRCLE* circles;

} ANNOUNCE_MESSAGE;

extern ANNOUNCE_MESSAGE* create_announce_message(uint16_t count){
	char* memory = (char*)malloc(sizeof(uint16_t) + count * sizeof(CIRCLE));
	ANNOUNCE_MESSAGE* msg = (ANNOUNCE_MESSAGE*)malloc(sizeof(ANNOUNCE_MESSAGE));
	msg->count = (uint16_t*)memory;
	memcpy(memory, &count, sizeof(count));
	msg->circles = (CIRCLE*)(memory + sizeof(uint16_t));
	return msg;
}

enum{
	REQ_DISCONNECT		= 1204,
	REQ_CONNECT			= 1669,
	RESP_CONNECTED		= 8351
};

#endif