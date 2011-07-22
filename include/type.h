/** type.h
 * 
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#ifndef __TYPE_H__
#define __TYPE_H__

typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef const char * STRING;
typedef unsigned char byte;
typedef byte bool;
#define true	1
#define false	0

/****** pox ******/
typedef struct _pox_code POX_CODE;
typedef struct _pox POX;
typedef struct _stack STACK;
typedef s32 POX_DATA;

/****** poxc ******/
#define MAX_NAME_LEN 31

/****** pox ******/
struct _pox_code
{
	byte code;		// Operating code
	u16 addr;		// Address
};

struct _pox
{
	POX_CODE * cs;				// Code section
	POX_DATA * ds;				// Data section
	u16 lencs;				// Length of cs
	u16 lends;				// Length of ds
	STACK * user_stack;		// User stack
	STACK * call_stack;		// call stack
	/* Though it should be u16, but, as the same
	   reason as why fgetc returns int rather than
	   char, I set it s32.*/
	s32 ip;					// Instruction Pointer
};

// stack
struct _stack
{
	POX_DATA * data;
	/* Though it should be u16, but, as the same reason 
	   as why fgetc returns int rather than char, I set it s32.*/
	s32 size;		// Stack size
	s32 sp;		// Stack pointer
};

#endif

