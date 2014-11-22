/*
 * misc.c - Miscellanious functions.
 */

#include <stdio.h>

int clear_newlines(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	while(fgets(string, sizeof(string), source) !=NULL){
		if(string[0]=='\n'){
			;
		}
		else{
			fprintf(target, string);
		}
	}
	fclose(source);
	fclose(target);
}
