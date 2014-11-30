/*
 *   lex.c - Contains the lexer.
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
