#include "astree.h"

void verificaDeclaracoes(AST *raiz) {
	if (raiz == 0) return;
	
	// deve-se verificar as declarações somente se o nodo da AST for uma declaração (de variável, vetor, função ou parâmetro de função)
	if (raiz->tipo == AST_DECL_VAR || raiz->tipo == AST_DECL_VEC || raiz->tipo == AST_DEF_F || raiz->tipo == AST_PARAM) {
	
		// verifica se foi colocado o nome do identificador
		if (raiz->simbolo == 0) {
    	printf("Linha %d: Declaração de identificador: faltando o nome do identificador.\n", raiz->linha);
    } else {
			
			// inicialmente o elemento da hashtable retorna um token de identificador. se ele não retornar este token, é porque o símbolo já foi definido
			if (raiz->simbolo->token != SIMBOLO_IDENTIFICADOR) {
				printf("Linha %d: Identificador %s já definido.\n", raiz->linha, raiz->simbolo->text);
			}
			
			// define o tipo do símbolo
			switch(raiz->tipo) { 
				case AST_DECL_VAR: 
					raiz->simbolo->token = SIMBOLO_VARIAVEL;
					break;
				case AST_DECL_VEC: 
					raiz->simbolo->token = SIMBOLO_VETOR;
					break;
				case AST_DEF_F: 
					raiz->simbolo->token = SIMBOLO_FUNCAO;
					break;
				case AST_PARAM: 
					raiz->simbolo->token = SIMBOLO_PARAM;
					break;
			}	
	}
	
	// chama recursivamente os filhos para continuar a verificação de declarações...
	for (int i = 0; i < MAX_FILHOS; i++) {
		verificaDeclaracoes(raiz->filhos[i]):	
	}	
}

void verificaUtilizacao(AST *raiz) {
	
	
}

void verificaDados(AST *raiz) {
	

}




void verificaChamadaFuncao() { 
	
}


void verificaListaParam() { 
	
	
}
