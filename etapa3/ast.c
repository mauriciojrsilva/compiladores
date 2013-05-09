#include "ast.h"

FILE *yyout;

// funcao para a criação de um novo nodo
AST* criaAST(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos) {
	AST *nodo = (AST*) malloc(sizeof(AST));	
	nodo->tipo = tipo;
	nodo->numFilhos = numFilhos;
	nodo->simbolo = simbolo;
	nodo->filhos	= filhos;	
	return nodo;
}

AST** criaNodos(AST* f1, AST* f2, AST* f3, AST* f4, int numFilhos) {
	int index = 0;
	AST** nodos = (AST**)calloc(numFilhos, sizeof(AST*));
	criaNodo(nodos, f1, &index);
	criaNodo(nodos, f2, &index);
	criaNodo(nodos, f3, &index);
	criaNodo(nodos, f4, &index);
	return nodos;
}

void criaNodo(AST** filhos, AST* filho, int* index) {
	if (filho != NULL) {
		filhos[index] = f1;
		(*index)++;
	}
}

void imprimeArvore(AST *raiz) { 
	// TODO: fazer a função de impressão da árvore
}