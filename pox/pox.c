/** Posh X Virtual Machine
 * by eXerigumo Clanjor
 * Copyleft (C) Clan Open Studio, 2010-2011.
 */
#include <stdio.h>
#include <string.h>
#include "pox.h"
#include "opcode.h"

void pox_load(char* filename, pox_t* pox)
{
	ERROR(0); // Clear last error
	int i;

	FILE* fp = fopen(filename, "rb");

	// Skip the magic line
	char ch;
	while((ch=fgetc(fp)) != '\n') if (ch == EOF) break; 

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
		if (sec_name[0] == EOF) break;
		uint4 sec_len;
		fread(&sec_len, sizeof(uint4), 1, fp);

		if (strcmp(sec_name, ".code") == 0){
			/*********** .code section format **********
			 * ".code" uint4    uint2       (byte   uint2*amount)*amount
			 * `------v-----'    `-v--'        `-v-'  `----v-----'
			 *  section hdr    code amount     code   data address
			 */
			fread(&pox->lencs, sizeof(uint2), 1, fp);
			pox->cs = calloc(sizeof(pox_code_t), pox->lencs);
			/** fread(pox->cs, sizeof(pox_code_t), pox->lencs, fp);
			 * It doesn't work! Fuck! How to pack memory??
			 */
			for(i=0; i<pox->lencs; i++){
				fread(&pox->cs[i].code, sizeof(byte), 1, fp);
				fread(&pox->cs[i].data, sizeof(uint2), 1, fp);
			}
			#ifdef __DEBUG__
			COLOR_GREEN_BOLD;
			printf("[CODE: %d]\n", pox->lencs);
			COLOR_RESET;
			for (i=0; i<pox->lencs; i++){
				printf("\t%4.4Xh  %2.2Xh  %4.4Xh\n", i, pox->cs[i].code, pox->cs[i].data);
			}
			#endif
		}
		else if (strcmp(sec_name, ".data") == 0){
			/*********** .data section format **********
			 * ".data" uint4     uint2          uint2       int4*amount
			 * `------v-----'     `-v--'          `-v--'       `----v-----'
			 *  section hdr   variable amount   value amount    value data
			 */
			uint2 vc; // How many variables?
			fread(&vc, sizeof(uint2), 1, fp);
			fread(&pox->lends, sizeof(uint2), 1, fp);
			vc += 0x10; // 0x10 for registers
			pox->lends += vc;
			pox->ds = calloc(sizeof(pox_code_t), pox->lends);
			for (i=vc; i<pox->lends; i++)
				fread(&pox->ds[i], sizeof(int4), 1, fp);
			#ifdef __DEBUG__
			COLOR_GREEN_BOLD;
			printf("[DATA: %d]\n", pox->lends);
			COLOR_RESET;
			for (i=0; i<pox->lends; i++){
				printf("\t%4.4Xh  %8.8Xh\n", i, pox->ds[i]);
			}
			#endif

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

void pox_run(pox_t* pox)
{
	ERROR(0); // Clear last error
	#ifdef __DEBUG__
	COLOR_GREEN_BOLD;
	printf("[POX_RUN] ");
	COLOR_RESET;
	printf("Begin.\n");
	#endif
	while(1){
		if (pox->ip >= pox->lencs)
			#ifdef __DEBUG__
			THROW(true, "Unexpected halted.");
			#else
			THROW(ERR_UNEXPECTED_HALTED);
			#endif
		pox_run_once(pox);
		if (error == ERR_HALT) break;
		if (error) return;
	}
	#ifdef __DEBUG__
	COLOR_GREEN_BOLD;
	printf("[POX_RUN] ");
	COLOR_RESET;
	printf("Done.\n");
	#endif
}
void pox_run_once(pox_t* pox)
{
	ERROR(0); // Clear last error
	#define CODE pox->cs[pox->ip].code
	#define ADDR pox->cs[pox->ip].data
	#define DATA pox->ds[ADDR]
	char msg[20];
	int4 tempi, tempj;
	switch(CODE){
	case NOP: break;

	case PUSH:
		stack_push(&pox->data_stack, DATA);
		break;
	case POP:
		stack_pop(&pox->data_stack, &DATA);
		break;
	case POPA:
		while(!error)
			stack_pop(&pox->data_stack, &DATA);
		ERROR(0);
		break;

	case JMP:
		pox->ip = ADDR-1;
		break;
	case JZ:
		stack_pop(&pox->data_stack, &tempi);
		if (!tempi) pox->ip = ADDR-1;
		break;
	case CALL:
		stack_push(&pox->call_stack, pox->ip);
		pox->ip = ADDR-1;
		break;
	case CZ:
		stack_pop(&pox->data_stack, &tempi);
		if (!tempi){
			stack_push(&pox->call_stack, pox->ip);
			pox->ip = ADDR-1;
		}
		break;
	case RET:
		stack_pop(&pox->call_stack, &tempi);
		pox->ip = (uint2) tempi;
		break;

	case INC:
		if (ADDR) DATA++;
		else{
			stack_pop(&pox->data_stack, &tempi);
			tempi++;
			stack_push(&pox->data_stack, tempi);
		}
		break;
	case DEC:
		if (ADDR) DATA--;
		else{
			stack_pop(&pox->data_stack, &tempi);
			tempi--;
			stack_push(&pox->data_stack, tempi);
		}
		break;
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD:
		stack_pop(&pox->data_stack, &tempj);
		stack_pop(&pox->data_stack, &tempi);
		switch(CODE){
		case ADD: tempi+=tempj; break;
		case SUB: tempi-=tempj; break;
		case MUL: tempi*=tempj; break;
		case DIV: tempi/=tempj; break;
		case MOD: tempi%=tempj; break;
		}
		stack_push(&pox->data_stack, tempi);
		break;

	case GT:
	case LT:
	case EQ:
	case AND:
	case OR:
		stack_pop(&pox->data_stack, &tempj);
		stack_pop(&pox->data_stack, &tempi);
		switch(CODE){
			case GT: tempi = (tempi>tempj); break;
			case LT: tempi = (tempi<tempj); break;
			case EQ: tempi = (tempi==tempj); break;
			case AND: tempi = (tempi&&tempj); break;
			case OR: tempi = (tempi||tempj); break;
		}
		stack_push(&pox->data_stack, tempi);
		break;
	case NOT:
		if (ADDR) DATA = !DATA;
		else{
			stack_pop(&pox->data_stack, &tempi);
			tempi = !tempi;
			stack_push(&pox->data_stack, tempi);
		}
		break;

	case IN:
		COLOR_BLUE_BOLD;
		printf(">>>>> ");
		COLOR_RESET;
		scanf("%d", &tempi);
		stack_push(&pox->data_stack, tempi);
		break;
	case OUT:
		stack_pop(&pox->data_stack, &tempi);
		COLOR_GREEN_BOLD;
		printf("[OUT] ");
		COLOR_RESET;
		printf("%d\n", tempi);
		break;

	case HALT:
		ERROR(ERR_HALT);
		break;

	default:
		#ifdef __DEBUG__
		sprintf(msg, "Unknown code: %2.2Xh", CODE);
		THROW(true, msg);
		#else
		THROW(ERR_UNKNOWN_CODE);
		#endif
	}
	pox->ip++;
	#undef DATA
	#undef ADDR
	#undef CODE
}
