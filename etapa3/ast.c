#include "ast.h"

FILE *yyout;

// funcao para a criação de um novo nodo
AST *criarNodo(int tipo, HASH_ELEMENT *simbolo, ast_list_node childs) {
	AST *nodo;
	nodo 						= (AST*) calloc(1, sizeof(AST));
	nodo->tipo    	= tipo;
	nodo->simbolo 	= simbolo;
	nodo->childs = childs;
	
	return nodo;
}

void imprimeArvore(AST *raiz) { 
	


}


