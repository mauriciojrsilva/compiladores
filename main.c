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
  	int token;
	
  	while (token = yylex()) {
    	printf ("token < %d > at %d\n", token, getLineNumber());
  	}
  	
  	return 0;
}
