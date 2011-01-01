#include <stdio.h>
#include "include/pox.h"
#include "include/opcodes.h"

int main(){
	FILE* fp = fopen("./test.pox", "wb");

	// POX Header
	fwrite("POX", 1, 3, fp);
	unsigned char v=0x00;
	fwrite(&v, 1, 1, fp);

	// Unknown section
	fwrite(".ver\0\0\0\0\0", 1, 5+4, fp);

	// DATA Section
	unsigned char ds[]={
		0x03, 0x00,	// variable amount
		0x01, 0x00, // value amount
		0x01, 0x00, 0x00, 0x00	// value: 1
	};
	fwrite(".data", 1, 5+1, fp);
	unsigned int offset = 4*1 + 4; // 4 * Amount + 4
	fwrite(&offset, sizeof(unsigned int), 1, fp);
	fwrite(ds, 1, offset, fp);

	// CODE Section
	uint16 lencs = 0x16+1;	// Amount of codes
	POX_CODE cs[]={
		/* a <= 0x10
		 * b <= 0x11
		 * i <= 0x12
		 * 1 <= 0x13
		 */
	/*00*/	{CALL,	0x03}, // call main		`.	main
	/*01*/	{CALL,	0x03}, // call main		 >	main
	/*02*/	{HALT,	0x00}, // halt			/	end
		// main:								func main:
	/*03*/	{IN,	0x00}, // in			`.	a = input
	/*04*/	{POP,	0x10}, // pop a			/
		// while:05							`.
	/*05*/	{IN,	0x00}, // in			 |	death:
	/*06*/	{POP,	0x11}, // pop b			 |		b = input
	/*07*/	{PUSH,	0x10}, // push a		  >		if a = b break
	/*08*/	{PUSH,	0x11}, // push b		 |	;
	/*09*/	{EQ,	0x00}, // eq			 |
	/*0A*/	{JZ,	0x05}, // jz while		/
	/*0B*/	{PUSH,	0x13}, // push 1		`.
	/*0C*/	{POP,	0x12}, // pop i			 |
		// for:0D							 |
	/*0D*/	{PUSH,	0x12}, // push i		 `.	for i in [1, a]:
	/*0E*/	{PUSH,	0x10}, // push a		 /
	/*0F*/	{GT,	0x00}, // gt			 |
	/*10*/	{NOT,	0x00}, // not			 |
	/*11*/	{JZ,	0x16}, // jz for_end	/
	/*12*/	{PUSH,	0x12}, // push i		`.		print i
	/*13*/	{OUT,	0x00}, // out			/
	/*14*/	{INC,	0x12}, // inc i			`.
	/*15*/	{JMP,	0x0D}, // jmp for		 |	;
		// for_end:16						/
	/*16*/	{RET,	0x00}, // ret				ret;
	};
	fwrite(".code", 1, 5+1, fp);
	offset = 3*lencs + 2; // 3 * Amount + 2
	fwrite(&offset, sizeof(unsigned int), 1, fp);
	fwrite(&lencs, sizeof(uint16), 1, fp);
	int i;
	for (i=0; i<lencs; i++){
		fwrite(&cs[i].code, sizeof(byte), 1, fp);
		fwrite(&cs[i].data, sizeof(uint16), 1, fp);
	}

	fclose(fp);
	return 0;
}
