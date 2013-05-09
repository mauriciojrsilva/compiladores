%{
#include <stdio.h>
#include "ast.h"

%}

%union {
        AST *astree;
        HASH_ELEMENT *symbol;
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

/* Indentificador */
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
				
%type <symbol> ';' ':' '(' ')' '{' '}' '=' '+' '-' '*' '/' '<' '>'

%%
/* Regras (e ações) da gramática da Linguagem K */

// criada a regra s para conseguir chamar a impressão da árvore
s : programa																																{ $$ = $1; /*imprimir arvore aqui...*/ }
 
programa: decl_global programa																							{ $$ = criarNodo(AST_PROG,  0, $1, $2, 0, 0); }
  | def_funcao programa																											{ $$ = criarNodo(AST_PROG,  0, $1, $2, 0, 0); }
  |																																					{ $$ = criarNodo(AST_EMPTY, 0,  0,  0, 0, 0); }
  ;

decl_global: decl_var ';'																										{ $$ = criarNodo(AST_DECL_GL, 0, $1,  0, 0, 0); }
  | decl_vetor ';'																													{ $$ = criarNodo(AST_DECL_GL, 0, $1,  0, 0, 0); }
  ;

decl_local: decl_var ';' decl_local																					{ $$ = criarNodo(AST_DECL_LOC, 0, $1, $3, 0, 0); }
	|																																					{ $$ = criarNodo(AST_EMPTY,    0,  0,  0, 0, 0); }
	;
  
decl_var: TK_IDENTIFICADOR ':' tipo_var																			{ $$ = criarNodo(AST_DECL_VAR, $1, $3, 0, 0, 0); }
  ;

decl_vetor: TK_IDENTIFICADOR ':' tipo_var '[' TK_LIT_INTEIRO ']'						{ $$ = criarNodo(AST_DECL_VEC, $1, $3, criarNodo(AST_VEC_SIZE, $5,  0,  0, 0, 0), 0, 0); }
	;

tipo_var: TK_PR_INTEIRO																											{ $$ = criarNodo(AST_T_INT,    0,  0,  0, 0, 0); }
        | TK_PR_FLUTUANTE																										{ $$ = criarNodo(AST_T_FLO,    0,  0,  0, 0, 0); }
        | TK_PR_BOOLEANO																										{ $$ = criarNodo(AST_T_BOO,    0,  0,  0, 0, 0); }
        | TK_PR_CARACTERE																										{ $$ = criarNodo(AST_T_CHA,    0,  0,  0, 0, 0); }
        | TK_PR_CADEIA																											{ $$ = criarNodo(AST_T_STR,    0,  0,  0, 0, 0); }
        ;

def_funcao: cabecalho decl_local bloco_comando															{ $$ = criarNodo(AST_DEF_F,    0,  $1,  $2, $3, 0); }
  ;
  
chamada_funcao: TK_IDENTIFICADOR '(' lista_expressoes ')'										{ $$ = criarNodo(AST_CHAM_F,   $1,  $3,  0, 0, 0); }


/* Function header - begin */
cabecalho: TK_IDENTIFICADOR ':' tipo_var '(' lista_parametros ')'						{ $$ = criarNodo(AST_HEADER,    $1,  $3,  $5, 0, 0); }
  ;
	
lista_parametros: lista_parametros_nao_vazia																{ $$ = $1; }
  |																																					{ $$ = criarNodo(AST_EMPTY,    0,  0,  0, 0, 0); }
  ;

lista_parametros_nao_vazia: parametro ',' lista_parametros_nao_vazia				{ $$ = criarNodo(AST_LIST_P,   0, $1, $3, 0, 0); }
  | parametro																																{ $$ = criarNodo(AST_LIST_P,   0, $1,  0, 0, 0); }
  ;

parametro: TK_IDENTIFICADOR ':' tipo_var																		{ $$ = criarNodo(AST_PARAM,   $1, $3,  0, 0, 0); }
  ;
/* Function header - end */


/* Function body - begin */

comando: bloco_comando																											{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | controle_fluxo																													{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | atribuicao																															{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | entrada																																	{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | saida																																		{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | retorna																																	{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | decl_var ';'																														{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  | chamada_funcao ';'																											{ $$ = criarNodo(AST_COM, 0, $1, 0, 0, 0); }
  ;

bloco_comando: '{' seq_comando '}'																					{ $$ = criarNodo(AST_BLO_COM, 0, $2, 0, 0, 0); }
  ;
  
seq_comando: comando seq_comando																						{ $$ = criarNodo(AST_SEQ,     0, $1,  0, 0, 0); }
	| ';'																																			{ $$ = criarNodo(AST_EMPTY,   0,  0,  0, 0, 0); }
  |																																					{ $$ = criarNodo(AST_EMPTY,   0,  0,  0, 0, 0); }	
  ;

atribuicao: TK_IDENTIFICADOR '=' expressao ';'															{ $$ = criarNodo(AST_ATR_VAR, $1, $3,  0, 0, 0); }	
  | TK_IDENTIFICADOR '[' expressao ']' '=' expressao ';'										{ $$ = criarNodo(AST_ATR_VEC, $1, $3, $6, 0, 0); }
  ;

entrada: TK_PR_ENTRADA TK_IDENTIFICADOR ';'																	{ $$ = criarNodo(AST_INP, $2, 0, 0, 0, 0); }
  ;

saida: TK_PR_SAIDA lista_expressoes_nao_vazia ';'														{ $$ = criarNodo(AST_OUT, 0, $2, 0, 0, 0); }
  ;

lista_expressoes_nao_vazia: expressao ',' lista_expressoes_nao_vazia				{ $$ = criarNodo(AST_LIST_E, 0, $1, $3, 0, 0); }
  | expressao																																{ $$ = criarNodo(AST_LIST_E, 0, $1,  0, 0, 0); }
  ;

retorna: TK_PR_RETORNA expressao ';'																				{ $$ = criarNodo(AST_RET, 0, $2, 0, 0, 0); }
  ;
  
controle_fluxo: TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando							{ $$ = criarNodo(AST_IF,    0, $3, $6,  0, 0); }
  | TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando TK_PR_SENAO comando			{ $$ = criarNodo(AST_IF,    0, $3, $6, $8, 0); }
  | TK_PR_ENQUANTO '(' expressao ')' comando																{ $$ = criarNodo(AST_WHILE, 0, $3, $5,  0, 0); }
  ;

expressao: TK_IDENTIFICADOR																									{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }	
  | TK_IDENTIFICADOR '[' expressao ']'																			{ $$ = criarNodo(AST_SYMBOL, $1, $3, 0, 0, 0); }	
  | TK_LIT_INTEIRO																													{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }
  | TK_LIT_FLUTUANTE																												{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }
  | TK_LIT_FALSO																														{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }
  | TK_LIT_VERDADEIRO																												{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }
  | TK_LIT_CARACTERE																												{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }
  | TK_LIT_CADEIA																														{ $$ = criarNodo(AST_SYMBOL, $1,  0, 0, 0, 0); }
  | expressao '+' expressao																									{ $$ = criarNodo(AST_OP_SUM, 0, $1, $3, 0, 0); }
  | expressao '-' expressao																									{ $$ = criarNodo(AST_OP_SUB, 0, $1, $3, 0, 0); }
  | expressao '*' expressao																									{ $$ = criarNodo(AST_OP_MUL, 0, $1, $3, 0, 0); }
  | expressao '/' expressao																									{ $$ = criarNodo(AST_OP_DIV, 0, $1, $3, 0, 0); }
  | expressao '<' expressao																									{ $$ = criarNodo(AST_OP_LES, 0, $1, $3, 0, 0); }
  | expressao '>' expressao																									{ $$ = criarNodo(AST_OP_GRE, 0, $1, $3, 0, 0); }
  | '+' expressao																														{ $$ = $2; }
  | '-' expressao																														{ $$ = $2; }
  | '(' expressao ')'																												{ $$ = $2; }
  | expressao TK_OC_LE expressao																						{ $$ = astCreate(AST_OP_LE, 0, $1, $3, 0, 0); }
  | expressao TK_OC_GE expressao																						{ $$ = astCreate(AST_OP_GE, 0, $1, $3, 0, 0); }
  | expressao TK_OC_EQ expressao																						{ $$ = astCreate(AST_OP_EQ, 0, $1, $3, 0, 0); }
  | expressao TK_OC_NE expressao																						{ $$ = astCreate(AST_OP_NE, 0, $1, $3, 0, 0); }
  | expressao TK_OC_AND expressao																						{ $$ = astCreate(AST_OP_AND, 0, $1, $3, 0, 0); }
  | expressao TK_OC_OR expressao																						{ $$ = astCreate(AST_OP_OR, 0, $1, $3, 0, 0); }
  | chamada_funcao																													{ $$ = astCreate(AST_CHAM_F, 0, $1, 0, 0, 0); }
  ;

lista_expressoes: lista_expressoes_nao_vazia																{ $$ = $1; }
  |																																					{ $$ = criarNodo(AST_EMPTY,    0,  0,  0, 0, 0); }
  ;
/* Function body - end */

%%
