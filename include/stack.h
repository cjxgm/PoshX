/** stack.h
 * Stack operation
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#ifndef __STACK_H__
#define __STACK_H__

#include "type.h"

STACK * stack_new(s32 size);
void stack_free(STACK * stack);
void stack_push(STACK * stack, const POX_DATA data);
POX_DATA stack_pop(STACK * stack);
POX_DATA stack_pop_all(STACK * stack);

#endif

