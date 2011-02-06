/** symtab.h
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

#ifndef __SYMTAB_H__
#define __SYMTAB_H__

uint2 symtab_append_var(const char *text);
uint2 symtab_append_value(const char *text);
uint2 symtab_append_label(const char *text);
void symtab_set_label(uint2 labelid, uint2 addr);
inline uint2 symtab_get_var_len();
inline uint2 symtab_get_value_len();
int4 symtab_get_value(uint2 valueid);
uint2 symtab_get_label(uint2 labelid);

#endif

