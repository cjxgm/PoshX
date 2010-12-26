#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "error.h"

void stack_push(STACK** stack, int32 data){
	STACK* node = malloc(sizeof(STACK));
	node->next = *stack;
	node->data = data;
	*stack = node;
}

void stack_pop(STACK** stack, int32* data){
	if (*stack == NULL)
		#ifdef __DEBUG__
		THROW(true, "Stack overflow.")
		#else
		THROW(ERR_STACK_OVERFLOW);
		#endif
	STACK* node = *stack;
	*stack = node->next;
	*data = node->data;
	free(node);
}
