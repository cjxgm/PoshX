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
		0x03, 0x00,	// There is 2 variable
		0x01, 0x00, // There is 1 value
		0x01, 0x00, 0x00, 0x00	// value: 1
	};
	fwrite(".data", 1, 5+1, fp);
	unsigned int offset = 4*1 + 4; // 4 * Amount + 4
	fwrite(&offset, sizeof(unsigned int), 1, fp);
	fwrite(ds, 1, offset, fp);

	// CODE Section
	uint16 lencs = 0x13+1;	// Amount of codes
	POX_CODE cs[]={
		/* a <= 0x10
		 * b <= 0x11
		 * i <= 0x12
		 * 1 <= 0x13
		 */
	/*00*/	{IN,	0x00}, // in			`.	a = input
	/*01*/	{POP,	0x10}, // pop a			/
		// while:02							`.
	/*02*/	{IN,	0x00}, // in			 |	death:
	/*03*/	{POP,	0x11}, // pop b			 |		b = input
	/*04*/	{PUSH,	0x10}, // push a		  >		if a = b break
	/*05*/	{PUSH,	0x11}, // push b		 |	;
	/*06*/	{EQ,	0x00}, // eq			 |
	/*07*/	{JZ,	0x02}, // jz while		/
	/*08*/	{PUSH,	0x13}, // push 1		`.
	/*09*/	{POP,	0x12}, // pop i			 |
		// for:0A							 |
	/*0A*/	{PUSH,	0x12}, // push i		 `.	for i in [1, a]:
	/*0B*/	{PUSH,	0x10}, // push a		 /
	/*0C*/	{GT,	0x00}, // gt			 |
	/*0D*/	{NOT,	0x00}, // not			 |
	/*0E*/	{JZ,	0x13}, // jz for_end	/
	/*0F*/	{PUSH,	0x12}, // push i		`.		print i
	/*10*/	{OUT,	0x00}, // out			/
	/*11*/	{INC,	0x12}, // inc i			`.
	/*12*/	{JMP,	0x0A}, // jmp for		 |	;
		// for_end:							/
	/*13*/	{HALT,	0x00}, // halt
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
