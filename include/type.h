/** type.h
 * 
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

#ifndef __TYPE_H__
#define __TYPE_H__

typedef short int2;
typedef unsigned short uint2;
typedef int int4;
typedef unsigned int uint4;
typedef const char* string;
typedef unsigned char byte;
typedef byte bool;
#define true	1
#define false	0

/****** pox ******/
typedef struct _pox_code pox_code_t;
typedef struct _pox pox_t;
typedef struct _stack stack_t;
typedef int4 pox_data_t;

/****** poxc ******/
typedef struct _tree tree_t;
#define MAX_NAME_LEN 31

/****** pox ******/
struct _pox_code
{
	byte code;		// Operating code
	uint2 addr;		// Address
};

struct _pox
{
	pox_code_t *cs;				// Code section
	pox_data_t *ds;				// Data section
	uint2 lencs;				// Length of cs
	uint2 lends;				// Length of ds
	stack_t *user_stack;		// User stack
	stack_t *call_stack;		// call stack
	/* Though it should be uint2, but, as the same
	   reason as why fgetc returns int rather than
	   char, I set it int4.*/
	int4 ip;					// Instruction Pointer
};

// stack
struct _stack
{
	pox_data_t *data;
	/* Though it should be uint2, but, as the same reason 
	   as why fgetc returns int rather than char, I set it int4.*/
	int4 size;		// Stack size
	int4 sp;		// Stack pointer
};

#endif

