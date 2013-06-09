%{
#include <stdio.h>
#include <list>
#include "../tree/common.h"
#include "../symbol.h"
#include "../tree/node.h"
#include "../tree/programnode.h"
#include "../tree/declarevarnode.h"
#include "../tree/declarevectornode.h"
#include "../tree/headernode.h"
#include "../tree/definefunctionnode.h"

int yylex();
void yyerror(const char *message);

typedef std::list<Node*> ParameterList;
typedef std::list<Node*> VariableList;

%}

/*%code requires {
}*/

%union {
  Node* node;
  std::list<Node*>* nodes;
  Common::DataType dataType;
  Symbol* symbol;
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

%type <node> s
%type <node> programa
%type <node> decl_global
%type <nodes> decl_local
%type <node> decl_var
%type <node> decl_vetor
%type <dataType> tipo_var
%type <node> def_funcao
%type <node> chamada_funcao
%type <node> cabecalho
%type <nodes> lista_parametros
%type <nodes> lista_parametros_nao_vazia
%type <node> parametro
%type <node> comando
%type <node> bloco_comando
%type <node> seq_comando
%type <node> atribuicao
%type <node> entrada
%type <node> saida
%type <node> lista_expressoes_nao_vazia
%type <node> retorna
%type <node> controle_fluxo
%type <node> expressao
%type <node> lista_expressoes

%start s

%%
/* Regras (e ações) da gramática da Linguagem K */

// criada a regra s para conseguir chamar a impressão da árvore
s : programa { $$ = $1; $$->print(); $$->printSourceCode(); }
	;

programa: programa decl_global { $1->addChild($2); }
	| programa def_funcao { $1->addChild($2); }
	| { $$ = new ProgramNode(); }
	;

decl_global: decl_var ';' { $$ = $1; }
	| decl_vetor ';' { $$ = $1; }
	;

decl_local: decl_local decl_var ';' { $$->push_back($2); }
	| decl_var ';' { $$ = new VariableList(); $$->push_back($1); }
	;
  
decl_var: TK_IDENTIFICADOR ':' tipo_var { $$ = new DeclareVarNode($1->getText(), $3); }
	;

decl_vetor: TK_IDENTIFICADOR ':' tipo_var '[' TK_LIT_INTEIRO ']' { $$ = new DeclareVectorNode($1->getText(), $3, atoi($5->getText().c_str())); }
	;

tipo_var: TK_PR_INTEIRO { $$ = Common::INT; }
	| TK_PR_FLUTUANTE { $$ = Common::FLOAT; }
	| TK_PR_BOOLEANO { $$ = Common::BOOL; }
	| TK_PR_CARACTERE { $$ = Common::CHAR; }
	| TK_PR_CADEIA { $$ = Common::STRING; }
	;

def_funcao: cabecalho decl_local bloco_comando { $$ = new DefineFunctionNode(); $$->addChild($1); $$->addChildren($2); $$->addChild($3); delete $2; }
	| cabecalho bloco_comando { $$ = new DefineFunctionNode(); $$->addChild($1); $$->addChild($2); }
	;
  
chamada_funcao: TK_IDENTIFICADOR '(' lista_expressoes ')' { $$ = new Node(); }
	;

/* Function header - begin */
cabecalho: TK_IDENTIFICADOR ':' tipo_var '(' lista_parametros ')' { $$ = new HeaderNode($1->getText(), $3, $5); }
	;
	
lista_parametros: lista_parametros_nao_vazia { $$ = $1; }
	| { /* TODO: check if something needs to be put in here */ }
	;

lista_parametros_nao_vazia: lista_parametros_nao_vazia ',' parametro { $1->push_back($3); }
	| parametro { $$ = new ParameterList(); $$->push_back($1); }
	;

parametro: TK_IDENTIFICADOR ':' tipo_var { $$ = new DeclareVarNode($1->getText(), $3); }
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

bloco_comando: '{' seq_comando '}' { $$ = new Node(); }
	;
  
seq_comando: seq_comando comando { }
	| seq_comando comando ';' { }
	| { $$ = new Node(); }
	;

atribuicao: TK_IDENTIFICADOR '=' expressao ';' { $$ = new Node(); }
	| TK_IDENTIFICADOR '[' expressao ']' '=' expressao ';' { $$ = new Node(); }
	;

entrada: TK_PR_ENTRADA TK_IDENTIFICADOR ';' { $$ = new Node(); }
	;

saida: TK_PR_SAIDA lista_expressoes_nao_vazia ';' { $$ = new Node(); }
	;

lista_expressoes: lista_expressoes_nao_vazia { $$ = $1; }
	| { $$ = new Node(); }
	;

lista_expressoes_nao_vazia: lista_expressoes_nao_vazia ',' expressao { }
	| expressao { $$ = new Node(); }
	;

retorna: TK_PR_RETORNA expressao ';' { $$ = new Node(); }
	;
  
controle_fluxo: TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando { $$ = new Node(); }
	| TK_PR_SE '(' expressao ')' TK_PR_ENTAO comando TK_PR_SENAO comando { $$ = new Node(); }
	| TK_PR_ENQUANTO '(' expressao ')' comando { $$ = new Node(); }
	;

expressao: TK_IDENTIFICADOR { $$ = new Node(); }
	| TK_IDENTIFICADOR '[' expressao ']' { $$ = new Node(); }
	| TK_LIT_INTEIRO { $$ = new Node(); }
	| TK_LIT_FLUTUANTE { $$ = new Node(); }
	| TK_LIT_FALSO { $$ = new Node(); }
	| TK_LIT_VERDADEIRO { $$ = new Node(); }
	| TK_LIT_CARACTERE { $$ = new Node(); }
	| TK_LIT_CADEIA { $$ = new Node(); }
	| expressao '+' expressao { $$ = new Node(); }
	| expressao '-' expressao { $$ = new Node(); }
	| expressao '*' expressao { $$ = new Node(); }
	| expressao '/' expressao { $$ = new Node(); }
	| expressao '<' expressao { $$ = new Node(); }
	| expressao '>' expressao { $$ = new Node(); }
	| '+' expressao { $$ = new Node(); }
	| '-' expressao { $$ = new Node(); }
	| '(' expressao ')' { $$ = $2; }
	| expressao TK_OC_LE expressao { $$ = new Node(); }
	| expressao TK_OC_GE expressao { $$ = new Node(); }
	| expressao TK_OC_EQ expressao { $$ = new Node(); }
	| expressao TK_OC_NE expressao { $$ = new Node(); }
	| expressao TK_OC_AND expressao { $$ = new Node(); }
	| expressao TK_OC_OR expressao { $$ = new Node(); }
	| chamada_funcao { $$ = $1; }
	;

/* Function body - end */

%%
