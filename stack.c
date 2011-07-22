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

STACK * stack_new(s32 size)
{
	STACK * stack = malloc(sizeof(STACK));
	if (stack == NULL) throw(ERR_MEMOP_FAILED);

	stack->sp = 0;
	stack->size = size;
	stack->data = malloc(sizeof(POX_DATA)* size);

	return stack;
}

void stack_free(STACK * stack)
{
	free(stack->data);
	// I think it's better to clear them up.
	stack->data = NULL;
	stack->size = 0;
	stack->sp = 0;
}

void stack_push(STACK * stack, const POX_DATA data)
{
	if (stack->sp == stack->size)
		throw(ERR_OUT_OF_STACK);
	
	stack->data[stack->sp++] = data;
}

POX_DATA stack_pop(STACK * stack)
{
	if (stack->sp == 0)
		throw(ERR_OUT_OF_STACK);

	return stack->data[--stack->sp];
}

POX_DATA stack_pop_all(STACK * stack)
{
	POX_DATA temp = 0;
	while(stack->sp) temp = stack_pop(stack);
	return temp;
}

