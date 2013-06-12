#ifndef COMMON_H
#define COMMON_H

#include <string>

namespace Common {

typedef enum TokenType {
  LIT_INT,
  LIT_FLOAT,
  LIT_BOOL,
  LIT_CHAR,
  LIT_STRING,
  IDENTIFIER,
  VARIABLE,
  VECTOR_VAR,
  FUNCTION,
  PARAMETER
} TokenType;

typedef enum DataType {
  BOOL,
  INT,
  FLOAT,
  CHAR,
  STRING,
  VECTOR
} DataType;

typedef enum OperationType {
  OP_SUM,
  OP_SUB,
  OP_MULT,
  OP_DIV,
  OP_LESS,
  OP_GREATER,
  OP_LE,
  OP_GE,
  OP_EQUAL,
  OP_NEQUAL,
  OP_AND,
	OP_OR,
	OP_PAREN
} OperationType;

}

#endif // COMMON_H
