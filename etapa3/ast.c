#include "ast.h"

FILE *yyout;

// funcao para a criação de um novo nodo
AST *criarNodo(int tipo, HASH_ELEMENT *simbolo, ListNode children) {
	AST *nodo;
	nodo 						= (AST*) calloc(1, sizeof(AST));
	nodo->tipo    	= tipo;
	nodo->simbolo 	= simbolo;
	nodo->childList	= children;
	
	return nodo;
}

void imprimeArvore(AST *raiz) { 
	


}


