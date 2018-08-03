#ifndef _GAME_NET_PROTOCOL_H_
#define _GAME_NET_PROTOCOL_H_
#include <stdint.h>

typedef struct{
	uint32_t x;
	uint32_t y;
} POINT;

typedef struct{
	POINT position;
	uint16_t radius;
	char nickname[20];
} CIRCLE;

typedef struct{
	uint16_t* count;//also, head
	CIRCLE* circles;

} ANNOUNCE_MESSAGE;

extern ANNOUNCE_MESSAGE* create_announce_message(uint16_t count){
	char* memory = malloc(sizeof(uint16_t) + count * sizeof(CIRCLE));
	ANNOUNCE_MESSAGE* msg = malloc(sizeof(ANNOUNCE_MESSAGE));
	msg->count = memory;
	memcpy(memory, &count, sizeof(count));
	msg->circles = memory + sizeof(uint16_t);
	return msg;
}

enum{
	REQ_DISCONNECT		= 0,
	REQ_CONNECT			= 1
};

#endif