#ifndef __POX_H__
#define __POX_H__

#include <stdlib.h>
#include "error.h"
#include "type.h"
#include "stack.h"

#define POX_VERSION 0x00

typedef struct pox_code
{
	byte code;		// Operating code 
	uint4 data;		// Data pointer (to pox_t.ds)
} pox_code_t;

typedef struct pox
{
	pox_code_t *cs;		// Code section
	int4 *ds;			// Data section
	uint4 lencs;		// Length of cs
	uint4 lends;		// Length of ds
	uint4 ip;			// Instruction Pointer
	stack_t *data_stack;		// Stack for user data;
	stack_t *call_stack;		// Stack for function calls;
} pox_t;

#define POX_INIT calloc(1, sizeof(pox_t))
void pox_load(char* filename, pox_t* pox);
void pox_run(pox_t* pox);
void pox_run_once(pox_t* pox);

#endif
