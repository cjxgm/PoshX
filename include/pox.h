/** pox.h
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

#ifndef __POX_H__
#define __POX_H__

#include "type.h"
#include "stdio.h"

pox_t *pox_load(FILE* fp);
pox_t *pox_load_file(const char *filename);
void pox_free(pox_t *pox);

void pox_run(pox_t *pox);
bool pox_run_once(pox_t *pox);

#endif

