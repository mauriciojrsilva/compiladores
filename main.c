/*
   main.c

   Arquivo principal do analisador léxico.
*/
#include <stdio.h>
#include "tokens.h"

extern FILE *yyin;

int getLineNumber (void)
{
	return 0;
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
