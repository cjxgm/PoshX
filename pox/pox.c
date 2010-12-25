#include <stdio.h>
#include <string.h>
#include "pox.h"

void pox_load(char* filename, POX* pox){
	int i;

	FILE* fp = fopen(filename, "rb");

	// Check filetype and version
	byte hdr[4]; // Pox Header
	fread(hdr, sizeof(byte), 4, fp);
	for (i=0; i<3; i++) if (hdr[i] != "POX"[i])
		#ifdef __DEBUG__
		THROW(true, "Filetype mismatch!");
		#else
		THROW(ERR_FILETYPE_MISMATCH);
		#endif
	if (hdr[3] != POX_VERSION)
		#ifdef __DEBUG__
		THROW(true, "Version mismatch!");
		#else
		THROW(ERR_VERSION_MISMATCH);
		#endif

	// Read sections
	while(!feof(fp)){
		/* It seems that fscanf has a bug which my crash the app when
		 * the data is longer than the length of the string?
		 * So I would like to write it myself instead of fscanf.
		 */
		char sec_name[21] = {0};
		for (i=0; i<20; i++) 
			if ((sec_name[i] = fgetc(fp)) == 0) break;
		uint32 sec_len;
		fread(&sec_len, sizeof(uint32), 1, fp);

		if (strcmp(sec_name, ".code") == 0){
			fread(&pox->lencs, sizeof(uint16), 1, fp);
			pox->cs = calloc(sizeof(POX_CODE), pox->lencs);
			fread(pox->cs, sizeof(POX_CODE), pox->lencs, fp);
			#ifdef __DEBUG__
			char msg[20];
			sprintf(msg, "%d", pox->lencs);
			THROW(false, msg);
			for (i=0; i<pox->lencs; i++){
				sprintf(msg, "0x%2.2X\t%4.4X", pox->cs[i].code, pox->cs[i].data);
				THROW(false, msg);
			}
			#endif
		}
		else if (strcmp(sec_name, ".data") == 0){
			fseek(fp, sec_len, SEEK_CUR);
		}
		else {
			fseek(fp, sec_len, SEEK_CUR);
			#ifdef __DEBUG__
			char err_msg[40];
			sprintf(err_msg, "Unknown section: %s", sec_name);
			THROW(false, err_msg);
			#else
			ERROR(ERR_UNKNOWN_SECTION);
			#endif
		}
	}
}

void pox_run(POX* pox){
	printf("[POX_RUN] Done.\n");
}
