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
		filhos[(*index)] = filho;
		(*index)++;
	}
}

void astPrintNodo(AST *nodo) {
        if (nodo == 0)
                return;
       
        printf("AST(");
       
        switch(nodo->tipo) {
                case AST_SYMBOL: printf("Simbolo na hash");
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
                case AST_PROG: printf("Programa");
                        break;
                case AST_BLO_COM: printf("Bloco de comandos");
                        break;
                case AST_COM: printf("Comando");
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
  for (i = 0; i < nivel; ++i)	{
  	printf("  ");
  }

  astPrintNodo(raiz);
 
  for(i = 0; i < raiz->numFilhos; i++) {
  	imprimeArvore_aux(raiz->filhos[i], nivel+1);
  }
}

void imprimeArvore(AST *raiz) {
	imprimeArvore_aux(raiz, 1);
}

void astImprimeArvoreArquivo(AST* nodo) {
  if (nodo == 0)
  	return;

  int i;

  switch(nodo->tipo) {
    case AST_SYMBOL: 
    	fprintf(yyout, "%s", nodo->simbolo->text);
    	break;
    case AST_OP_SUM: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " + ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_SUB: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " - ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_MUL: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " * ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_DIV: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " / ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_LES: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " < ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_GRE: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " > ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_LE: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " <= ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_GE: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " >= ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_EQ: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " == ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_NE: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " != ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_AND: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " && ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_OP_OR: 
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, " || ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")");
      break;
    case AST_LIST_E: 
    	fprintf(yyout, " ");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      if(nodo->filhos[1] != 0) {
        fprintf(yyout, ",");
        astImprimeArvoreArquivo(nodo->filhos[1]);
      }
      break;
    case AST_IF: 
    	fprintf(yyout, "se (");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, ")\nentao ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      if(nodo->filhos[2] != 0) {
        fprintf(yyout, "\nsenao ");
        astImprimeArvoreArquivo(nodo->filhos[2]);
      }
      break;
    case AST_WHILE:
    	fprintf(yyout, "enquanto (");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, ")\n");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      break;
    case AST_RET: 
    	fprintf(yyout, "retorna ");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, "; ");
      break;
    case AST_INP: 
    	fprintf(yyout, "entrada %s", nodo->simbolo->text);
    	fprintf(yyout, "; ");
      break;
    case AST_OUT: 
    	fprintf(yyout, "saida");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, "; ");
      break;
    case AST_ATR_VAR: 
    	fprintf(yyout, "%s = ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, "; ");
      break;
    case AST_ATR_VEC: 
    	fprintf(yyout, "%s[", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, "] = ");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, "; ");
      break;
    case AST_CHAM_F: 
    	fprintf(yyout, "%s (", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, ")");
      fprintf(yyout, "; ");
      break;
    case AST_SEQ: fprintf(yyout, "\n");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      if(nodo->filhos[1] != 0) {        
        astImprimeArvoreArquivo(nodo->filhos[1]);
      }
      break;
    case AST_PARAM: 
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0]);
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
    	astImprimeArvoreArquivo(nodo->filhos[0]);
      if(nodo->filhos[1] != 0) {
        fprintf(yyout, ", ");
        astImprimeArvoreArquivo(nodo->filhos[1]);
      }
      break;
    case AST_HEADER: 
    	fprintf(yyout, "\n%s: ", nodo->simbolo->text);
    	astImprimeArvoreArquivo(nodo->filhos[0]);
    	fprintf(yyout, "(");
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, ")\n");
      break;
    case AST_DECL_LOC:
    	astImprimeArvoreArquivo(nodo->filhos[0]);
    	if(nodo->filhos[1] != 0) {    		
    		astImprimeArvoreArquivo(nodo->filhos[1]);
    	}
      break;
    case AST_DEF_F: 
      astImprimeArvoreArquivo(nodo->filhos[0]);
      astImprimeArvoreArquivo(nodo->filhos[1]);
      astImprimeArvoreArquivo(nodo->filhos[2]);
      break;
    case AST_DECL_VEC: 
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0]);
      astImprimeArvoreArquivo(nodo->filhos[1]);
      fprintf(yyout, "; ");
      break;
    case AST_VEC_SIZE: 
    	fprintf(yyout, " [%s]", nodo->simbolo->text);
      break;
    case AST_DECL_VAR: 
    	fprintf(yyout, "%s: ", nodo->simbolo->text);
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, "; ");
      break;
    case AST_DECL_GL: 
    	astImprimeArvoreArquivo(nodo->filhos[0]);
      break;
    case AST_PROG: 
    	fprintf(yyout, "\n");
      for(i = 0; i < nodo->numFilhos; i++)
      	astImprimeArvoreArquivo(nodo->filhos[i]);
      break;
    case AST_BLO_COM: 
    	fprintf(yyout, "{");
      astImprimeArvoreArquivo(nodo->filhos[0]);
      fprintf(yyout, "\n}");
      break;
    case AST_COM: 
    	astImprimeArvoreArquivo(nodo->filhos[0]);
      break;
    case AST_EMPTY: 
    	fprintf(yyout, "");
      break;
    default: break;
  }
}