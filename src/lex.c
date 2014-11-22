/*
 * lex.c - The lexer.
 */

#include <stdio.h>
#include <string.h>

int lex(char *input, char *output){
	FILE *source = fopen(input, "r");
	FILE *target = fopen(output, "w");
	char string[256];
	char *token;
	while(fgets(string, sizeof(string), source) !=NULL){
		if(string[0]=='.'){
			if(string[1]=='b' || string[1]=='o' || string[1]=='h' || string[1]=='d' || string[1]=='i' || string[1]=='f'){
				token = strtok(string, " ,");
				while(token !=NULL){
					fprintf(target, "%s\n", token);
					token = strtok(NULL, " ,");
				}
			}
			if(string[1]=='a'){
				token = strtok(string, " ,");
				while(token !=NULL){
					fprintf(target, "%s\n", token);
					token = strtok(NULL, " ,");
				}
				fgets(string, sizeof(string), source);
				fprintf(target, string);
			}
		}
		else{
			token = strtok(string, " ,");
			while(token !=NULL){
				fprintf(target, "%s\n", token);
				token = strtok(NULL, " ,");
			}
		}
	}
	fclose(source);
	fclose(target);
}
