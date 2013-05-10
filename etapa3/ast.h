#include "hash.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_FILHOS 4

#define AST_SYMBOL              1

#define AST_OP_SUM              2
#define AST_OP_SUB              3
#define AST_OP_MUL              4
#define AST_OP_DIV              5
#define AST_OP_LES              6
#define AST_OP_GRE              7
#define AST_OP_LE               8
#define AST_OP_GE               9
#define AST_OP_EQ               10
#define AST_OP_NE               11
#define AST_OP_AND              12
#define AST_OP_OR               13

#define AST_LIST_E              14
#define AST_CHAM_F              15

#define AST_IF                  16
#define AST_WHILE               17

#define AST_RET                 28
#define AST_INP                 29
#define AST_OUT                 30

#define AST_ATR_VAR             31
#define AST_ATR_VEC             32

#define AST_SEQ                 33
#define AST_PARAM               34

#define AST_T_INT               35
#define AST_T_FLO               36
#define AST_T_BOO               37
#define AST_T_CHA               38
#define AST_T_STR               39

#define AST_LIST_P              40

#define AST_DEF_F               41
#define AST_DECL_VEC    				42
#define AST_VEC_SIZE    				43
#define AST_DECL_VAR    				44
#define AST_DECL_GL             45
#define AST_DECL_LOC            46

#define AST_PROG                47

#define AST_COM                 48

#define AST_BLO_COM             49

#define AST_HEADER              50

#define AST_EMPTY               51

typedef struct AST {
  int tipo, numFilhos;
	HASH_ELEMENT* simbolo;
  struct AST** filhos;
} AST;

// protótipos das funções
AST* criaAST(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos);
AST** criaNodos(AST* f1, AST* f2, AST* f3, AST* f4, int numFilhos);
void criaNodo(AST** filhos, AST* filho, int* index);
void imprimeArvore(AST *raiz);
