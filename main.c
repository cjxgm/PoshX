/** main.c
 * 
 **
 * This file is a part of PoshX project.
 * Under GPLv3. See COPYING for more details.
 * NO WARRANTY!
 **
 * AUTHORS:
 *		eXerigumo Clanjor
 */

#include <string.h>
#include "poshx.h"

void show_help();

int main(int argc, char * argv[])
{
	bool compile_mode = false; // true => compile; false => run
	const char * input_file = NULL;
	const char * output_file = "a.pox";

#define SHIFT { argc--; argv++; }
	while(argc>1){
		// Is it an option or an input file?
		if (argv[1][0] == '-'){
			// Compile
			if (strcmp(argv[1], "-c") == 0){
				compile_mode = true;
				SHIFT;
			}

			// Output_file
			else if (strcmp(argv[1], "-o") == 0){
				compile_mode = true; // It must be compile mode
				SHIFT;
				output_file = argv[1];
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
		debug("[COMPILE]");
		debug("\tinput file: %s", input_file);
		debug("\toutput file: %s", output_file);
		poxc_compile_file(input_file, output_file);
	}

	// Run
	else {
		POX * pox = pox_load_file(input_file); 
		pox_run(pox);
		pox_free(pox);
	}
	return 0;
}

void show_help(const char * name)
{
#define NORMAL "\033[0m"
#define RED_BOLD "\033[01;31m"
#define GREEN_BOLD "\033[01;32m"
#define YELLOW_BOLD "\033[01;33m"
#define PURPLE_BOLD "\033[01;35m"

	// Header
	printf("%sPosh X 10.%d\n", PURPLE_BOLD, POX_VERSION);
	printf("%sUnder GPLv3. %sNO WARRANTY!\n", NORMAL, RED_BOLD);
	printf("\n");

	// Syntax
	printf("%s%s ", RED_BOLD, name);
	printf("%s[%s--help%s] ", NORMAL, RED_BOLD, NORMAL);
	printf("[%s-h%s] ", RED_BOLD, NORMAL);
	printf("[%s-c%s] ", RED_BOLD, NORMAL);
	printf("[%s-o %soutput_file%s] ", RED_BOLD, GREEN_BOLD, NORMAL);
	printf("%sinput_file%s\n", GREEN_BOLD, NORMAL);

	// --help, -h
	printf("\t%s-h, --help\n", RED_BOLD);
	printf("%s\t\tShow this help.\n", NORMAL);

	// -c
	printf("\t%s-c\n", RED_BOLD);
	printf("%s\t\tCompile the input_file rather than run it.\n", NORMAL);

	// -o output_file
	printf("\t%s-o %soutput_file\n", RED_BOLD, GREEN_BOLD);
	printf("%s\t\tSpecify the output file. Automatically specify -c.\n", NORMAL);

	// input_file
	printf("\t%sinput_file\n", GREEN_BOLD);
	printf("\t\t%sJust as its name.\n", NORMAL);
	printf("\n");
	printf("%sCopyleft (C) Clanjor Productions, 2010-2011.\n", YELLOW_BOLD);
	printf(NORMAL);
}

