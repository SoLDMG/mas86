/*
 *   gen.c - Binary generator.
 *  Copyright (C) 2014  Thijs van der Woude

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/instr.h"

int gen(char *input, char *output, char *map){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	FILE *something = fopen(map, "r");
	char string[256];
	char *token;
	int val;
	int bits = 16;		// Like NASM, mas86 always assumes that it starts in 16-bit mode.
	int origin = 0;
	while(fgets(string, sizeof(string), source) !=NULL){
		if(string[0]=='.'){
			if(strcmp(string, ".ascii\n")==0){
				fgets(string, sizeof(string), source);
				token = strtok(string, "\n\0");
				fprintf(target, "%s", token);
			}
			else if(strcmp(string, ".asciz\n")==0){
				fgets(string, sizeof(string), source);
				token = strtok(string, "\n\0");
				fprintf(target, "%s", token);
				fputc(0, target);
			}
			else if(strcmp(string, ".dec\n")==0){
				fgets(string, sizeof(string), source);
				int val = atoi(string);
				fputc(val, target);
			}
			else if(strcmp(string, ".hex\n")==0){
				int val;
				fscanf(source, "%x", &val);
				if(val<256){
					fputc(val, target);
				}
				else{
					printf("can't do this yet\n");
				}
			}
			else if(strcmp(string, ".org\n")==0){
				fgets(string, sizeof(string), source);
				int val = atoi(string);
				origin = val;
			}
			else if(strcmp(string, ".fill\n")==0){
				fgets(string, sizeof(string), source);
				int times = atoi(string);
				fgets(string, sizeof(string), source);
				int val = atoi(string);
				int x = 1;
				while(x<=times){
					fputc(val, target);
					x++;
				}
			}
			else if(strcmp(string, ".bits16\n")==0){
				bits = 16;
			}
			else if(strcmp(string, ".bits32\n")==0){
				bits = 32;
			}
			else if(strcmp(string, ".bits64\n")==0){
				bits = 64;
			}
		}
		else{
			/*
			 * !!! *** NOTE: ALL of the *_VAL definitions are located in "include/instr.h" *** !!!
			 */

			// PUSHA
			if(strcmp(string, "pusha\n")==0){
				if(bits==64){
					printf("as: pusha not supported in 64-bit mode\n");
				}
				else{
					fputc(PUSHA_VAL, target);
				}
			}
			// POPA
			if(strcmp(string, "popa\n")==0){
				if(bits==64){
					printf("as: popa not supported in 64-bit mode\n");
				}
				else{
					fputc(POPA_VAL, target);
				}
			}
			// NOP
			if(strcmp(string, "nop\n")==0){
				fputc(NOP_VAL, target);
			}
			// WAIT/FWAIT
			if(strcmp(string, "wait\n")==0 || strcmp(string, "fwait\n")==0){
				fputc(WAIT_VAL, target);
			}
			// LODSB
			if(strcmp(string, "lodsb\n")==0){
				fputc(LODSB_VAL, target);
			}
			// LODSW
			if(strcmp(string, "lodsw\n")==0){
				fputc(LODSW_VAL, target);
			}
			// MOV
			if(strcmp(string, "mov\n")==0){
				fgets(string, sizeof(string), source);
				if(strcmp(string, "ah\n")==0){
					fputc(180, target);
					fgets(string, sizeof(string), source);
					if(string[0]=='0' || string[0]=='1' || string[0]=='2' || string[0]=='3' || string[0]=='4' || string[0]=='5' \
					|| string[0]=='6' || string[0]=='7' || string[0]=='8' || string[0]=='9'){
						val = atoi(string);
						if(val>256){
							printf("as: value too big for register\n");
							exit(0);
						}
						else{
							fputc(val, target);
						}
					}
					else{
						fgets(string, sizeof(string), source);
						printf("can't do this yet\n");
					}
				}
				if(strcmp(string, "al\n")==0){
					fputc(176, target);
					fgets(string, sizeof(string), source);
					if(string[0]=='0' || string[0]=='1' || string[0]=='2' || string[0]=='3' || string[0]=='4' || string[0]=='5' \
					|| string[0]=='6' || string[0]=='7' || string[0]=='8' || string[0]=='9'){
						val = atoi(string);
						if(val>256){
							printf("as: value too big for register\n");
							exit(0);
						}
						else{
							fputc(val, target);
						}
					}
					else{
						fgets(string, sizeof(string), source);
						printf("can't do this yet\n");
					}
				}
				else if(strcmp(string, "ax\n")==0){
					fgets(string, sizeof(string), source);
					if(string[0]=='0' || string[0]=='1' || string[0]=='2' || string[0]=='3' || string[0]=='4' || string[0]=='5' \
					|| string[0]=='6' || string[0]=='7' || string[0]=='8' || string[0]=='9'){
						fputc(184, target);
						val = atoi(string);
						if(val<256){
							fputc(val, target);
							fputc(0, target);
						}
						else{
							printf("cant do this yet\n");
						}
					}
					else{
						fputc(137, target);
						if(strcmp(string, "ax\n")==0){
							fputc(192, target);
						}
						if(strcmp(string, "bx\n")==0){
							fputc(216, target);
						}
						if(strcmp(string, "cx\n")==0){
							fputc(200, target);
						}
						if(strcmp(string, "dx\n")==0){
							fputc(208, target);
						}
					}
				}
				else if(strcmp(string, "bx\n")==0){
					fgets(string, sizeof(string), source);
					if(string[0]=='0' || string[0]=='1' || string[0]=='2' || string[0]=='3' || string[0]=='4' || string[0]=='5' \
					|| string[0]=='6' || string[0]=='7' || string[0]=='8' || string[0]=='9'){
						fputc(187, target);
						val = atoi(string);
						if(val<256){
							fputc(val, target);
							fputc(0, target);
						}
						else{
							printf("cant do this yet\n");
						}
					}
					else{
						fputc(137, target);
						if(strcmp(string, "ax\n")==0){
							fputc(195, target);
						}
						if(strcmp(string, "bx\n")==0){
							fputc(219, target);
						}
						if(strcmp(string, "cx\n")==0){
							fputc(203, target);
						}
						if(strcmp(string, "dx\n")==0){
							fputc(211, target);
						}
					}
				}
				else if(strcmp(string, "cx\n")==0){
					fgets(string, sizeof(string), source);
					if(string[0]=='0' || string[0]=='1' || string[0]=='2' || string[0]=='3' || string[0]=='4' || string[0]=='5' \
					|| string[0]=='6' || string[0]=='7' || string[0]=='8' || string[0]=='9'){
						fputc(185, target);
						val = atoi(string);
						if(val<256){
							fputc(val, target);
							fputc(0, target);
						}
						else{
							printf("cant do this yet\n");
						}
					}
					else{
						fputc(137, target);
						if(strcmp(string, "ax\n")==0){
							fputc(193, target);
						}
						if(strcmp(string, "bx\n")==0){
							fputc(217, target);
						}
						if(strcmp(string, "cx\n")==0){
							fputc(201, target);
						}
						if(strcmp(string, "dx\n")==0){
							fputc(209, target);
						}
					}
				}
				else if(strcmp(string, "dx\n")==0){
					fgets(string, sizeof(string), source);
					if(string[0]=='0' || string[0]=='1' || string[0]=='2' || string[0]=='3' || string[0]=='4' || string[0]=='5' \
					|| string[0]=='6' || string[0]=='7' || string[0]=='8' || string[0]=='9'){
						fputc(186, target);
						val = atoi(string);
						if(val<256){
							fputc(val, target);
							fputc(0, target);
						}
						else{
							printf("cant do this yet\n");
						}
					}
					else{
						fputc(137, target);
						if(strcmp(string, "ax\n")==0){
							fputc(194, target);
						}
						if(strcmp(string, "bx\n")==0){
							fputc(218, target);
						}
						if(strcmp(string, "cx\n")==0){
							fputc(202, target);
						}
						if(strcmp(string, "dx\n")==0){
							fputc(210, target);
						}
					}
				}
			}
			// RET
			if(strcmp(string, "ret\n")==0){
				fputc(RET_VAL, target);
			}
			// INT3
			else if(strcmp(string, "int3\n")==0){
				fputc(INT3_VAL, target);
			}
			// INT
			else if(strcmp(string, "int\n")==0){
				fputc(INT_VAL, target);
				fgets(string, sizeof(string), source);
				val = atoi(string);
				fputc(val, target);
			}
			// FNOP
			else if(strcmp(string, "fnop\n")==0){
				fputc(FNOP1_VAL, target);
				fputc(FNOP2_VAL, target);
			}
			// FDECSTP
			else if(strcmp(string, "fdecstp\n")==0){
				fputc(FDECSTP1_VAL, target);
				fputc(FDECSTP2_VAL, target);
			}
			// FINCSTP
			else if(strcmp(string, "fincstp\n")==0){
				fputc(FINCSTP1_VAL, target);
				fputc(FINCSTP2_VAL, target);
			}
			// CPUID
			else if(strcmp(string, "cpuid\n")==0){
				fputc(CPUID1_VAL, target);
				fputc(CPUID2_VAL, target);
			}
			// PAUSE
			else if(strcmp(string, "pause\n")==0){
				fputc(PAUSE1_VAL, target);
				fputc(PAUSE2_VAL, target);
			}
			// HLT
			else if(strcmp(string, "hlt\n")==0){
				fputc(HLT_VAL, target);
			}
			// CLC
			else if(strcmp(string, "clc\n")==0){
				fputc(CLC_VAL, target);
			}
			// STC
			else if(strcmp(string, "stc\n")==0){
				fputc(STC_VAL, target);
			}
			// CLI
			else if(strcmp(string, "cli\n")==0){
				fputc(CLI_VAL, target);
			}
			// STI
			else if(strcmp(string, "sti\n")==0){
				fputc(STI_VAL, target);
			}
			// CLD
			else if(strcmp(string, "cld\n")==0){
				fputc(CLD_VAL, target);
			}
			// STD
			else if(strcmp(string, "std\n")==0){
				fputc(STD_VAL, target);
			}
			else{
				;
			}
		}
	}
	printf("%d\n", origin);
	fclose(source);
	fclose(target);
}
