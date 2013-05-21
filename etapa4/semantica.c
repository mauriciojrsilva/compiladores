#include "astree.h"

void verificaDeclaracoes(AST *raiz) {
	if (raiz == 0) return;
	
	// deve-se verificar as declarações somente se o nodo da AST for uma declaração (de variável, vetor, função ou parâmetro de função)
	if (raiz->tipo == AST_DECL_VAR || raiz->tipo == AST_DECL_VEC || raiz->tipo == AST_DEF_F || raiz->tipo == AST_PARAM) {
	
		// verifica se foi colocado o nome do identificador
		if (raiz->simbolo == 0) {
    	printf("Linha %d: Declaração de identificador: faltando o nome do identificador.\n", raiz->linha);
    } else {
			
			// inicialmente o elemento da hashtable retorna um token de identificador. se ele retornar um token diferente, é porque o símbolo já foi definido
			if (raiz->simbolo->token != SIMBOLO_IDENTIFICADOR) {
				printf("Linha %d: Identificador %s já definido.\n", raiz->linha, raiz->simbolo->text);
			}
			
			// define o tipo (token) do símbolo
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
	
	// chama recursivamente os filhos para continuar a verificação de declarações de identificadores...
	for (int i = 0; i < MAX_FILHOS; i++) {
		verificaDeclaracoes(raiz->filhos[i]):	
	}	
}

void verificaUtilizacao(AST *raiz) {
	if (raiz == 0) return;
	
	
	// verifica a utilização das variáveis (escalares)
  if (raiz->tipo == AST_SYMBOL || raiz->tipo == AST_ATR_VAR) {
		
		if (raiz->simbolo->token == SIMBOLO_VETOR) {
    	printf("Linha %d: Vetor %s sendo usado como escalar.\n", raiz->linha, raiz->simbolo->text);
    } else if(raiz->simbolo->token == SIMBOLO_FUNCAO) {
    	printf("Linha %d: Função %s sendo usada como escalar.\n", raiz->linha, raiz->simbolo->text);
    } else if (raiz->simbolo->token != SIMBOLO_VARIAVEL && raiz->simbolo->token != SIMBOLO_PARAM) {
    	printf("Linha %d: Variável %s não foi declarada.\n", raiz->linha, raiz->simbolo->text);
    }

	// verifica a utilização dos vetores
	} else if (raiz->tipo == AST_SYMBOL_VEC || raiz->tipo == AST_ATR_VEC) {
 
 		if (raiz->simbolo->token == SIMBOLO_VARIAVEL || raiz->simbolo->token == SIMBOLO_PARAM) {
			printf("Linha %d: Variável %s sendo usada como vetor.\n", raiz->linha, raiz->simbolo->text);
    } else if (raiz->simbolo->token == SIMBOLO_FUNCAO) {
    	printf("Linha %d: Função %s sendo usada como vetor.\n", raiz->linha, raiz->simbolo->text);
    } else if (raiz->simbolo->token != SIMBOLO_VETOR){
    	printf("Linha %d: Vetor %s não foi declarado.\n", raiz->linha, raiz->simbolo->text);
    }
  
  // verifica a utilização das funções
 	} else if (raiz->tipo == AST_CHAM_F) { 
		
		if (raiz->simbolo->token == SIMBOLO_VARIAVEL || raiz->simbolo->token == SIMBOLO_PARAM) {
			printf("Linha %d: Variável %s sendo usada como função.\n", raiz->linha, raiz->simbolo->text);
		} else if (raiz->simbolo->token == SIMBOLO_VETOR) {
			printf("Linha %d: Vetor %s sendo usado como função.\n", raiz->linha, raiz->simbolo->text);
		} else if (raiz->simbolo->token != SIMBOLO_FUNCAO) {
			printf("Linha %d: Função %s não foi declarada.\n", raiz->linha, raiz->simbolo->text);
		} else if (raiz->simbolo->token == SIMBOLO_FUNCAO) {
			/* TO DO*/
			//verificaChamadaFuncao(raiz);
		}

		
	}

	
	
	// chama recursivamente os filhos para continuar a verificação de utilização de identificadores...
	for (int i = 0; i < MAX_FILHOS; i++) {
		verificaUtilizacao(raiz->filhos[i]):	
	}
}

void verificaDados(AST *raiz) {
	

}




void verificaChamadaFuncao() { 
	
}


void verificaListaParam() { 
	
	
}
