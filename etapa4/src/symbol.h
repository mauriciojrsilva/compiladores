#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

typedef enum TokenType {
    LIT_INTEGER,
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
    INTEGER,
    FLOAT,
    CHAR,
    STRING,
    VECTOR
} DataType;


class Symbol {

public:
    Symbol(std::string text, TokenType tokenType);
    TokenType getTokenType() const;
    void setTokenType(const TokenType &value);
    DataType getDataType() const;
    void setDataType(const DataType &value);
    int getCount() const;
    void setCount(int value);
    std::string getText() const;
    void setText(const std::string &value);

private:
    TokenType tokenType;
    DataType dataType;
    int count;
    std::string text;
    Symbol* value;
    Symbol* next;
};

#endif // SYMBOL_H