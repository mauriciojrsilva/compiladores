#ifndef HASH_H
#define HASH_H

#include <stdio.h>

#define SIMBOLO_LIT_INTEIRO              1
#define SIMBOLO_LIT_FLUTUANTE            2
#define SIMBOLO_LIT_VERDADEIRO           3
#define SIMBOLO_LIT_FALSO                4
#define SIMBOLO_LIT_CHAR                 5
#define SIMBOLO_LIT_CADEIA               6
#define SIMBOLO_IDENTIFICADOR            7
#define SIMBOLO_VARIAVEL                 8
#define SIMBOLO_VETOR                    9
#define SIMBOLO_FUNCAO                  10
#define SIMBOLO_PARAM                   11

#define TIPODADO_INTEIRO                1
#define TIPODADO_FLUTUANTE              2
#define TIPODADO_CHAR                   3
#define TIPODADO_BOOLEANO               4
#define TIPODADO_CADEIA                 5

typedef struct hash_t {
        int token;
        int tipoDado;
        struct AST *ast;
        char *text;
        struct hash_t *next;
} HASH_ELEMENT;

void hash_init();
HASH_ELEMENT* hash_insert(int token, char *text);
int hash_address(char *text);
HASH_ELEMENT* hash_find(char *text);
void hash_print();

#endif