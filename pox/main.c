#include <stdio.h>
#include <assert.h>
#include "pox.h"

int main(int argc, char* argv[])
{
	assert(argc==2);

	// Init
	pox_t* pox = POX_INIT;

	// Load
	pox_load(argv[1], pox);
	switch(error){
		case 0:
		case ERR_UNKNOWN_SECTION:
			break;
		default:
			return error;
	}
	
	// Run
	pox_run(pox);

	return error;
}
