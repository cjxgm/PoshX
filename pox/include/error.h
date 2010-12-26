#ifndef __ERROR_H__
#define __ERROR_H__

static int error = 0;

#define ERROR(e) error = e
#ifdef __DEBUG__
#include <stdio.h>
#define THROW(iserr,e){\
	if (iserr) printf("Error: ");\
	printf("%s\n", e);\
	if (iserr) { error=-1; return; };\
}
#else
#define THROW(e) { ERROR(e); return; }
#endif

#define ERR_FILETYPE_MISMATCH			1
#define ERR_VERSION_MISMATCH			2
#define ERR_UNKNOWN_SECTION				3
#define ERR_UNEXPECTED_HALTED			4
#define ERR_UNKNOWN_CODE				5
#define ERR_STACK_OVERFLOW				6

#define ERR_HALT						255

#endif
