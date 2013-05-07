%{
#include <stdio.h>
#include "ast.h"


%}

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
%token TK_LIT_INTEIRO
%token TK_LIT_FLUTUANTE
%token TK_LIT_FALSO
%token TK_LIT_VERDADEIRO
%token TK_LIT_CARACTERE
%token TK_LIT_CADEIA

/* Indentificador */
%token TK_IDENTIFICADOR

/* Erro */
%token TOKEN_ERRO

%left TK_OC_OR TK_OC_AND
%left '<' '>' TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%left '+' '-'
%left '*' '/'

%type <ast> lista_expressoes seq_comando lista_parametros chamada_funcao tipo_var decl_local decl_vetor decl_var def_funcao decl_global programa s

%%
/* Regras (e ações) da gramática da Linguagem K */

// criada a regra s para conseguir chamar a impressão da árvore
s : programa																																{ $$ = $1; }
 
programa: decl_global programa																							{ $$ = criarNodo(AST_PROG,  0, $1, $2, 0, 0); }
  | def_funcao programa																											{ $$ = criarNodo(AST_PROG,  0, $1, $2, 0, 0); }
  |																																					{ $$ = criarNodo(AST_EMPTY, 0,  0,  0, 0, 0); }
  ;

decl_global: decl_var ';'																										{ $$ = criarNodo(AST_DECL_GL, 0, $1,  0, 0, 0); }
  | decl_vetor ';'																													{ $$ = criarNodo(AST_DECL_GL, 0, $1,  0, 0, 0); }
  ;

decl_local: decl_var ';' decl_local																					{ $$ = criarNodo(AST_DECL_LOC, 0, $1, $2, 0, 0); }
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
cabecalho: TK_IDENTIFICADOR ':' tipo_var '(' lista_parametros ')'						//{ $$ = criarNodo(AST_,    0,  0,  0, 0, 0); }
  ;

lista_parametros: lista_parametros_nao_vazia
  |																																					{ $$ = criarNodo(AST_EMPTY,    0,  0,  0, 0, 0); }
  ;

lista_parametros_nao_vazia: parametro ',' lista_parametros_nao_vazia
  | parametro
  ;

parametro: TK_IDENTIFICADOR ':' tipo_var
  ;
/* Function header - end */

/* Function body - begin */

comando: bloco_comando
  | controle_fluxo
  | atribuicao
  | entrada
  | saida
  | retorna
  | decl_var ';'
  | chamada_funcao ';'
  ;

bloco_comando: '{' seq_comando '}'
  ;
  
seq_comando: comando seq_comando																						
	| ';'
  |																																					{ $$ = criarNodo(AST_EMPTY,    0,  0,  0, 0, 0); }	
  ;

atribuicao: TK_IDENTIFICADOR '=' expressao ';'
  | TK_IDENTIFICADOR '[' expressao ']' '=' expressao ';'
  ;

entrada: TK_PR_ENTRADA TK_IDENTIFICADOR ';'
  ;

saida: TK_PR_SAIDA lista_expressoes_nao_vazia ';'
  ;

lista_expressoes_nao_vazia: expressao ',' lista_expressoes_nao_vazia
  | expressao
  ;

retorna: TK_PR_RETORNA expressao ';'
  ;
  
controle_fluxo: TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando
  | TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando TK_PR_SENAO comando
  | TK_PR_ENQUANTO '(' expressao ')' comando
  ;

expressao: TK_IDENTIFICADOR
  | TK_IDENTIFICADOR '[' expressao ']'
  | TK_LIT_INTEIRO
  | TK_LIT_FLUTUANTE
  | TK_LIT_FALSO
  | TK_LIT_VERDADEIRO
  | TK_LIT_CARACTERE
  | TK_LIT_CADEIA
  | expressao '+' expressao
  | expressao '-' expressao
  | expressao '*' expressao
  | expressao '/' expressao
  | expressao '<' expressao
  | expressao '>' expressao
  | '+' expressao
  | '-' expressao
  | '(' expressao ')'
  | expressao TK_OC_LE expressao
  | expressao TK_OC_GE expressao
  | expressao TK_OC_EQ expressao
  | expressao TK_OC_NE expressao
  | expressao TK_OC_AND expressao
  | expressao TK_OC_OR expressao
  | chamada_funcao
  ;

lista_expressoes: lista_expressoes_nao_vazia
  |																																					{ $$ = criarNodo(AST_EMPTY,    0,  0,  0, 0, 0); }
  ;
/* Function body - end */

%%
