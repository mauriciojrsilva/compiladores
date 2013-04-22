/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include <stdio.h>

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

void yyerror(char const *mensagem) {
  fprintf(stderr, "Syntax Error on line %d\n", getLineNumber());
  exit(1);
}

int main (int argc, char **argv)
{
  int resultado = yyparse();
  printf("\nPrinting hash ...\n");
  hash_print();
  return resultado;
}

