#ifndef __ERROR_H__
#define __ERROR_H__

static int error = 0;

#define ERROR(e) error = e

#define COLOR_RED_BOLD printf("\033[01;31m");
#define COLOR_GREEN_BOLD printf("\033[01;32m");
#define COLOR_BLUE_BOLD printf("\033[01;34m");
#define COLOR_RESET printf("\033[0m");

#ifdef __DEBUG__
	#include <stdio.h>
	#define THROW(iserr,e){\
		if (iserr) { COLOR_RED_BOLD; printf("Error: "); }\
		COLOR_RESET;\
		printf("%s\n", e);\
		COLOR_RESET;\
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
