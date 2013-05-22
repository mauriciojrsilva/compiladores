#ifndef AST_H
#define AST_H


#include "hash.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_FILHOS 4

#define AST_SYMBOL              1
#define AST_SYMBOL_VEC          2

#define AST_OP_SUM              3
#define AST_OP_SUB              4
#define AST_OP_MUL              5
#define AST_OP_DIV              6
#define AST_OP_LES              7
#define AST_OP_GRE              8
#define AST_OP_LE               9
#define AST_OP_GE               10
#define AST_OP_EQ               11
#define AST_OP_NE               12
#define AST_OP_AND              13
#define AST_OP_OR               14

#define AST_LIST_E              15
#define AST_CHAM_F              16

#define AST_IF                  17
#define AST_WHILE               18

#define AST_RET                 19
#define AST_INP                 20
#define AST_OUT                 21

#define AST_ATR_VAR             22
#define AST_ATR_VEC             23

#define AST_SEQ                 24
#define AST_PARAM               25

#define AST_T_INT               26
#define AST_T_FLO               27
#define AST_T_BOO               28
#define AST_T_CHA               29
#define AST_T_STR               30

#define AST_LIST_P              31

#define AST_DEF_F               32
#define AST_DECL_VEC    				33
#define AST_VEC_SIZE    				34
#define AST_DECL_VAR    				35
#define AST_DECL_GL             36
#define AST_DECL_LOC            37

#define AST_PROG                38

#define AST_COM                 39

#define AST_BLO_COM             40

#define AST_HEADER              41

#define AST_EMPTY               42

typedef struct AST {
  int tipo, numFilhos, linha;
	HASH_ELEMENT* simbolo;
  struct AST** filhos;
} AST;

// protótipos das funções
AST* criaAST(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos);
AST** criaNodos(AST* f1, AST* f2, AST* f3, AST* f4, int numFilhos);
void criaNodo(AST** filhos, AST* filho, int* index);
void imprimeArvore(AST *raiz);

#endif
