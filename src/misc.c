/*
 *   misc.c - Contains the miscellanious functions.
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
#include <string.h>

// Functions that main() doesn't call.
int string_length(char *string){
	int size_string = 0;
	while(string[size_string]!='\n'){
		size_string++;
	}
	return size_string;
}

int convert_to_hex(int x){
	char *hex_string;
	sprintf(hex_string, "%x", x);
	printf(hex_string);
}

// This main() actually does use, but I couldn't come up with a better place to put this :(
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

// This as well.
int determine_length(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	int length = 0;
	char *token;
	while(fgets(string, sizeof(string), source) !=NULL){
		int size_string = 0;
		int ch = 0;
		int stop = 0;
		if(string[0]=='.'){
			if(strcmp(string, ".ascii\n")==0){
				fgets(string, sizeof(string), source);
				length = length + string_length(string);
			}
			else if(strcmp(string, ".asciz\n")==0){
				fgets(string, sizeof(string), source);
				length = length + string_length(string) + 1;
			}
		}
		else{
			if( \
			strcmp(string, "ret\n")==0 || \
			strcmp(string, "cli\n")==0 || \
			strcmp(string, "sti\n")==0 || \
			strcmp(string, "clc\n")==0 || \
			strcmp(string, "stc\n")==0 || \
			strcmp(string, "cld\n")==0 || \
			strcmp(string, "std\n")==0 || \
			strcmp(string, "hlt\n")==0 || \
			strcmp(string, "pusha\n")==0 || \
			strcmp(string, "popa\n")==0 || \
			strcmp(string, "lodsw\n")==0 || \
			strcmp(string, "lodsb\n")==0 || \
			strcmp(string, "int3\n")== 0 || \
			strcmp(string, "nop\n")==0
			){
				length++;
			}
			else if( \
			strcmp(string, "int\n")==0 || \
			strcmp(string, "pause\n")==0 || \
			strcmp(string, "fnop\n")==0 || \
			strcmp(string, "cpuid\n")==0 \
			){
				length = length + 2;
				fgets(string, sizeof(string), source);
			}
			else if(strcmp(string, "mov\n")==0){
				fgets(string, sizeof(string), source);
				if(strcmp(string, "ah\n")==0 || strcmp(string, "al\n")==0){
					length = length + 2;
					fgets(string, sizeof(string), source);
				}
				else if(strcmp(string, "dx\n")==0){
					length = length + 3;
					fgets(string, sizeof(string), source);
				}
			}
			else{
				while(string[ch]!='\0' && stop == 0){
					if(string[ch]==':'){
						token = strtok(string, ":");
						fprintf(target, "%s\n", token);
						stop++;
						fprintf(target, "%d\n", length);
					}
					else{
						ch++;
					}
				}
			}
		}
	}
	printf("%d\n", length);
	fclose(source);
	fclose(target);
}
