#include "poxc.h"

void poxc_compile(FILE* fpin, FILE* fpout){
	fprintf(fpout, MAGIC_LINE);
	lex(fpin);
	if (error) return;
	/*parse();
	if (error) return;
	writeds();
	writecs();*/
}

/** Lexical Analyze
 */
void lex(FILE* fp){
}
