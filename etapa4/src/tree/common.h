#ifndef COMMON_H
#define COMMON_H

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

}

#endif // COMMON_H
