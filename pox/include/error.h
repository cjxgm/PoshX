#ifndef __ERROR_H__
#define __ERROR_H__

static int error = 0;

#ifdef __DEBUG__
#include <stdio.h>
#define THROW(iserr,e){\
	if (iserr) printf("Error: ");\
	printf("%s\n", e);\
	if (iserr) return;\
}
#else
#define ERROR(e) error = e
#define THROW(e) { ERROR(e); return; }
#endif

#define ERR_FILETYPE_MISMATCH			1
#define ERR_VERSION_MISMATCH			2
#define ERR_UNKNOWN_SECTION				3

#endif
