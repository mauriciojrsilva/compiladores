#include <stdio.h>
#include <stdlib.h>

extern "C" FILE* yyin;
extern "C" FILE* yyout;
extern "C" int numeroLinha;
int yyparse (void);

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