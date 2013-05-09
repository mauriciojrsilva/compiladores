#include "hash.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_FILHOS 4

#define AST_SYMBOL              1
#define AST_SYMBOL_VEC  				2
#define AST_SYMBOL_LIT  				3

#define AST_OP_SUM              4
#define AST_OP_SUB              5
#define AST_OP_MUL              6
#define AST_OP_DIV              7
#define AST_OP_LES              8
#define AST_OP_GRE              9
#define AST_OP_LE               10
#define AST_OP_GE               11
#define AST_OP_EQ               12
#define AST_OP_NE               13
#define AST_OP_AND              14
#define AST_OP_OR               15

#define AST_LIST_E              16
#define AST_CHAM_F              17

#define AST_IF                  18
#define AST_WHILE               19
#define AST_DO_WHILE    				20

#define AST_RET                 21
#define AST_INP                 22
#define AST_OUT                 23

#define AST_ATR_VAR             24
#define AST_ATR_VEC             25

#define AST_SEQ                 26
#define AST_PARAM               27

#define AST_T_INT               28
#define AST_T_FLO               29
#define AST_T_BOO               30
#define AST_T_CHA               31
#define AST_T_STR               32

#define AST_LIST_P              33

#define AST_DEF_F               34
#define AST_DECL_VEC    				35
#define AST_VEC_SIZE    				36
#define AST_DECL_VAR    				37
#define AST_DECL_GL             38
#define AST_DECL_LOC            39

#define AST_PROG                40

#define AST_COM                 41

#define AST_BLO_COM             42

#define AST_HEADER              43

#define AST_EMPTY               44

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