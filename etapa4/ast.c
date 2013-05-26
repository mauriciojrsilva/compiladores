#include "ast.h"

extern FILE *yyout;

void insereEmLista(AST** filhos, AST* filho) {
  if (filhos == NULL || filho == NULL)
    return;

  int i;
  for (i = 0; i < MAX_FILHOS; i++) {
    if (filhos[i] == NULL) {
      filhos[i] = filho;      
      break;
    }
  }

  if (i == MAX_FILHOS - 1) {
    printf("Não é possivel inserir um filho em nodo, ele está com a lista de filhos cheia.\n");
    exit(0);
  }  
}

void insereFilho(AST* nodo, AST* filho) {
  if (nodo == NULL)
    return;

  /*printf("Pai  -  inicioEscopo %d - ", nodo->inicioEscopo);
  astPrintNodo(nodo);
  if (nodo->hashTable == NULL)
    printf("Hashtable do pai NULL\n");
  printf("Filho  -  inicioEscopo %d - ", filho->inicioEscopo);
  astPrintNodo(filho);
  printf("\n");*/
  if (nodo->inicioEscopo) {
    if (!filho->inicioEscopo) {
      filho->hashTable = nodo->hashTable;
      if (filho->simbolo != NULL) {
        hashElement_insert(filho->hashTable, filho->simbolo);
      }
    } else
      insereHashTableEmListaDePaisNoNodo(filho, nodo->hashTable);

    if (filho->filhos != NULL)
      passaHashTableParaFilhos(filho->hashTable, filho->filhos, filho->numFilhos);
  }

  insereEmLista(nodo->filhos, filho);
  nodo->numFilhos++;
}

void insereDoisFilhos(AST* nodo, AST* filhoUm, AST* filhoDois) {
  insereFilhos(nodo, 2, filhoUm, filhoDois);
}

void insereTresFilhos(AST* nodo, AST* filhoUm, AST* filhoDois, AST* filhoTres) {
  insereFilhos(nodo, 3, filhoUm, filhoDois, filhoTres);
}

void insereQuatroFilhos(AST* nodo, AST* filhoUm, AST* filhoDois, AST* filhoTres, AST* filhoQuatro) {
  insereFilhos(nodo, 3, filhoUm, filhoDois, filhoTres, filhoQuatro);
}

void insereFilhos(AST* nodo, int numFilhos, ...) {
  va_list filhos;
  va_start(filhos, numFilhos);
  int i;
  for(i = 0; i < numFilhos; i++) {
    insereFilho(nodo, va_arg(filhos, AST*));
  }
  va_end(filhos);
}

AST** geraListaFilhos(int numFilhos, ...) {
  AST** listaFilhos = (AST**)calloc(numFilhos, sizeof(AST*));
  va_list filhos;
  va_start(filhos, numFilhos);
  int i;
  for(i = 0; i < numFilhos; i++) {
    listaFilhos[i] = va_arg(filhos, AST*);
  }
  va_end(filhos);
  return listaFilhos;
}

AST* criaASTSimples(int tipo) {
  AST *nodo = (AST*) malloc(sizeof(AST)); 
  nodo->tipo = tipo;
  nodo->numFilhos = 0;
  nodo->filhos = (AST**)calloc(MAX_FILHOS, sizeof(AST*));
  nodo->simbolo = NULL;
  nodo->linha = getLineNumber();
  nodo->hashTable = NULL;
  nodo->hashTablesPai = (HASH_ELEMENT***)calloc(MAX_ESCOPOS_INICIO, sizeof(HASH_ELEMENT**));
  nodo->numHashTablesPai = MAX_ESCOPOS_INICIO;
  nodo->inicioEscopo = 0;
  nodo->comErro = 0;
  return nodo;
}

AST* criaASTDeclaraVar(int tipo, HASH_ELEMENT* simbolo, int tipoFilho) {
  AST* nodo = criaASTSimples(tipo);
  nodo->simbolo = simbolo;
  nodo->simbolo->tipoDado = mapTipoDado(tipoFilho);
  return nodo;
}

AST* criaASTDefFunc(int tipo, AST* header) {
  AST* nodo = criaASTSimples(tipo);
  nodo->simbolo = header->simbolo;
  return nodo;
}

AST* criaASTAtribuiVar(int tipo, HASH_ELEMENT* simbolo) {
  AST* nodo = criaASTSimples(tipo);
  nodo->simbolo = simbolo;
  return nodo;
}

AST* criaASTComErro(int tipo, int tipoErro) {
  AST* nodo = criaASTSimples(tipo);
  nodo->comErro = 1;
  return nodo;
}

AST* criaASTComEscopo(int tipo) {
  AST* nodo = criaASTSimples(tipo);
  nodo->inicioEscopo = 1;
  nodo->hashTable = hash_init();
  
  if (nodo->simbolo != NULL)
    hashElement_insert(nodo->hashTable, nodo->simbolo);

  return nodo;
}

// funcao para a criação de um novo nodo
AST* criaAST(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos) {
	AST *nodo = (AST*) malloc(sizeof(AST));	
	nodo->tipo = tipo;
	nodo->numFilhos = numFilhos;
	nodo->simbolo = simbolo;
	nodo->filhos = filhos;
	nodo->linha = getLineNumber();
  nodo->hashTable = NULL;
  nodo->hashTablesPai = (HASH_ELEMENT***)calloc(MAX_ESCOPOS_INICIO, sizeof(HASH_ELEMENT**));
  nodo->numHashTablesPai = MAX_ESCOPOS_INICIO;
  nodo->inicioEscopo = 0;
	return nodo;
}

AST* criaASTNovoEscopo(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos) {
  AST *nodo = criaAST(tipo, simbolo, filhos, numFilhos);
  nodo->inicioEscopo = 1;
  nodo->hashTable = hash_init();
  if (simbolo != NULL)
    hashElement_insert(nodo->hashTable, simbolo);  
  passaHashTableParaFilhos(nodo->hashTable, filhos, numFilhos);
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
		filhos[(*index)] = filho;
		(*index)++;
	}
}

void passaHashTableParaFilhos(HASH_ELEMENT** hashTable, AST** filhos, int numFilhos) {
  int i;
  AST* filhoAtual;
  for (i = 0; i < numFilhos; i++) {
    filhoAtual = filhos[i];

    if (!filhoAtual->inicioEscopo) {
      filhoAtual->hashTable = hashTable;
      if (filhoAtual->simbolo != NULL) {
        hashElement_insert(filhoAtual->hashTable, filhoAtual->simbolo);
      }
    } else
      insereHashTableEmListaDePaisNoNodo(filhoAtual, hashTable);
    
    if (filhos[i]->filhos != NULL)
      passaHashTableParaFilhos(hashTable, filhoAtual->filhos, filhoAtual->numFilhos);
  }
}

void insereHashTableEmListaDePaisNoNodo(AST* nodo, HASH_ELEMENT** hashTable) {
  if (nodo != NULL) {
    int i, temPai = 0, preenchidos = 0, primeiroIndiceLivre = -1;
    for (i = 0; i < nodo->numHashTablesPai; i++) {
      primeiroIndiceLivre = preenchidos;
      if (nodo->hashTablesPai[i] != NULL) {
        preenchidos++;
        if (nodo->hashTablesPai[i] == hashTable) {
          temPai = 1;
          break;
        }
      }
    }

    if (!temPai) {
      if (preenchidos < nodo->numHashTablesPai) {
        nodo->hashTablesPai[primeiroIndiceLivre] = hashTable;
      } else {
        int novoTamanho = nodo->numHashTablesPai * TAXA_CRESCIMENTO_ESCOPOS;
        HASH_ELEMENT*** novaListaPais = (HASH_ELEMENT***)calloc(novoTamanho, sizeof(HASH_ELEMENT**));
        for (i = 0; i < nodo->numHashTablesPai; i++) {
          novaListaPais[i] = nodo->hashTablesPai[i];
        }
        free(nodo->hashTablesPai);
        nodo->hashTablesPai = novaListaPais;
        nodo->numHashTablesPai = novoTamanho;
      }
    }
  }
}

void astPrintNodo(AST* nodo) {
  if (nodo == 0)
    return;
 
  printf("AST(");
 
  switch(nodo->tipo) {
    case AST_SYMBOL_LIT: printf("Simbolo na hash");
      break;
    case AST_SYMBOL: printf("Simbolo na hash");
      break;
    case AST_SYMBOL_VEC: printf("Simbolo vetor na hash");
    break;
    case AST_OP_SUM: printf("Operacao +");
      break;
    case AST_OP_SUB: printf("Operacao -");
      break;
    case AST_OP_MUL: printf("Operacao *");
      break;
    case AST_OP_DIV: printf("Operacao /");
      break;
    case AST_OP_LES: printf("Operacao <");
      break;
    case AST_OP_GRE: printf("Operacao >");
      break;
    case AST_OP_LE: printf("Operacao LE");
      break;
    case AST_OP_GE: printf("Operacao GE");
      break;
    case AST_OP_EQ: printf("Operacao EQ");
      break;
    case AST_OP_NE: printf("Operacao NE");
      break;
    case AST_OP_AND: printf("Operacao AND");
      break;
    case AST_OP_OR: printf("Operacao OR");
      break;
    case AST_LIST_E: printf("Lista de expressoes");
      break;
    case AST_IF: printf("Se");
      break;
    case AST_WHILE: printf("Enquanto");
      break;
    case AST_RET: printf("Retorna");
      break;
    case AST_INP: printf("Entrada");
      break;
    case AST_OUT: printf("Saida");
      break;
    case AST_ATR_VAR: printf("Atribuicao variavel");
      break;
    case AST_ATR_VEC: printf("Atribuicao vetor");
      break;
    case AST_CHAM_F: printf("Chamada de funcao");
      break;
    case AST_SEQ: printf("Sequencia de comandos");
      break;
    case AST_PARAM: printf("Parametro");
      break;
    case AST_T_INT: printf("Tipo inteiro");
      break;
    case AST_T_FLO: printf("Tipo flutuante");
      break;
    case AST_T_BOO: printf("Tipo booleano");
      break;
    case AST_T_CHA: printf("Tipo caracter");
      break;
    case AST_LIST_P: printf("Lista de parametros");
      break;  
    case AST_DEF_F: printf("Definicao de funcao");
      break;
    case AST_DECL_VEC: printf("Declaracao de vetor");
      break;
    case AST_VEC_SIZE: printf("Tamanho do vetor");
      break;
    case AST_DECL_VAR: printf("Declaracao de variavel");
      break;
    case AST_DECL_GL: printf("Declaracao global");
      break;
    case AST_DECL_LOC: printf("Declaracao local");
      break;
    case AST_PROG: printf("Programa");
      break;
    case AST_BLO_COM: printf("Bloco de comandos");
      break;
    case AST_COM: printf("Comando");
      break;
    case AST_HEADER: printf("Header");
      break;
    case AST_EMPTY: printf("Empty");
      break;
    default: printf("UNKNOWN");
      break;
  }
 
  if (nodo->simbolo != 0)
    printf(", %s", nodo->simbolo->text);
         
  printf(");\n");
}


void imprimeArvore_aux(AST *raiz, int nivel) {
  if (raiz == 0)
  	return;
 
  int i;
  //if (raiz->tipo == 39)    
  //  printf("raiz (%d) nivel: %d numFilhos (%d)\n", raiz->tipo, nivel, raiz->numFilhos);
  for (i = 0; i < nivel; ++i)	{
  	printf("  ");
  }

  astPrintNodo(raiz);
 
  for(i = 0; i < raiz->numFilhos; i++) {
  	imprimeArvore_aux(raiz->filhos[i], nivel + 1);
  }
}

void imprimeArvore(AST *raiz) {  
	imprimeArvore_aux(raiz, 0);
}

void astImprimeArvoreArquivo(AST* nodo, int nivel) {
  if (nodo == 0)
  	return;
  
  int i;
  //printf("raiz (%d) numFilhos (%d)\n", nodo->tipo, nodo->numFilhos);

  switch(nodo->tipo) {
    case AST_SYMBOL_LIT: 
      fprintf(yyout, "%s", nodo->simbolo->text);
    break;
    case AST_SYMBOL: 
    	fprintf(yyout, "%s", nodo->simbolo->text);
    break;
    case AST_SYMBOL_VEC: 
    	fprintf(yyout, "%s", nodo->simbolo->text);
    	fprintf(yyout, "[");
			astImprimeArvoreArquivo(nodo->filhos[0], nivel);
    	fprintf(yyout, "]");
    break;
    case AST_OP_SUM:
    	if (nodo->numFilhos == 1) {
    		fprintf(yyout, " + ");
    		astImprimeArvoreArquivo(nodo->filhos[0], nivel);
    	} else if (nodo->numFilhos == 2) {
    		astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      	fprintf(yyout, " + ");
      	astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    	}      
    break;
    case AST_OP_SUB: 
      if (nodo->numFilhos == 1) {
    		fprintf(yyout, " - ");
    		astImprimeArvoreArquivo(nodo->filhos[0], nivel);
    	} else if (nodo->numFilhos == 2) {
    		astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      	fprintf(yyout, " - ");
      	astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    	}      
    break;
    case AST_OP_MUL: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " * ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_DIV: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " / ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_LES: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " < ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_GRE: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " > ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_LE: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " <= ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_GE: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " >= ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_EQ: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " == ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_NE: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " != ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_AND: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " && ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_OP_OR: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, " || ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
    break;
    case AST_LIST_E: 
    	fprintf(yyout, " ");
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      if(nodo->filhos[1] != 0) {
        fprintf(yyout, ",");
        astImprimeArvoreArquivo(nodo->filhos[1], nivel);
      }
    break;
    case AST_IF:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "se (");
      astImprimeArvoreArquivo(nodo->filhos[0], 0);
      fprintf(yyout, ") entao ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
      if(nodo->filhos[2] != 0) {
        fprintf(yyout, "%s", generateSpaces(nivel * 2));
        fprintf(yyout, "\nsenao ");
        astImprimeArvoreArquivo(nodo->filhos[2], nivel + 1);
      }
    break;
    case AST_WHILE:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "enquanto (");
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, ")\n");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel + 1);
    break;
    case AST_RET:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "retorna ");
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, "; ");
    break;
    case AST_INP:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "entrada %s", nodo->simbolo->text);
    	fprintf(yyout, "; ");
    break;
    case AST_OUT:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "saida ");
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, "; ");
    break;
    case AST_ATR_VAR: 
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "%s = ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, "; ");
    break;
    case AST_ATR_VEC:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));      
    	fprintf(yyout, "%s[", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, "] = ");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
      fprintf(yyout, "; ");
    break;
    case AST_CHAM_F: 
    	fprintf(yyout, "%s(", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, ")");
    break;
    case AST_SEQ:
      for (i = 0; i < nodo->numFilhos; i++) {        
        astImprimeArvoreArquivo(nodo->filhos[i], nivel);
        fprintf(yyout, "\n");
      }
    break;
    case AST_PARAM: 
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
    break;
    case AST_T_INT: 
    	fprintf(yyout, "inteiro");
    break;
    case AST_T_FLO: 
    	fprintf(yyout, "flutuante");
    break;
    case AST_T_BOO: 
    	fprintf(yyout, "booleano");
    break;
    case AST_T_CHA: 
    	fprintf(yyout, "caractere");
    break;
    case AST_T_STR: 
    	fprintf(yyout, "cadeia");
    break;
    case AST_LIST_P:            
      for (i = 0; i < nodo->numFilhos; i++) {
        astImprimeArvoreArquivo(nodo->filhos[i], nivel);
        if (i < nodo->numFilhos-1)
          fprintf(yyout, ", ");
      }
    break;
    case AST_HEADER: 
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
    	astImprimeArvoreArquivo(nodo->filhos[0], nivel);
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
      fprintf(yyout, ") ");
    break;
    case AST_DECL_LOC:      
      for (i = 0; i < nodo->numFilhos; i++) {
        fprintf(yyout, "\n");
        astImprimeArvoreArquivo(nodo->filhos[i], nivel);
      }
    break;
    case AST_DEF_F: 
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
      astImprimeArvoreArquivo(nodo->filhos[2], nivel);
      fprintf(yyout, "\n");
    break;
    case AST_DECL_VEC:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      astImprimeArvoreArquivo(nodo->filhos[1], nivel);
      fprintf(yyout, "; ");
    break;
    case AST_VEC_SIZE: 
    	fprintf(yyout, " [%s]", nodo->simbolo->text);
    break;
    case AST_DECL_VAR:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, "; ");
    break;
    case AST_DECL_GL: 
    	astImprimeArvoreArquivo(nodo->filhos[0], nivel);
      fprintf(yyout, "\n");
    break;
    case AST_PROG:
      for(i = 0; i < nodo->numFilhos; i++)
      	astImprimeArvoreArquivo(nodo->filhos[i], nivel);
    break;
    case AST_BLO_COM:
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
    	fprintf(yyout, "{\n");      
      for(i = 0; i < nodo->numFilhos; i++) {        
        astImprimeArvoreArquivo(nodo->filhos[i], nivel + 1);        
      }
      fprintf(yyout, "%s", generateSpaces(nivel * 2));
      fprintf(yyout, "}");
    break;
    case AST_COM: 
    	astImprimeArvoreArquivo(nodo->filhos[0], nivel);      
    break;
    case AST_EMPTY: 
    	fprintf(yyout, "");
    break;
    default: break;
  }
}

char* generateSpaces(int num) {
  int i;
  char* spaces = (char*)malloc(num*sizeof(char));
  for (i = 0; i < num; i++) {
    spaces[i] = ' ';
  }
  return spaces;
}

int mapTipoDado(int tipo) {
  switch(tipo) {
    case AST_T_BOO: return TIPODADO_BOOLEANO;
    case AST_T_CHA: return TIPODADO_CHAR;
    case AST_T_INT: return TIPODADO_INTEIRO;
    case AST_T_FLO: return TIPODADO_FLUTUANTE;        
    case AST_T_STR: return TIPODADO_CADEIA;
    default: return 0;
  }
}