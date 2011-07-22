/** symtab.h
 * 
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#ifndef __SYMTAB_H__
#define __SYMTAB_H__

u16 symtab_append_var(const char * text);
u16 symtab_append_value(const char * text);
u16 symtab_append_label(const char * text);
void symtab_set_label(u16 labelid, u16 addr);
inline u16 symtab_get_var_len();
inline u16 symtab_get_value_len();
s32 symtab_get_value(u16 valueid);
u16 symtab_get_label(u16 labelid);

#endif

