/*
 * gen.c - Binary generator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gen(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	char *token;
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
		}
		else{
			// NOP
			if(strcmp(string, "nop\n")==0){
				fputc(144, target);
			}
			// WAIT/FWAIT
			if(strcmp(string, "wait\n")==0 || strcmp(string, "fwait\n")==0){
				fputc(155, target);
			}
			// LODSB
			if(strcmp(string, "lodsb\n")==0){
				fputc(172, target);
			}
			// LODSW
			if(strcmp(string, "lodsw\n")==0){
				fputc(173, target);
			}
			// RET
			if(strcmp(string, "ret\n")==0){
				fputc(195, target);
			}
			// INT3
			else if(strcmp(string, "int3\n")==0){
				fputc(204, target);
			}
			// INT
			else if(strcmp(string, "int\n")==0){
				fputc(205, target);
				fgets(string, sizeof(string), source);
				int val = atoi(string);
				fputc(val, target);
			}
			// PAUSE
			else if(strcmp(string, "pause\n")==0){
				fputc(243, target);
				fputc(144, target);
			}
			// HLT
			else if(strcmp(string, "hlt\n")==0){
				fputc(244, target);
			}
			// CLI
			else if(strcmp(string, "cli\n")==0){
				fputc(250, target);
			}
			// STI
			else if(strcmp(string, "sti\n")==0){
				fputc(251, target);
			}
			// CLD
			else if(strcmp(string, "cld\n")==0){
				fputc(252, target);
			}
			// STD
			else if(strcmp(string, "std\n")==0){
				fputc(253, target);
			}
			else{
				;
			}
		}
	}
	fclose(source);
	fclose(target);
}
