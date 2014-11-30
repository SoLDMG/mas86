/*
/*
 *   main.c - Main C source file.
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

int main(int argc, char **argv){
	prep_pass1(argv[1], argv[2]);
	prep_pass2(argv[2], argv[3]);
	prep_pass3(argv[3], argv[4]);
	lex(argv[4], argv[5]);
	clear_newlines(argv[5], argv[6]);
	determine_length(argv[6], argv[7]);
	gen(argv[6], argv[8], argv[7]);
	return 0;
}
