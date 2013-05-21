/*

   main.c

*/
#include <stdio.h>
#include <stdlib.h>
#include "hash.c"

extern FILE* yyin;
extern FILE* yyout;
extern char* yytext;
extern int numeroLinha;

/*
void initMe(void) {
	hash_init();
}
*/
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

int main (int argc, char **argv) {
  
  // verifica validade dos parâmetros de entrada
  if(argc < 3) {
		printf("Use main <input_file_name> <output_file_name>\n");
		exit(1);
	}
	
	// inicia a tabela hash
	hash_init();
	
	// inicializa arquivos para leitura/escrita
	yyin  = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");
	
	// chama o parser...
  yyparse();
  
  // fecha os arquivos
  fclose(yyin);
  fclose(yyout);

  exit(0);
}

