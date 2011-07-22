/** common.h
 * 
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#define POX_VERSION			0x00
#ifndef POX_MAGIC_LINE
#define POX_MAGIC_LINE		"/usr/bin/poshx"
#endif

#define NOP		0x00

#define PUSH	0x01
#define POP		0x02
#define POPA	0x03

#define JMP		0x10
#define JZ		0x11
#define CALL	0x12
#define CZ		0x13
#define RET		0x14

#define INC		0x20
#define DEC		0x21
#define ADD		0x22
#define SUB		0x23
#define MUL		0x24
#define DIV		0x25
#define MOD		0x26

#define GT		0x30
#define LT		0x31
#define EQ		0x32
#define AND		0x33
#define OR		0x34
#define NOT		0x35

//#define INT		0x40
#define IN		0x41
#define OUT		0x42

#define HALT	0xFF

#endif

