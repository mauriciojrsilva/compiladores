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
  | def_funcao programa
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

def_funcao : cabecalho comando ';'
  ;
  
chamada_funcao: TK_IDENTIFICADOR '(' lista_expressoes ')'

/* Function header - begin */
cabecalho : TK_IDENTIFICADOR ':' tipo_var '(' lista_parametros ')'
  ;

lista_parametros : lista_parametros_nao_vazia
  |
  ;

lista_parametros_nao_vazia : parametro ',' lista_parametros_nao_vazia
  | parametro
  ;

parametro : TK_IDENTIFICADOR ':' tipo_var
  ;
/* Function header - end */

/* Function body - begin */

comando : bloco_comando
  | controle_fluxo
  | atribuicao
  | entrada
  | saida
  | retorna
  |
  ;

bloco_comando : '{' seq_comando '}'
  ;
  
seq_comando : comando
  | comando ';' seq_comando
  | decl_var
  | decl_var ';' seq_comando
  | decl_vetor
  | decl_vetor ';' seq_comando
  ;

atribuicao : TK_IDENTIFICADOR '=' expressao
  | TK_IDENTIFICADOR '[' expressao ']' '=' expressao
  ;

entrada : TK_PR_ENTRADA TK_IDENTIFICADOR
  ;

saida : TK_PR_SAIDA lista_expressoes_nao_vazia
  ;

lista_expressoes_nao_vazia : expressao ',' lista_expressoes_nao_vazia
  | expressao
  ;

retorna : TK_PR_RETORNA expressao
  ;
  
controle_fluxo : TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando
  | TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando TK_PR_SENAO comando
  | TK_PR_ENQUANTO '(' expressao ')' comando
  ;

expressao : TK_IDENTIFICADOR
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
  | '(' expressao ')'
  | expressao TK_OC_LE expressao
  | expressao TK_OC_GE expressao
  | expressao TK_OC_EQ expressao
  | expressao TK_OC_NE expressao
  | expressao TK_OC_AND expressao
  | expressao TK_OC_OR expressao
  | chamada_funcao
  ;

lista_expressoes : lista_expressoes_nao_vazia
  |
  ;
/* Function body - end */

%%
