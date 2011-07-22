/** poxc.h
 * 
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#ifndef __POXC_H__
#define __POXC_H__

#include "type.h"
#include "stdio.h"

void poxc_compile(FILE * fpin, FILE * fpout); // Avoid using this
void poxc_compile_file(const char * filein, const char * fileout);

////// INTERNAL USE //////
inline void poxc_parse(FILE * fp);
void poxc_lex(FILE * fp);
inline bool is_key(const char *IDo_check);
void emit_code(const char * key);
void poxc_write(FILE * fp);

#define TYPE_UNKNOWN 		0
#define TYPE_KEY 			1
#define TYPE_IDENT 			2
#define TYPE_VALUE 			3
#define TYPE_LABEL 			4

#endif

