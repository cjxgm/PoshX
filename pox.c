/** pox.c
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

#include <string.h>
#include <stdlib.h>
#include "pox.h"
#include "error.h"
#include "stack.h"
#include "common.h"

POX * pox_load_file(STRING filename)
{
	// Open file
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) throw(ERR_FILEOP_FAILED);

	// Skip the magic line
	// e.g. "#!...\n"
	int ch;
	while ((ch = getc(fp)) != EOF && ch != '\n');

	POX * pox = pox_load(fp);
	fclose(fp);

	return pox;
}

POX * pox_load(FILE* fp)
{
	int i;

	// Read POX Header
	/** POX HEADER STRUCTURE
	 * _________________
	 * |'P'|'O'|'X'| V |
	 * ~~~~~~~~~~~~~~~~~
	 * V is the subversion of Posh X 10.V
	 */
	byte hdr[4];
	fread(hdr, sizeof(byte), 4, fp);

	// Check if it is a POX file
	for (i=0; i<3; i++)
		if (hdr[i] != "POX"[i])
			throw(ERR_FILETYPE_MISMATCH);

	// Check the version
	if (hdr[3] != POX_VERSION)
		throw(ERR_FILEVER_MISMATCH);

	// Init
	POX * pox = malloc(sizeof(POX));
	pox->cs = NULL;
	pox->ds = NULL;
	pox->lencs = pox->lends = pox->ip = 0;
	pox->user_stack = stack_new(0xFFFF);
	pox->call_stack = stack_new(0xFFFF);

	// Load sections
	/** SECTION STRUCTURE
	 * _____________________________________
	 * | N +...+ 0 | P + . + . + . | B +...|
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 * N:	Section name (Maximal 20)
	 *		Followed by 0.
	 * P:	4 bytes, it's the length of
	 *		the section body.
	 * B:	The section body.
	 */
	while (!feof(fp)){
		// Section name
		char sec_name[21];
		for (i=0; i<20; i++){
			int ch;
			if ((ch = getc(fp)) == 0)
				break;
			if (ch == EOF){
				if (i != 0)	throw(ERR_FILEOP_FAILED);
				return pox;
			}
			sec_name[i] = ch;
		}
		sec_name[i] = 0;

		// Body length
		u32 body_len;
		fread(&body_len, sizeof(u32), 1, fp);

		debug("[%s: %d]", sec_name, body_len);

		// .code section
		if (strcmp(sec_name, ".code") == 0){
			/** .CODE SECTION STRUCTURE
			 * ____________________________________
			 * | A + . | C + D + . | C + D + . |...)
			 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			 * A:	2 bytes. Amount of instructions
			 * C:	1 byte. Operating code
			 * D:	2 bytes. Address of data
			 * ...:	(C+D) wiil be as many as A shows.
			 */
			// Amount
			fread(&pox->lencs, sizeof(u16), 1, fp);

			// Read CS
			pox->cs = malloc(sizeof(POX_CODE) * pox->lencs);
			for (i=0; i<pox->lencs; i++){
				fread(&pox->cs[i].code, sizeof(byte), 1, fp);
				fread(&pox->cs[i].addr, sizeof(u16), 1, fp);
			}

#ifdef __DEBUG__
			for (i=0; i<pox->lencs; i++)
				debug("\t%4.4Xh: %2.2Xh  %4.4Xh", 
						i, pox->cs[i].code, pox->cs[i].addr);
			debug("");
#endif
		}

		// .data section
		else if (strcmp(sec_name, ".data") == 0){
			/** .DATA SECTION STRUCTURE
			 * ____________________________________________________
			 * | A1+ . | A2+ . | V + . + . + . | V + . + . + . |...)
			 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			 * A1:	2 bytes. Amount of variables
			 * A2:	2 bytes. Amount of values
			 * V:	4 bytes. Value
			 * ...:	V wiil be as many as A2 shows.
			 */
			// Read amounts
			u16 len;
			fread(&len, sizeof(u16), 1, fp);
			len += 0x10; // 0x00~0x10(not included)
			// are reserved for registers.
			fread(&pox->lends, sizeof(u16), 1, fp);
			pox->lends += len;

			// Read ds
			pox->ds = malloc(sizeof(POX_DATA) * pox->lends);
			// 0x10~len(not included) are used for variables
			// len~lends(not included) are used for datas
			for (i=len; i<pox->lends; i++)
				fread(&pox->ds[i], sizeof(POX_DATA), 1, fp);

#ifdef __DEBUG__
			for (i=0; i<pox->lends; i++)
				debug("\t%4.4Xh: %8.8Xh", i, pox->ds[i]);
			debug("");
#endif
		}

		// Unknown section
		else {
			warn(ERR_UNKNOWN_SEC);
			// Skip it
			fseek(fp, body_len, SEEK_CUR);
		}
	}
	return pox;
}

void pox_free(POX * pox)
{
	free(pox->cs);
	free(pox->ds);
	stack_free(pox->user_stack);
	stack_free(pox->call_stack);

	// Clear them up
	pox->cs = NULL;
	pox->ds = NULL;
	pox->user_stack = pox->call_stack = NULL;
	pox->lencs = pox->lends = pox->ip = 0;
}

void pox_run(POX * pox)
{
	debug("{POX_RUN BEGINS}");

	for(;;){
		if (pox->ip >= pox->lencs)
			throw(ERR_UNEXPECTED_HALT);
		if (pox_run_once(pox))
			break;
	}
	debug("{POX_RUN ENDS}");
}

// @return	true  -> halt
//			false -> continue
bool pox_run_once(POX * pox)
{
#define CODE (pox->cs[pox->ip].code)
#define ADDR (pox->cs[pox->ip].addr)
#define DATA (pox->ds[ADDR])

	POX_DATA tempi, tempj;

	switch(CODE){
	case NOP:
		break;

	case PUSH:
		stack_push(pox->user_stack, DATA);
		break;
	case POP:
		DATA = stack_pop(pox->user_stack);
		break;
	case POPA:
		DATA = stack_pop_all(pox->user_stack);
		break;

	case JMP:
		pox->ip = (s32)ADDR - 1;
		break;
	case JZ:
		tempi = stack_pop(pox->user_stack);
		if (tempi == 0) pox->ip = (s32)ADDR - 1;
		break;
	case CALL:
		stack_push(pox->call_stack, (POX_DATA)pox->ip);
		pox->ip = (s32)ADDR - 1;
		break;
	case CZ:
		tempi = stack_pop(pox->user_stack);
		if (tempi == 0){
			stack_push(pox->call_stack, (POX_DATA)pox->ip);
			pox->ip = (s32)ADDR - 1;
		}
		break;
	case RET:
		pox->ip = (s32)stack_pop(pox->call_stack);
		break;

	case INC:
		if (ADDR) DATA++;
		else{
			tempi = stack_pop(pox->user_stack);
			tempi++;
			stack_push(pox->user_stack, tempi);
		}
		break;
	case DEC:
		if (ADDR) DATA--;
		else{
			tempi = stack_pop(pox->user_stack);
			tempi--;
			stack_push(pox->user_stack, tempi);
		}
		break;
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD:
		// Pay attention to the order I pop them!
		tempj = stack_pop(pox->user_stack);
		tempi = stack_pop(pox->user_stack);
		switch(CODE){
		case ADD: tempi+=tempj; break;
		case SUB: tempi-=tempj; break;
		case MUL: tempi*=tempj; break;
		case DIV: tempi/=tempj; break;
		case MOD: tempi%=tempj; break;
		}
		stack_push(pox->user_stack, tempi);
		break;

	case GT:
	case LT:
	case EQ:
	case AND:
	case OR:
		// Pay attention to the order I pop them!
		tempj = stack_pop(pox->user_stack);
		tempi = stack_pop(pox->user_stack);
		switch(CODE){
			case GT: tempi = (tempi>tempj); break;
			case LT: tempi = (tempi<tempj); break;
			case EQ: tempi = (tempi==tempj); break;
			case AND: tempi = (tempi&&tempj); break;
			case OR: tempi = (tempi||tempj); break;
		}
		stack_push(pox->user_stack, tempi);
		break;
	case NOT:
		if (ADDR) DATA = !DATA;
		else{
			tempi = stack_pop(pox->user_stack);
			tempi = !tempi;
			stack_push(pox->user_stack, tempi);
		}
		break;

	case IN:
		// \033[00;31m		Yello Color
		// \033[0m			Normal Color(Normally it's white)
		printf("\033[00;33m>>>>>\033[0m ");
		scanf("%d", &tempi);
		stack_push(pox->user_stack, tempi);
		break;
	case OUT:
		// \033[00;31m		Purple Color
		// \033[0m			Normal Color(Normally it's white)
		printf("\033[00;35m[OUT]\033[0m ");
		printf("%d\n", stack_pop(pox->user_stack));
		break;

	case HALT:
		return true; // Halt
		break;

	default:
		throw(ERR_UNKNOWN_OPCODE);
		debug("%2.2Xh", CODE);
	}
	pox->ip++;
	return false; // Continue
	#undef DATA
	#undef ADDR
	#undef CODE
}

