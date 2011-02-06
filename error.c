/** error.c
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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "error.h"

string error_msgs[] = {
	"",
/* 01 */
	"File operation failed!\n"
	"\t(e.g. Cannot open/read/write the file, etc.)",
/* 02 */
	"Memory operation failed!\n"
	"\t(Generally it's because you don't have\n"
	"\t enough memory left.)",
/* 03 */
	"Stack overflow/underflow!",
/* 04 */
	"File type mismatch!\n"
	"\tAre you sure it is a POX file?",
/* 05 */
	"File version mismatch!",
/* 06 */
	"Unknown section!",
/* 07 */
	"Unexpected halted!\n"
	"\tIs there any \"halt\"?",
/* 08 */
	"Unknown operating code!\n"
	"\tYou write the file yourself???",
/* 09 */
	"Identifier is too long!",
/* 10 */
	"Unknown character!",
/* 11 */
	"Symbol table overflow!\n"
	"\tUsually, it's because you use too many variables/values.",
/* 12 */
	"Unexpected end of file!",
/* 13 */
	"Unexpected value/variable!",
/* 14 */
	"Redefinition of label!",
/* 15 */
	"Code table overflow!\n"
	"\tUsually, it's because you use too many instructions.",
/* 16 */
	"Label undefined!!",
};

void throw(byte errno)
{
	assert(errno != ERR_OK);

	// CAUTION: It may go wrong if you pass it a wrong errno!
	// \033[00;31m		Red Color
	// \033[0m			Normal Color(Normally it's white)
	printf("\033[00;31mERROR:\033[0m %s\n", error_msgs[errno]);
	exit(errno);
}

#ifdef __DEBUG__

void debug(string fmt, ...)
{
	if (fmt == NULL || fmt[0] == 0){
		printf("\n");
		return;
	}

	// \033[00;34m		Blue Color
	// \033[0m			Normal Color(Normally it's white)
	printf("\033[00;34mDEBUG:\033[0m ");

	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	printf("\n");
}

void warn(byte errno)
{
	assert(errno != ERR_OK);

	// CAUTION: It may go wrong if you pass it a wrong errno!
	// \033[00;33m		Yello Color
	// \033[0m			Normal Color(Normally it's white)
	printf("\033[00;33mWARNING:\033[0m %s\n", error_msgs[errno]);
}

#endif

