/** main.c
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
#include "poshx.h"

void show_help();

int main(int argc, char *argv[])
{
	bool compile_mode = false; // true => compile; false => run
	const char *input_file = NULL;

#define SHIFT { argc--; argv++; }
	while(argc>1){
		// Is it an option or an input file?
		if (argv[1][0] == '-'){
			// Compile
			if (strcmp(argv[1], "-c") == 0){
				compile_mode = true;
				SHIFT;
			}

			// Wrong option
			else {
				show_help(argv[0]);
				return 0;
			}
		}

		// Input file
		else {
			input_file = argv[1];
			SHIFT;
		}
	}

	if (input_file == NULL){
		show_help(argv[0]);
		return 0;
	}

	// Compile
	if (compile_mode){
		// TODO
	}

	// Run
	else {
		pox_t *pox = pox_load_file(input_file); 
		pox_run(pox);
		pox_free(pox);
	}
	return 0;
}

void show_help(const char *name)
{
#define NORMAL "\033[0m"
#define RED "\033[00;31m"
#define RED_BOLD "\033[01;31m"
#define GREEN_BOLD "\033[01;32m"
#define YELLOW_BOLD "\033[01;33m"
#define PURPLE_BOLD "\033[01;35m"

	// Header
	printf("%sPosh X 10.%d\n", PURPLE_BOLD, POX_VERSION);
	printf("%sUnder GPLv3. %sNO WARRANTY!\n", NORMAL, RED);
	printf("\n");

	// Syntax
	printf("%s%s ", RED_BOLD, name);
	printf("%s[%s--help%s] ", NORMAL, RED_BOLD, NORMAL);
	printf("[%s-h%s] ", RED_BOLD, NORMAL);
	printf("[%s-c%s] ", RED_BOLD, NORMAL);
	// Just for the blank area
	printf("%sinput_file%s\n", GREEN_BOLD, NORMAL);

	// --help, -h
	printf("\t%s-h, --help\n", RED_BOLD);
	printf("%s\t\tShow this help.\n", NORMAL);

	// -c
	printf("\t%s-c\n", RED_BOLD);
	printf("%s\t\tCompile the input_file rather than run it.\n", NORMAL);

	// input_file
	printf("\t%sinput_file\n", GREEN_BOLD);
	printf("\t\t%sJust as its name.\n", NORMAL);
	printf("\n");
	printf("%sCopyleft (C) Clan Open Studio.\n", YELLOW_BOLD);
	printf(NORMAL);
}

