/** symtab.c
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
#include "type.h"
#include "error.h"

static char symtab_var[0xFFFF][MAX_NAME_LEN];
static int var_pos = 0;
static char symtab_value[0xFFFF][MAX_NAME_LEN];
static int value_pos = 0;
static struct _label
{
	char name[MAX_NAME_LEN];
	int addr; // Set to int rather than uint 2 is resonable.
} symtab_label[0xFFFF];
static int label_pos = 0;

int symtab_append_var(const char * text)
{
	// Check if there is the same
	int i;
	for (i=0; i<var_pos; i++)
		if (strcmp(symtab_var[i], text) == 0)
			return i;
	
	// Overflow!
	if (var_pos + value_pos == 0xFFFF)
		throw(ERR_SYMTAB_OVERFLOW);

	debug("SYMTAB.VAR[%d]\t%s", var_pos, text);

	strcpy(symtab_var[var_pos], text);
	return var_pos++;
}

int symtab_append_value(const char * text)
{
	// Check if there is the same
	int i;
	for (i=0; i<value_pos; i++)
		if (strcmp(symtab_value[i], text) == 0)
			return i;

	// Overflow!
	if (var_pos + value_pos == 0xFFFF)
		throw(ERR_SYMTAB_OVERFLOW);

	debug("SYMTAB.VALUE[%d]\t%s", value_pos, text);

	strcpy(symtab_value[value_pos], text);
	return value_pos++;
}

u16 symtab_append_label(const char * text)
{
	// Check if there is the same
	int i;
	for (i=0; i<label_pos; i++)
		if (strcmp(symtab_label[i].name, text) == 0)
			return i;
	
	// Overflow!
	if (label_pos == 0xFFFF)
		throw(ERR_SYMTAB_OVERFLOW);

	debug("SYMTAB.LABEL[%d]\t%s", label_pos, text);

	strcpy(symtab_label[label_pos].name, text);
	symtab_label[label_pos].addr = -1;
	return label_pos++;
}

void symtab_set_label(u16 labelid, u16 addr)
{
	// if (labelid >= label_pos) throw(???);
	if (symtab_label[labelid].addr != -1){
		debug("[%s: %d] -> %d", &symtab_label[labelid].name[1],
						symtab_label[labelid].addr, addr);
		throw(ERR_REDEFINE_LABEL);
	}
	symtab_label[labelid].addr = addr;
}

inline u16 symtab_get_var_len()
{
	return var_pos;
}

inline u16 symtab_get_value_len()
{
	return value_pos;
}

s32 symtab_get_value(u16 valueid)
{
	return atoi(symtab_value[valueid]);
}

u16 symtab_get_label(u16 labelid)
{
	if (symtab_label[labelid].addr == -1){
		debug("[%s:%d]", symtab_label[labelid].name, labelid);
		throw(ERR_LABEL_UNDEFINED);
	}
	return symtab_label[labelid].addr;
}

