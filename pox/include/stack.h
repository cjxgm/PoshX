#ifndef __STACK_H__
#define __STACK_H__

#include "types.h"

typedef struct tagSTACK{
	int32 data;
	struct tagSTACK* next;
} STACK;

void stack_push(STACK** stack, int32 data);
void stack_pop(STACK** stack, int32* data);

#endif
