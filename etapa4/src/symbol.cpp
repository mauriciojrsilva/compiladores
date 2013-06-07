#include "symbol.h"

Symbol::Symbol(std::string text, Common::TokenType tokenType) {
    this->text = text;
    this->tokenType = tokenType;
}


std::string Symbol::getText() const {
    return text;
}

void Symbol::setText(const std::string &value) {
    text = value;
}

Common::DataType Symbol::getDataType() const {
    return dataType;
}

void Symbol::setDataType(const Common::DataType &value) {
    dataType = value;
}

Common::TokenType Symbol::getTokenType() const {
    return tokenType;
}

void Symbol::setTokenType(const Common::TokenType &value) {
    tokenType = value;
}

int Symbol::getCount() const {
    return count;
}

void Symbol::setCount(int value) {
    count = value;
}