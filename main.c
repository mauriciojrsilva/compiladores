/*
   main.c

   Arquivo principal do analisador léxico.
*/
#include <stdio.h>
#include "tokens.h"

extern FILE*yyin;
extern char* yytext;
extern int running;
extern int numeroLinha;

void initMe(void) {
	hash_init();
}

int yywrap(void){
	running = 0;
	return 1;
}

int getLineNumber(void) {
	return numeroLinha;
}

int main (int argc, char **argv)
{
  	int token = yylex();

  	while (running) {
    	printf ("token  %d - %s linha %d\n", token, yytext, getLineNumber());
    	token = yylex();
  	}

  	hash_print();

  	return 0;
}
