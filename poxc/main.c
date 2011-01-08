#include <stdio.h>
#include <assert.h>
#include "poxc.h"

int main(int argc, char* argv[]){
	assert(argc==3);

	FILE* fpin = fopen(argv[1], "r");
	FILE* fpout = fopen(argv[2], "wb");
	poxc_compile(fpin, fpout);
	fclose(fpin);
	fclose(fpout);

	return error;
}
