/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include <stdio.h>
#include "tokens.h"

extern FILE *yyin;

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s\n", mensagem);
}

int main (int argc, char **argv)
{
  int resultado = yyparse();
  return resultado;
}

