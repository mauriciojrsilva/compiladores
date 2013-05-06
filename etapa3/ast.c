#include "ast.h"

// funcao para a criação de um novo nodo
AST *criarNodo(int tipo, HASH_ELEMENT *simbolo, AST *f0, AST *f1, AST *f2, AST *f3) {
	AST *nodo;
	nodo 						= (AST*) calloc(1, sizeof(AST));
	nodo->tipo    	= tipo;
	nodo->simbolo 	= simbolo;
	nodo->filhos[0] = f0;
	nodo->filhos[1] = f1;
	nodo->filhos[2] = f2;
	nodo->filhos[3] = f3;
return nodo;
}

void imprimeArvore(AST *raiz) { 
	


}


