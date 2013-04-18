/*
   main.c

   Arquivo principal do analisador sintático.
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

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s\n", mensagem);
}

int main (int argc, char **argv)
{
  int resultado = yyparse();
  return resultado;
}

