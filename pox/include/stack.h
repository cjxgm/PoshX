#ifndef __STACK_H__
#define __STACK_H__

#include "type.h"

typedef struct stack
{
	int4 data;
	struct stack *next;
} stack_t;

void stack_push(stack_t **stack, int4 data);
void stack_pop(stack_t **stack, int4 *data);

#endif
