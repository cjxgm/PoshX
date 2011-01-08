#ifndef __POX_H__
#define __POX_H__

#include <stdlib.h>
#include "error.h"
#include "type.h"
#include "stack.h"

#define POX_VERSION 0x00

typedef struct tagPOX_CODE{
	byte code;			// Operating code 
	uint16 data;		// Data pointer (to POX.ds)
} POX_CODE;

typedef struct tagPOX{
	POX_CODE* cs;		// Code section
	int32* ds;			// Data section
	uint16 lencs;		// Length of cs
	uint16 lends;		// Length of ds
	uint16 ip;			// Instruction Pointer
	STACK* sdata;		// Stack for user data;
	STACK* scall;		// Stack for function calls;
} POX;

#define POX_INIT calloc(1, sizeof(POX))
void pox_load(char* filename, POX* pox);
void pox_run(POX* pox);
void pox_run_once(POX* pox);

#endif
