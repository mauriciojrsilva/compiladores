%{
#include <stdio.h>

%}

/* Declaração dos tokens da gramática da Linguagem K */
%union
{
	int	sval;
};

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


%%
/* Regras (e ações) da gramática da Linguagem K */
 
programa : decl_global programa
  | 
  ;

decl_global : decl_var ';'
  | decl_vetor ';'
  ;

decl_var : TK_IDENTIFICADOR ':' tipo_var
  ;

decl_vetor : TK_IDENTIFICADOR ':' tipo_var '[' TK_LIT_INTEIRO ']'
        ;

tipo_var : TK_PR_INTEIRO
        | TK_PR_FLUTUANTE
        | TK_PR_BOOLEANO
        | TK_PR_CARACTERE
        ;

%%
