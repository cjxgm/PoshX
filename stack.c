/** stack.c
 * Stack operation
 **
 * This file is part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * Obey the KING Principle.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 * COPYLEFT(C):
 *		Clan Open Studio, 2010-2011.
 */

#include "stdlib.h"
#include "stack.h"
#include "error.h"

stack_t *stack_new(int4 size)
{
	stack_t *stack = malloc(sizeof(stack_t));
	if (stack == NULL) throw(ERR_MEMOP_FAILED);

	stack->sp = 0;
	stack->size = size;
	stack->data = malloc(sizeof(pox_data_t)*size);

	return stack;
}

void stack_free(stack_t *stack)
{
	free(stack->data);
	// I think it's better to clear them up.
	stack->data = NULL;
	stack->size = 0;
	stack->sp = 0;
}

void stack_push(stack_t *stack, const pox_data_t data)
{
	if (stack->sp == stack->size)
		throw(ERR_OUT_OF_STACK);
	
	stack->data[stack->sp++] = data;
}

pox_data_t stack_pop(stack_t *stack)
{
	if (stack->sp == 0)
		throw(ERR_OUT_OF_STACK);

	return stack->data[--stack->sp];
}

pox_data_t stack_pop_all(stack_t *stack)
{
	pox_data_t temp = 0;
	while(stack->sp) temp = stack_pop(stack);
	return temp;
}

