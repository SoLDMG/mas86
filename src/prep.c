/*
 * prep.c - The preprocessor.
 */

#include <stdio.h>
#include <string.h>

#define SEPERATORS "\t\n\""
#define STD_COMMENT '!'

// Does some basic tokenizing, needed for the preprocessing.
int prep_pass1(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	char *token;
	while(fgets(string, sizeof(string), source) !=NULL){
		token = strtok(string, SEPERATORS);
		while(token !=NULL){
			fprintf(target, "%s\n", token);
			token = strtok(NULL, SEPERATORS);
		}
	}
	fclose(source);
	fclose(target);
}

// Removes spaces used as whitespace.
int prep_pass2(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	char *token;
	while(fgets(string, sizeof(string), source) !=NULL){
		int c = 0;
		int loop = 0;
		while(loop==0){
			if(string[c] == ' '){
				c++;
			}
			else{
				while(string[c]!='\0'){
					fputc(string[c], target);
					c++;
				}
				loop++;
			}
		}
	}
	fclose(source);
	fclose(target);
}

int prep_pass3(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	char *token;
	int comment_char = STD_COMMENT;
	while(fgets(string, sizeof(string), source) !=NULL){
		int print = 0;
		// If it's just a newline:
		if(string[0] == '\n'){
			print++;
		}
		// If it's a directive:
		if(string[0] == '.'){
			// If it's a comment directive:
			if(string[1] == 'c'){
				comment_char = string[10];
				print++;
			}
			if(string[3] == 's'){
				string[7] = '\n';
			}
			if(string[3] == 'x'){
				string[4] = '\n';
			}
			if(string[3] == 'l'){
				string[5] = '\n';
			}
			if(string[1] == 'o'){
				string[4] = '\n';
			}
			if(string[2] == 'e'){
				string[4] = '\n';
			}
		}
		// If it's a comment:
		if(string[0] == comment_char){
			print++;
		}
		if(print == 0){
			fprintf(target, "%s", string);
		}
	}
	fclose(source);
	fclose(target);
}
