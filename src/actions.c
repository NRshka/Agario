#include "actions.h"
#define mem_up_size 5

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t length;
} VECTOR;

typedef struct client{
	uint16_t x;
	uint16_t y;
	VECTOR range;
	VECTOR speed;
	uint16_t sup_speed;//ускорение
} CLIENT;

typedef struct{
	uint16_t count;
	uint16_t data_len;
	CLIENT** array;//array of pointers
}DYNAMIC_LIST;

void add_client(DYNAMIC_LIST* list, CLIENT* cl){
	if(count >= data_len){
		list->data_len += mem_up_size;
		list->array = realloc(list->array, list->data_len * sizeof(CLIENT*));
	}
	list->array[list->count++] = cl;
}

void delete_client(DYNAMIC_LIST* list, uint4_t index){
	//TODO: проверка на rangeout
	free(list->array[index]);
	for(int i = index; i < list->count - 1; i++)
		list->array[i] = list->array[i + 1];
}

int calc_range(CLIENT* cl1, CLIENT* cl2){
	uint16_t distance = sqrt((cl1->x - cl2->x) * (cl1->x - cl2->x) + (cl1->y - cl2->y) * (cl1->y - cl2->y));
	return (cl1->range + cl2->range) - distance;
}

typedef struct{
	uint16_t count;
	uint16_t data_len;
	_ACTIONS* array;//array of pointers
}