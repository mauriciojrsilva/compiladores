#include "semantica.h"
#include "hash.h"

void verificaDeclaracoes(AST* raiz) {
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
	}
	
	// chama recursivamente os filhos para continuar a verificação de declarações de identificadores...
	int i;
	for (i = 0; i < raiz->numFilhos; i++) {
		verificaDeclaracoes(raiz->filhos[i]);
	}	
}

// função semântica que verifica a utilização dos identificadores
void verificaUtilizacao(AST *raiz) {
	if (raiz == 0) return;
	
	// verifica a utilização das variáveis (escalares)
  if (raiz->tipo == AST_SYMBOL || raiz->tipo == AST_ATR_VAR) {
		
		if (raiz->simbolo->token == SIMBOLO_VETOR) {
    	printf("Linha %d: Vetor %s sendo usado como escalar.\n", raiz->linha, raiz->simbolo->text);
    } else if (raiz->simbolo->token == SIMBOLO_FUNCAO) {
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
			// se a função está sendo chamada corretamente, chama função auxiliar para verificar os parâmetros da função
			verificaChamadaFuncao(raiz);
		}
	}
	
	// chama recursivamente os filhos para continuar a verificação de utilização de identificadores...
	int i;
	for (i = 0; i < raiz->numFilhos; i++) {
		verificaUtilizacao(raiz->filhos[i]);
	}
}

void verificaTipoDados(AST *raiz) {
  if(raiz == 0) return;
 
  // Verifica tipos dos operandos de expressões aritmeticas
  if(raiz->tipo == AST_OP_SUM || raiz->tipo == AST_OP_SUB || raiz->tipo == AST_OP_MUL || raiz->tipo == AST_OP_DIV) {
    if(raiz->filhos[0]->tipo != AST_OP_SUM &&
      raiz->filhos[0]->tipo != AST_OP_SUB &&
      raiz->filhos[0]->tipo != AST_OP_MUL &&
      raiz->filhos[0]->tipo != AST_OP_DIV) {
      if(raiz->filhos[0]->tipo == AST_SYMBOL ||
        raiz->filhos[0]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[0]->simbolo->tipoDado != TIPODADO_INTEIRO &&
          raiz->filhos[0]->simbolo->tipoDado != TIPODADO_FLUTUANTE &&
          raiz->filhos[0]->simbolo->tipoDado != TIPODADO_CHAR) {
          printf("Linha %d: Operador %s is of an invalid tipo for arithmetic expression.\n", raiz->linha, raiz->filhos[0]->simbolo->text);
        }
      } else 
      	printf("Linha %d: Operador de tipo inválido para a expressão aritmetica.\n", raiz->linha);
    }

    if(raiz->filhos[1]->tipo != AST_OP_SUM &&
      raiz->filhos[1]->tipo != AST_OP_SUB &&
      raiz->filhos[1]->tipo != AST_OP_MUL &&
      raiz->filhos[1]->tipo != AST_OP_DIV) {
      if(raiz->filhos[1]->tipo == AST_SYMBOL ||
        raiz->filhos[1]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[1]->simbolo->tipoDado != TIPODADO_INTEIRO &&
          raiz->filhos[1]->simbolo->tipoDado != TIPODADO_FLUTUANTE &&
          raiz->filhos[1]->simbolo->tipoDado != TIPODADO_CHAR) {
          printf("Linha %d: Operador %s is of an invalid tipo for arithmetic expression.\n", raiz->linha, raiz->filhos[1]->simbolo->text);
        }
      } else 
      	printf("Linha %d: Operador de tipo inválido para a expressão aritmetica.\n", raiz->linha);
    }
  }

  // Verifica tipos dos operandos de expressões relacionais
  else if(raiz->tipo == AST_OP_LES || raiz->tipo == AST_OP_GRE || raiz->tipo == AST_OP_LE || raiz->tipo == AST_OP_GE) {
    if(raiz->filhos[0]->tipo != AST_OP_SUM &&
      raiz->filhos[0]->tipo != AST_OP_SUB &&
      raiz->filhos[0]->tipo != AST_OP_MUL &&
      raiz->filhos[0]->tipo != AST_OP_DIV) {
      if(raiz->filhos[0]->tipo == AST_SYMBOL ||
        raiz->filhos[0]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[0]->simbolo->tipoDado != TIPODADO_INTEIRO &&
          raiz->filhos[0]->simbolo->tipoDado != TIPODADO_FLUTUANTE &&
          raiz->filhos[0]->simbolo->tipoDado != TIPODADO_CHAR) {
          printf("Linha %d: Operador %s is of an invalid tipo for relational expression.\n", raiz->linha, raiz->filhos[0]->simbolo->text);
        }
      } else 
      	printf("Linha %d: Expressão relacional possui operador de tipo inválido.\n", raiz->linha);
    }

    if(raiz->filhos[1]->tipo != AST_OP_SUM &&
      raiz->filhos[1]->tipo != AST_OP_SUB &&
      raiz->filhos[1]->tipo != AST_OP_MUL &&
      raiz->filhos[1]->tipo != AST_OP_DIV) {
      if(raiz->filhos[1]->tipo == AST_SYMBOL ||
        raiz->filhos[1]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[1]->simbolo->tipoDado != TIPODADO_INTEIRO &&
          raiz->filhos[1]->simbolo->tipoDado != TIPODADO_FLUTUANTE &&
          raiz->filhos[1]->simbolo->tipoDado != TIPODADO_CHAR) {
          printf("Linha %d: Operador %s is of an invalid tipo for relational expression.\n", raiz->linha, raiz->filhos[1]->simbolo->text);
        }
      } else 
      	printf("Linha %d: Expressão relacional possui operador de tipo inválido.\n", raiz->linha);
    }
  }


  // Verifica tipos dos operandos de expressões lógicas
  else if(raiz->tipo == AST_OP_AND || raiz->tipo == AST_OP_OR) {
    if(raiz->filhos[0]->tipo != AST_OP_LES &&
      raiz->filhos[0]->tipo != AST_OP_GRE &&
      raiz->filhos[0]->tipo != AST_OP_LE &&
      raiz->filhos[0]->tipo != AST_OP_GE &&
      raiz->filhos[0]->tipo != AST_OP_EQ &&
      raiz->filhos[0]->tipo != AST_OP_NE &&
      raiz->filhos[0]->tipo != AST_OP_AND &&
      raiz->filhos[0]->tipo != AST_OP_OR) {
      if(raiz->filhos[0]->tipo == AST_SYMBOL ||
        raiz->filhos[0]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[0]->simbolo->tipoDado != TIPODADO_BOOLEANO) {
          printf("Linha %d: Operador %s é de um tipo inválido para expressões lógicas.\n", raiz->linha, raiz->filhos[0]->simbolo->text);
        }
      } else 
      	printf("Linha %d: Expressão logica possui operador de tipo inválido.\n", raiz->linha);
    }

    if(raiz->filhos[1]->tipo != AST_OP_LES &&
      raiz->filhos[1]->tipo != AST_OP_GRE &&
      raiz->filhos[1]->tipo != AST_OP_LE &&
      raiz->filhos[1]->tipo != AST_OP_GE &&
      raiz->filhos[1]->tipo != AST_OP_EQ &&
      raiz->filhos[1]->tipo != AST_OP_NE &&
      raiz->filhos[1]->tipo != AST_OP_AND &&
      raiz->filhos[1]->tipo != AST_OP_OR) {
      if(raiz->filhos[1]->tipo == AST_SYMBOL ||
        raiz->filhos[1]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[1]->simbolo->tipoDado != TIPODADO_BOOLEANO) {
          printf("Linha %d: Operador %s é de um tipo inválido para expressões lógicas.\n", raiz->linha, raiz->filhos[1]->simbolo->text);
        }
      } else 
      	printf("Linha %d: Expressão logica possui operador de tipo inválido.\n", raiz->linha);
    }
  }

  // Verifica tipo do indice do vetor
  else if(raiz->tipo == AST_SYMBOL_VEC ||
    raiz->tipo == AST_ATR_VEC) {
    if(raiz->filhos[0]->tipo != AST_OP_SUM &&
      raiz->filhos[0]->tipo != AST_OP_SUB &&
      raiz->filhos[0]->tipo != AST_OP_MUL &&
      raiz->filhos[0]->tipo != AST_OP_DIV) {
      if(raiz->filhos[0]->tipo == AST_SYMBOL ||
        raiz->filhos[0]->tipo == AST_SYMBOL_VEC) {
        if(raiz->filhos[0]->simbolo->tipoDado != TIPODADO_INTEIRO &&
          raiz->filhos[0]->simbolo->tipoDado != TIPODADO_CHAR) {
          printf("Linha %d: indice do vetor %s é de um tipo inválido.\n", raiz->linha, raiz->filhos[0]->simbolo->text);
        }
      } else 
      	printf("Linha %d: indice do vetor é de um tipo inválido.\n", raiz->linha);
    }
  }

	int i;
  for (i = 0; i < raiz->numFilhos; ++i) {
  	verificaTipoDados(raiz->filhos[i]);
  }
}

// função auxiliar para verificar a consistência dos parâmetros de chamadas de funções
void verificaChamadaFuncao(AST* raiz) { 
	//if (raiz == 0) return;
      
  if (raiz->tipo == AST_CHAM_F) {
		AST *params = raiz->simbolo->ast;

    if (params->tipo == AST_EMPTY && raiz->filhos[0]->tipo != AST_EMPTY) {
    	printf("Linha %d: Função %s possui número inválido de parâmetros.\n", raiz->linha, raiz->simbolo->text);
    } else {
			// função que verifica os parâmetros propriamente dita... 
			verificaListaParametros(params, raiz->filhos[0], raiz);
		}
  }
}

// função auxiliar que verifica se os tipos dos parâmetros declarados e utilizados nas chamadas de funções batem
void verificaListaParametros(AST *paramDeclaracao, AST *paramChamada, AST *raiz) { 
	// se não há mais parâmetros, interrompe a recursão
	if(paramDeclaracao == 0 && paramChamada == 0) return;
	
	// verifica se a declaração de parâmetros e os parâmetros da chamada estão "pareados" durante a recursão
	// se não estiverem, é porque o número de parâmetros na chamada é inválido
	if(paramDeclaracao == 0 && paramChamada != 0 || paramDeclaracao != 0 && paramChamada == 0) {
		printf("Line %d: Function call %s invalid number of parameters.\n", raiz->linha, raiz->simbolo->text);
		return;
	}
	
	// verifica o tipo do parâmetro passado na chamada da função... pode ser uma expressão ou não (ex: funcao(2+1,2 > 0))
	int tipoParametro = verificaTipoExpressao(paramChamada->filhos[0]);
	
	// verifica se os tipos do par chamada <-> declaração batem (verificar se todos os tipos estão sendo tratados!)
	if (paramDeclaracao->filhos[0]->simbolo->tipoDado == TIPODADO_BOOLEANO && tipoParametro != TIPODADO_BOOLEANO) {
		printf("Linha %d: Chamada da função %s tipo de parâmetro inválido.\n", raiz->linha, raiz->simbolo->text);
		return;
	} else if (paramDeclaracao->filhos[0]->simbolo->tipoDado == TIPODADO_CHAR && tipoParametro != TIPODADO_CHAR	&& tipoParametro != TIPODADO_BOOLEANO) {
		printf("Linha %d: Chamada da função %s tipo de parâmetro inválido.\n", raiz->linha, raiz->simbolo->text);
		return;
	} else if (paramDeclaracao->filhos[0]->simbolo->tipoDado == TIPODADO_INTEIRO && tipoParametro == TIPODADO_FLUTUANTE) {
		printf("Linha %d: Chamada da função %s tipo de parâmetro inválido.\n", raiz->linha, raiz->simbolo->text);
		return;
	}
  
  // chamada recursiva para comparar o próximo "par" de parâmetros
	verificaListaParametros(paramDeclaracao->filhos[1], paramChamada->filhos[1], raiz);
}



int verificaTipoExpressao(AST *expressao) {
	int tipoDado1, tipoDado2;
  if (expressao == 0) {
		return -1;
	} else {
  	if (expressao->simbolo != 0) {
			return expressao->simbolo->tipoDado;
  	} else {
			// operadores relacionais/lógicos sempre retornam um valor booleano!
    	if (expressao->tipo == AST_OP_LES || 
    	    expressao->tipo == AST_OP_GRE || 
    	    expressao->tipo == AST_OP_LE  ||
          expressao->tipo == AST_OP_GE  || 
          expressao->tipo == AST_OP_EQ  || 
          expressao->tipo == AST_OP_NE  ||
          expressao->tipo == AST_OP_AND || 
          expressao->tipo == AST_OP_OR) {
				return TIPODADO_BOOLEANO;
			}
      
      // verifica os tipos das sub-expressões
      tipoDado1 = verificaTipoExpressao(expressao->filhos[0]);
      tipoDado2 = verificaTipoExpressao(expressao->filhos[1]);
      
      // não entendi muito bem isso... revisar!
      if (tipoDado1 == TIPODADO_FLUTUANTE || tipoDado2 == TIPODADO_FLUTUANTE) return TIPODADO_FLUTUANTE;
      if (tipoDado1 == TIPODADO_INTEIRO || tipoDado2 == TIPODADO_INTEIRO) return TIPODADO_INTEIRO;
      if (tipoDado1 == TIPODADO_CHAR || tipoDado2 == TIPODADO_CHAR) return TIPODADO_CHAR; else return TIPODADO_BOOLEANO;
    }
  }
} 
