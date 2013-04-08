/*
   main.c

   Arquivo principal do analisador léxico.
*/
#include <stdio.h>
#include "tokens.h"

extern FILE* yyin;
extern char* yytext;
extern int numeroLinha;

void initMe(void) {
	hash_init();
}

int yywrap(void){
	return 1;
}

int getLineNumber(void) {
	return numeroLinha;
}

int main (int argc, char **argv)
{
  	int token;

  	while (token = yylex())
    	printf ("token < %d, %s > at line %d\n", token, yytext, getLineNumber());

  	hash_print();

  	return 0;
}
