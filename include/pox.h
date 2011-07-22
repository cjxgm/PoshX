/** pox.h
 * 
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#ifndef __POX_H__
#define __POX_H__

#include "type.h"
#include "stdio.h"

POX * pox_load(FILE* fp);
POX * pox_load_file(STRING filename);
void pox_free(POX * pox);

void pox_run(POX * pox);
bool pox_run_once(POX * pox);

#endif

