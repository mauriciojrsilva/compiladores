/*
   
   Etapa 1 - Analisador Léxico
   
   Lucas Lazari da Silva
   Diogo Dadalt
   Mauricio Jaspe 
   
*/
#include <stdio.h>
#include "tokens.h"

extern FILE *yyin;

int running;

int main (int argc, char **argv)
{
	// inicia a hash table	
	initMe();
	
  	int token = yylex();
	
	while (running) {
    	printf ("token  %d - linha %d\n", token, getLineNumber());
    	token = yylex();
  	}

  	hash_print();

  	return 0;
}
