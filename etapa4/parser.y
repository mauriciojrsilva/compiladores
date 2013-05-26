%{
#include <stdio.h>
#include "ast.h"
#include "hash.h"
#include "semantica.h"

%}

%union {
  AST* astree;
  HASH_ELEMENT* symbol;
  AST_FILHOS* filhos;
  /*AST* bloco;
  AST* statement;
  AST* identificador;
  AST* declVar;
  AST_FILHOS* */
}

/* Declaração dos tokens da gramática da Linguagem K */
/* Palavras Reservadas (PR) */
%token TK_PR_INTEIRO
%token TK_PR_FLUTUANTE
%token TK_PR_BOOLEANO
%token TK_PR_CARACTERE
%token TK_PR_CADEIA
%token TK_PR_SE
%token TK_PR_ENTAO
%token TK_PR_SENAO
%token TK_PR_ENQUANTO
%token TK_PR_REALIZA
%token TK_PR_ENTRADA
%token TK_PR_SAIDA
%token TK_PR_RETORNA

/* Operadores Compostos (OC) */
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR

/* Literais (LIT) */
%token <symbol> TK_LIT_INTEIRO
%token <symbol> TK_LIT_FLUTUANTE
%token <symbol> TK_LIT_FALSO
%token <symbol> TK_LIT_VERDADEIRO
%token <symbol> TK_LIT_CARACTERE
%token <symbol> TK_LIT_CADEIA

/* Identificador */
%token <symbol> TK_IDENTIFICADOR

/* Erro */
%token TOKEN_ERRO

%left TK_OC_OR TK_OC_AND
%left '<' '>' TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%left '+' '-'
%left '*' '/'

%type <astree> s 
%type <astree> programa	
//%type <astree> statements 
%type <astree> decl_global	
%type <astree> decl_local	
%type <astree> decl_var	
%type <astree> decl_vetor	
%type <astree> tipo_var	
%type <astree> def_funcao	
%type <astree> chamada_funcao	
%type <astree> cabecalho	
%type <astree> lista_parametros
%type <astree> lista_parametros_nao_vazia	
%type <astree> parametro	
%type <astree> comando	
%type <astree> bloco_comando	
%type <astree> seq_comando	
%type <astree> atribuicao	
%type <astree> entrada	
%type <astree> saida	
%type <astree> lista_expressoes_nao_vazia
%type <astree> retorna	
%type <astree> controle_fluxo	
%type <astree> expressao	
%type <astree> lista_expressoes

%start s

%%
/* Regras (e ações) da gramática da Linguagem K */

// criada a regra s para conseguir chamar a impressão da árvore
s : programa { $$ = $1; /*imprimeTest($1, 0);*/ imprimeArvore($$); /*astImprimeArvoreArquivo($$, 0);*/ /*verificaDeclaracoes($$); verificaUtilizacao($$); verificaTipoDados($$);*/ /*imprimir arvore aqui...*/ }
 
programa: programa decl_global { insereFilho($1, $2); /*printf("PROG - dg prog\n");*/ }
  | programa def_funcao { insereFilho($1, $2); /*printf("PROG - df prog\n");*/ }
  | { $$ = criaASTSimples(AST_PROG); }
  ;

decl_global: decl_var ';' { $$ = criaASTSimples(AST_DECL_GL); insereFilho($$, $1); /*printf("DECL_GLOBAL - dvar\n");*/ }
  | decl_vetor ';' { $$ = criaASTSimples(AST_DECL_GL); insereFilho($$, $1); /*printf("DECL_GLOBAL - dvec\n");*/ }
  ;

decl_local: decl_local decl_var ';' { insereFilho($1, $2); }
	| decl_var ';' { $$ = criaASTSimples(AST_DECL_LOC); insereFilho($$, $1); }
	;
  
decl_var: TK_IDENTIFICADOR ':' tipo_var { $$ = criaASTDeclaraVar(AST_DECL_VAR, $1, $3->tipo); insereFilho($$, $3); /* TODO: retirar o 'insereFilho' */ /*printf("DECL_VAR - only (%s)\n", $1->text);*/ }
  ;

decl_vetor: TK_IDENTIFICADOR ':' tipo_var '[' TK_LIT_INTEIRO ']' { $$ = criaASTDeclaraVar(AST_DECL_VEC, $1, $3->tipo); insereDoisFilhos($$, $3, criaASTDeclaraVar(AST_VEC_SIZE, $5, TIPODADO_INTEIRO)); /* TODO: retirar o 'insereFilho' */ }
	;

tipo_var: TK_PR_INTEIRO { $$ = criaASTSimples(AST_T_INT); }
        | TK_PR_FLUTUANTE { $$ = criaASTSimples(AST_T_FLO); }
        | TK_PR_BOOLEANO { $$ = criaASTSimples(AST_T_BOO); }
        | TK_PR_CARACTERE { $$ = criaASTSimples(AST_T_CHA); }
        | TK_PR_CADEIA { $$ = criaASTSimples(AST_T_STR); }
        ;

def_funcao: cabecalho decl_local bloco_comando { $$ = criaASTSimples(AST_DEF_F); insereTresFilhos($$, $1, $2, $3); }
  | cabecalho bloco_comando { $$ = criaASTSimples(AST_DEF_F); insereDoisFilhos($$, $1, $2); }
  ;
  
chamada_funcao: TK_IDENTIFICADOR '(' lista_expressoes ')' { $$ = criaASTDeclaraVar(AST_CHAM_F, $1, -1); insereFilho($$, $3); }


/* Function header - begin */
cabecalho: TK_IDENTIFICADOR ':' tipo_var '(' lista_parametros ')' { $$ = criaASTDeclaraVar(AST_HEADER, $1, $3->tipo); insereDoisFilhos($$, $3, $5); }
  ;
	
lista_parametros: lista_parametros_nao_vazia { $$ = $1; }
  | { $$ = criaASTSimples(AST_EMPTY); }
  ;

lista_parametros_nao_vazia: lista_parametros_nao_vazia ',' parametro { insereFilho($1, $3); }
  | parametro { $$ = criaASTSimples(AST_LIST_P); insereFilho($$, $1); }
  ;

parametro: TK_IDENTIFICADOR ':' tipo_var { $$ = criaASTDeclaraVar(AST_PARAM, $1, $3->tipo); insereFilho($$, $3); /* TODO: retirar o 'insereFilho' */ }
  ;
/* Function header - end */


/* Function body - begin */

comando: bloco_comando { $$ = $1; }
  | controle_fluxo { $$ = $1; }
  | atribuicao { $$ = $1; }
  | entrada { $$ = $1; }
  | saida { $$ = $1; }
  | retorna { $$ = $1; }
  | decl_var ';' { $$ = $1; }
  | chamada_funcao ';' { $$ = $1; }
  ;

bloco_comando: '{' seq_comando '}' { $$ = criaASTSimples(AST_BLO_COM); insereFilho($$, $2); }
  ;
  
seq_comando: seq_comando comando { insereFilho($1, $2); }
	| seq_comando comando ';' { insereFilho($1, $2); }
  | { $$ = criaASTSimples(AST_SEQ); }
  ;

atribuicao: TK_IDENTIFICADOR '=' expressao ';' { $$ = criaASTAtribuiVar(AST_ATR_VAR, $1); insereFilho($$, $3); }	
  | TK_IDENTIFICADOR '[' expressao ']' '=' expressao ';' { $$ = criaASTAtribuiVar(AST_ATR_VEC, $1); insereDoisFilhos($$, $3, $6); }
  ;

entrada: TK_PR_ENTRADA TK_IDENTIFICADOR ';' { $$ = criaASTAtribuiVar(AST_INP, $2); }
  ;

saida: TK_PR_SAIDA lista_expressoes_nao_vazia ';' { $$ = criaASTSimples(AST_OUT); insereFilho($$, $2); }
  ;

lista_expressoes: lista_expressoes_nao_vazia { $$ = $1; }
  | { $$ = criaASTSimples(AST_EMPTY); }
  ;

lista_expressoes_nao_vazia: lista_expressoes_nao_vazia ',' expressao { insereFilho($1, $3); }
  | expressao { $$ = criaASTSimples(AST_LIST_E); insereFilho($$, $1); }
  ;

retorna: TK_PR_RETORNA expressao ';' { $$ = criaASTSimples(AST_RET); insereFilho($$, $2); }
  ;
  
controle_fluxo: TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando { $$ = criaASTSimples(AST_IF); insereDoisFilhos($$, $3, $6); }
  | TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando TK_PR_SENAO comando { $$ = criaASTSimples(AST_IF); insereTresFilhos($$, $3, $6, $8); }
  | TK_PR_ENQUANTO '(' expressao ')' comando { $$ = criaASTSimples(AST_WHILE); insereDoisFilhos($$, $3, $5); }
  ;

expressao: TK_IDENTIFICADOR { $$ = criaASTAtribuiVar(AST_SYMBOL, $1); }	
  | TK_IDENTIFICADOR '[' expressao ']' { $$ = criaASTAtribuiVar(AST_SYMBOL_VEC, $1); insereFilho($$, $3); }	
  | TK_LIT_INTEIRO { $$ = criaASTDeclaraVar(AST_SYMBOL_LIT, $1, AST_T_INT); }
  | TK_LIT_FLUTUANTE { $$ = criaASTDeclaraVar(AST_SYMBOL_LIT, $1, AST_T_FLO); }
  | TK_LIT_FALSO { $$ = criaASTDeclaraVar(AST_SYMBOL_LIT, $1, AST_T_BOO); }
  | TK_LIT_VERDADEIRO { $$ = criaASTDeclaraVar(AST_SYMBOL_LIT, $1, AST_T_BOO); }
  | TK_LIT_CARACTERE { $$ = criaASTDeclaraVar(AST_SYMBOL_LIT, $1, AST_T_CHA); }
  | TK_LIT_CADEIA { $$ = criaASTDeclaraVar(AST_SYMBOL_LIT, $1, AST_T_STR); }
  | expressao '+' expressao { $$ = criaASTSimples(AST_OP_SUM); insereDoisFilhos($$, $1, $3); }
  | expressao '-' expressao { $$ = criaASTSimples(AST_OP_SUB); insereDoisFilhos($$, $1, $3); }
  | expressao '*' expressao { $$ = criaASTSimples(AST_OP_MUL); insereDoisFilhos($$, $1, $3); }
  | expressao '/' expressao { $$ = criaASTSimples(AST_OP_DIV); insereDoisFilhos($$, $1, $3); }
  | expressao '<' expressao { $$ = criaASTSimples(AST_OP_LES); insereDoisFilhos($$, $1, $3); }
  | expressao '>' expressao { $$ = criaASTSimples(AST_OP_GRE); insereDoisFilhos($$, $1, $3); }
  | '+' expressao { $$ = criaASTSimples(AST_OP_SUM); insereFilho($$, $2); }
  | '-' expressao { $$ = criaASTSimples(AST_OP_SUB); insereFilho($$, $2); }
  | '(' expressao ')' { $$ = $2; }
  | expressao TK_OC_LE expressao { $$ = criaASTSimples(AST_OP_LE); insereDoisFilhos($$, $1, $3); }
  | expressao TK_OC_GE expressao { $$ = criaASTSimples(AST_OP_GE); insereDoisFilhos($$, $1, $3); }
  | expressao TK_OC_EQ expressao { $$ = criaASTSimples(AST_OP_EQ); insereDoisFilhos($$, $1, $3); }
  | expressao TK_OC_NE expressao { $$ = criaASTSimples(AST_OP_NE); insereDoisFilhos($$, $1, $3); }
  | expressao TK_OC_AND expressao { $$ = criaASTSimples(AST_OP_AND); insereDoisFilhos($$, $1, $3); }
  | expressao TK_OC_OR expressao { $$ = criaASTSimples(AST_OP_OR); insereDoisFilhos($$, $1, $3); }
  | chamada_funcao { $$ = $1; }
  ;

/* Function body - end */

%%

void imprimeTest(AST* raiz, int nivel) {
  if (raiz == NULL)
    return;

  int i;
  for(i = 0; i < nivel; i++)
    printf("  ");
  
  printf("raiz (%d), filhos (%d)\n", raiz->tipo, raiz->numFilhos);
    
  for(i = 0; i < raiz->numFilhos; i++) {    
    imprimeTest(raiz->filhos[i], nivel + 1);
  }
}