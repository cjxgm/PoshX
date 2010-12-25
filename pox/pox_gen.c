#include <stdio.h>
#include "include/pox.h"

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
		0x01, 0x00,	// There is 1 variable
		0x01, 0x00, // There is 1 value
		0x01, 0x00, 0x00, 0x00	// value: 1
	};
	fwrite(".data", 1, 5+1, fp);
	unsigned int offset = 4*1 + 4; // 4 * Amount + 4
	fwrite(&offset, sizeof(unsigned int), 1, fp);
	fwrite(ds, 1, offset, fp);

	// CODE Section
	uint16 lencs = 9;	// Amount of codes
	POX_CODE cs[]={
		{0x41, 0x0000},	// in
		{0x02, 0x1000},	// pop a  # a=>0x10
		{0x01, 0x1000},	// push a
		{0x01, 0x1100},	// push 1 # 1=>0x11
		{0x22, 0x0000},	// add
		{0x42, 0x0000},	// out
		{0x01, 0x1000},	// push a
		{0x42, 0x0000},	// out
		{0xFF, 0x0000}	// halt
	};
	fwrite(".code", 1, 5+1, fp);
	offset = 3*9 + 2; // 3 * Amount + 2
	fwrite(&offset, sizeof(unsigned int), 1, fp);
	fwrite(&lencs, sizeof(uint16), 1, fp);
	fwrite(cs, sizeof(POX_CODE), 9, fp);

	fclose(fp);
	return 0;
}
