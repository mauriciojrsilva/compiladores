#include "symbol.h"

Symbol::Symbol(std::string text, TokenType tokenType) {
    this->text = text;
    this->tokenType = tokenType;
}


std::string Symbol::getText() const
{
    return text;
}

void Symbol::setText(const std::string &value)
{
    text = value;
}

DataType Symbol::getDataType() const
{
    return dataType;
}

void Symbol::setDataType(const DataType &value)
{
    dataType = value;
}

TokenType Symbol::getTokenType() const
{
    return tokenType;
}

void Symbol::setTokenType(const TokenType &value)
{
    tokenType = value;
}

int Symbol::getCount() const
{
    return count;
}

void Symbol::setCount(int value)
{
    count = value;
}