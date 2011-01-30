#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "error.h"

void stack_push(stack_t **stack, int4 data)
{
	stack_t *node = malloc(sizeof(stack_t));
	node->next = *stack;
	node->data = data;
	*stack = node;
}

void stack_pop(stack_t **stack, int4 *data)
{
	if (*stack == NULL)
		#ifdef __DEBUG__
		THROW(true, "Stack overflow.")
		#else
		THROW(ERR_STACK_OVERFLOW);
		#endif
	stack_t *node = *stack;
	*stack = node->next;
	*data = node->data;
	free(node);
}
