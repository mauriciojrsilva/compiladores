#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILHOS 4

// estrutura de dados do nodo da árvore sintática abstrata
typedef struct ast_nodo {
	int tipo;
	HASH_ELEMENT *simbolo;
	struct ast_nodo *filhos[MAX_FILHOS];
} AST;

// protótipos das funções
AST criarNodo(int tipo, HASH_ELEMENT *simbolo, AST *f0, AST *f1, AST *f2, AST *f3);

void imprimeArvore(AST *raiz);

