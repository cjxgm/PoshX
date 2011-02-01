/** stack.h
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

#ifndef __STACK_H__
#define __STACK_H__

#include "type.h"

stack_t *stack_new(int4 size);
void stack_free(stack_t *stack);
void stack_push(stack_t *stack, const pox_data_t data);
pox_data_t stack_pop(stack_t *stack);
pox_data_t stack_pop_all(stack_t *stack);

#endif

