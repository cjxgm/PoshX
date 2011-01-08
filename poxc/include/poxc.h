#ifndef __POXC_H__
#define __POXC_H__

#include "error.h"
#include "const.h"
#include "type.h"
#include "opcode.h"


typedef struct tagTOKEN{
	byte type;
	union data{
		uint16 value;
		char text[MAX_IDLEN];
	} data;
	struct tagTOKEN* next;
} TOKEN;
void poxc_compile(FILE* fpin, FILE* fpout);
void lex(FILE* fp);

void append_token(byte type, char text[]);

#endif
