/*
 * main.c - Main C file.
 */

int main(int argc, char **argv){
	prep_pass1(argv[1], argv[2]);
	prep_pass2(argv[2], argv[3]);
	prep_pass3(argv[3], argv[4]);
	lex(argv[4], argv[5]);
	clear_newlines(argv[5], argv[6]);
	gen(argv[6], argv[7]);
	return 0;
}
