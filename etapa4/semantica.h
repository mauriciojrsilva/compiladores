#include "ast.h"

/* Funções principais da análise semântica, chamadas no início da análise sintática*/
void verificaDeclaracoes(AST *raiz);
void verificaUtilizacao(AST *raiz);
void verificaTipoDados(AST *raiz);

/* Funções que auxiliam as funções principais acima */
void verificaChamadaFuncao(AST *raiz);
void verificaListaParametros(AST *paramDeclaracao, AST *paramChamada, AST *raiz);
