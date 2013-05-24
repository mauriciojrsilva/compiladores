#ifndef AST_H
#define AST_H

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILHOS 4

#define AST_SYMBOL              1
#define AST_SYMBOL_VEC          2
#define AST_SYMBOL_LIT          3

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

#define AST_RET                 20
#define AST_INP                 21
#define AST_OUT                 22

#define AST_ATR_VAR             23
#define AST_ATR_VEC             24

#define AST_SEQ                 25
#define AST_PARAM               26

#define AST_T_INT               27
#define AST_T_FLO               28
#define AST_T_BOO               29
#define AST_T_CHA               30
#define AST_T_STR               31

#define AST_LIST_P              32

#define AST_DEF_F               33
#define AST_DECL_VEC    				34
#define AST_VEC_SIZE    				35
#define AST_DECL_VAR    				36
#define AST_DECL_GL             37
#define AST_DECL_LOC            38

#define AST_PROG                39

#define AST_COM                 40

#define AST_BLO_COM             41

#define AST_HEADER              42

#define AST_EMPTY               43

typedef struct AST {
  int tipo, numFilhos, linha, numHashTablesPai, inicioEscopo;
	HASH_ELEMENT* simbolo;
	HASH_ELEMENT** hashTable;
	HASH_ELEMENT*** hashTablesPai;
  struct AST** filhos;
} AST;

// protótipos das funções
AST* criaAST(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos);
AST* criaASTNovoEscopo(int tipo, HASH_ELEMENT* simbolo, AST** filhos, int numFilhos);
AST** criaNodos(AST* f1, AST* f2, AST* f3, AST* f4, int numFilhos);
void criaNodo(AST** filhos, AST* filho, int* index);
void passaHashTableParaFilhos(HASH_ELEMENT** hashTable, AST** filhos, int numFilhos);
void insereHashTableEmListaDePaisNoNodo(AST* nodo, HASH_ELEMENT** hashTable);
void imprimeArvore(AST *raiz);
int mapTipoDado(int type);

#endif
