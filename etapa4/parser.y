%{
#include <stdio.h>
#include "ast.h"
#include "hash.h"

%}

%union {
  AST* astree;
  HASH_ELEMENT* symbol;
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
%token<symbol> TK_LIT_INTEIRO
%token<symbol> TK_LIT_FLUTUANTE
%token<symbol> TK_LIT_FALSO
%token<symbol> TK_LIT_VERDADEIRO
%token<symbol> TK_LIT_CARACTERE
%token<symbol> TK_LIT_CADEIA

/* Identificador */
%token<symbol> TK_IDENTIFICADOR

/* Erro */
%token TOKEN_ERRO

%left TK_OC_OR TK_OC_AND
%left '<' '>' TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%left '+' '-'
%left '*' '/'

%type <astree> s programa	decl_global	decl_local	decl_var	decl_vetor	tipo_var	def_funcao	chamada_funcao	cabecalho	lista_parametros
				lista_parametros_nao_vazia	parametro	comando	bloco_comando	seq_comando	atribuicao	entrada	saida	lista_expressoes_nao_vazia
				retorna	controle_fluxo	expressao	lista_expressoes

%%
/* Regras (e ações) da gramática da Linguagem K */

// criada a regra s para conseguir chamar a impressão da árvore
s : programa { $$ = $1; imprimeArvore($$); astImprimeArvoreArquivo($$); /*imprimir arvore aqui...*/ }
 
programa: decl_global programa { $$ = criaAST(AST_PROG, NULL, criaNodos($1, $2, NULL, NULL, 2), 2); }
  | def_funcao programa { $$ = criaAST(AST_PROG, NULL, criaNodos($1, $2, NULL, NULL, 2), 2); }
  | { $$ = criaAST(AST_EMPTY, NULL, NULL, 0); }
  ;

decl_global: decl_var ';' { $$ = criaAST(AST_DECL_GL, NULL, criaNodos($1, NULL, NULL, NULL, 1), 1); }
  | decl_vetor ';' { $$ = criaAST(AST_DECL_GL, NULL, criaNodos($1, NULL, NULL, NULL, 1), 1); }
  ;

decl_local: decl_var ';' decl_local { $$ = criaAST(AST_DECL_LOC, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
	| { $$ = criaAST(AST_EMPTY, NULL, NULL, 0); }
	;
  
decl_var: TK_IDENTIFICADOR ':' tipo_var { $$ = criaAST(AST_DECL_VAR, $1, criaNodos($3, NULL, NULL, NULL, 1), 1); }
  ;

decl_vetor: TK_IDENTIFICADOR ':' tipo_var '[' TK_LIT_INTEIRO ']' { $$ = criaAST(AST_DECL_VEC, $1, criaNodos($3, criaAST(AST_VEC_SIZE, $5,  NULL, 0), NULL, NULL, 2), 2); }
	;

tipo_var: TK_PR_INTEIRO { $$ = criaAST(AST_T_INT, NULL, NULL, 0); }
        | TK_PR_FLUTUANTE { $$ = criaAST(AST_T_FLO, NULL, NULL, 0); }
        | TK_PR_BOOLEANO { $$ = criaAST(AST_T_BOO, NULL, NULL, 0); }
        | TK_PR_CARACTERE { $$ = criaAST(AST_T_CHA, NULL, NULL, 0); }
        | TK_PR_CADEIA { $$ = criaAST(AST_T_STR, NULL, NULL, 0); }
        ;

def_funcao: cabecalho decl_local bloco_comando { $$ = criaAST(AST_DEF_F, NULL, criaNodos($1, $2, $3, NULL, 3), 3); }
  ;
  
chamada_funcao: TK_IDENTIFICADOR '(' lista_expressoes ')' { $$ = criaAST(AST_CHAM_F, $1, criaNodos($3, NULL, NULL, NULL, 1), 1); }


/* Function header - begin */
cabecalho: TK_IDENTIFICADOR ':' tipo_var '(' lista_parametros ')' { $$ = criaAST(AST_HEADER, $1, criaNodos($3, $5, NULL, NULL, 2), 2); }
  ;
	
lista_parametros: lista_parametros_nao_vazia { $$ = $1; }
  | { $$ = criaAST(AST_EMPTY, NULL, NULL, 0); }
  ;

lista_parametros_nao_vazia: parametro ',' lista_parametros_nao_vazia { $$ = criaAST(AST_LIST_P, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | parametro { $$ = $1; }
  ;

parametro: TK_IDENTIFICADOR ':' tipo_var { $$ = criaAST(AST_PARAM, $1, criaNodos($3, NULL, NULL, NULL, 1), 1); }
  ;
/* Function header - end */


/* Function body - begin */

comando: bloco_comando { $$ = $1; }
  | controle_fluxo { $$ = $1; }
  | atribuicao { $$ = $1; }
  | entrada { $$ = $1; }
  | saida { $$ = $1; }
  | retorna { $$ = $1; }
  | decl_var ';' { $$ = criaAST(AST_COM, NULL, criaNodos($1, NULL, NULL, NULL, 1), 1); }
  | chamada_funcao ';' { $$ = criaAST(AST_COM, NULL, criaNodos($1, NULL, NULL, NULL, 1), 1); }
  ;

bloco_comando: '{' seq_comando '}' { $$ = criaAST(AST_BLO_COM, NULL, criaNodos($2, NULL, NULL, NULL, 1), 1); }
  ;
  
seq_comando: comando seq_comando { $$ = criaAST(AST_SEQ, NULL, criaNodos($1, $2, NULL, NULL, 2), 2); }
	| ';' { $$ = criaAST(AST_EMPTY, NULL, NULL, 0); }
  | { $$ = criaAST(AST_EMPTY, NULL, NULL, 0); }	
  ;

atribuicao: TK_IDENTIFICADOR '=' expressao ';' { $$ = criaAST(AST_ATR_VAR, $1, criaNodos($3, NULL, NULL, NULL, 1), 1); }	
  | TK_IDENTIFICADOR '[' expressao ']' '=' expressao ';' { $$ = criaAST(AST_ATR_VEC, $1, criaNodos($3, $6, NULL, NULL, 2), 2); }
  ;

entrada: TK_PR_ENTRADA TK_IDENTIFICADOR ';' { $$ = criaAST(AST_INP, $2, NULL, 0); }
  ;

saida: TK_PR_SAIDA lista_expressoes_nao_vazia ';' { $$ = criaAST(AST_OUT, NULL, criaNodos($2, NULL, NULL, NULL, 1), 1); }
  ;

lista_expressoes_nao_vazia: expressao ',' lista_expressoes_nao_vazia { $$ = criaAST(AST_LIST_E, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao { $$ = $1; }
  ;

retorna: TK_PR_RETORNA expressao ';' { $$ = criaAST(AST_RET, NULL, criaNodos($2, NULL, NULL, NULL, 1), 1); }
  ;
  
controle_fluxo: TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando { $$ = criaAST(AST_IF, NULL, criaNodos($3, $6, NULL, NULL, 2), 2); }
  | TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando TK_PR_SENAO comando { $$ = criaAST(AST_IF, NULL, criaNodos($3, $6, $8, NULL, 3), 3); }
  | TK_PR_ENQUANTO '(' expressao ')' comando { $$ = criaAST(AST_WHILE, NULL, criaNodos($3, $5, NULL, NULL, 2), 2); }
  ;

expressao: TK_IDENTIFICADOR { $$ = criaAST(AST_SYMBOL, $1, NULL, 0); }	
  | TK_IDENTIFICADOR '[' expressao ']' { $$ = criaAST(AST_SYMBOL_VEC, $1, criaNodos($3, NULL, NULL, NULL, 1), 1); }	
  | TK_LIT_INTEIRO { $$ = criaAST(AST_SYMBOL, $1,  NULL, 0); }
  | TK_LIT_FLUTUANTE { $$ = criaAST(AST_SYMBOL, $1,  NULL, 0); }
  | TK_LIT_FALSO { $$ = criaAST(AST_SYMBOL, $1,  NULL, 0); }
  | TK_LIT_VERDADEIRO { $$ = criaAST(AST_SYMBOL, $1,  NULL, 0); }
  | TK_LIT_CARACTERE { $$ = criaAST(AST_SYMBOL, $1,  NULL, 0); }
  | TK_LIT_CADEIA { $$ = criaAST(AST_SYMBOL, $1, NULL, 0); }
  | expressao '+' expressao { $$ = criaAST(AST_OP_SUM, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao '-' expressao { $$ = criaAST(AST_OP_SUB, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao '*' expressao { $$ = criaAST(AST_OP_MUL, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao '/' expressao { $$ = criaAST(AST_OP_DIV, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao '<' expressao { $$ = criaAST(AST_OP_LES, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao '>' expressao { $$ = criaAST(AST_OP_GRE, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | '+' expressao { $$ = criaAST(AST_OP_SUM, NULL, criaNodos($2, NULL, NULL, NULL, 1), 1); }
  | '-' expressao { $$ = criaAST(AST_OP_SUB, NULL, criaNodos($2, NULL, NULL, NULL, 1), 1); }
  | '(' expressao ')' { $$ = $2; }
  | expressao TK_OC_LE expressao { $$ = criaAST(AST_OP_LE, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao TK_OC_GE expressao { $$ = criaAST(AST_OP_GE, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao TK_OC_EQ expressao { $$ = criaAST(AST_OP_EQ, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao TK_OC_NE expressao { $$ = criaAST(AST_OP_NE, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao TK_OC_AND expressao { $$ = criaAST(AST_OP_AND, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | expressao TK_OC_OR expressao { $$ = criaAST(AST_OP_OR, NULL, criaNodos($1, $3, NULL, NULL, 2), 2); }
  | chamada_funcao { $$ = $1; }
  ;

lista_expressoes: lista_expressoes_nao_vazia { $$ = $1; }
  | { $$ = criaAST(AST_EMPTY, NULL, NULL, 0); }
  ;
/* Function body - end */

%%
