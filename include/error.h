/** error.h
 * The error proccessing function and basic IO.
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

#ifndef __ERROR_H__
#define __ERROR_H__

#include "type.h"

extern string error_msgs[];

void throw(byte errno);
void warn(byte errno);
void print(string str);
#ifdef __DEBUG__
void debug(string fmt, ...);
#else
#define debug(fmt, ...)
#endif

#define ERR_OK						0
#define ERR_FILEOP_FAILED			1
#define ERR_MEMOP_FAILED			2
#define ERR_OUT_OF_STACK			3
#define ERR_FILETYPE_MISMATCH		4
#define ERR_FILEVER_MISMATCH		5
#define ERR_UNKNOWN_SEC				6
#define ERR_UNEXPECTED_HALT			7
#define ERR_UNKNOWN_OPCODE			8

#endif

