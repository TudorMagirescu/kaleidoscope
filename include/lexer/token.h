#pragma once

#include <string>

class Token {
    public:
        virtual std::string to_string()=0;
        virtual bool isEof() { return false; }
};

class NumToken : public Token {
    public:
        double value;

        NumToken(double value): value(value) {};
        std::string to_string() override;
};

enum class IdTokenType{
    DEF,
    EXTERN,
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    LEFT_PARANTHESIS,
    RIGHT_PARANTHESIS,
    USER_DEFINED,
};

class IdToken : public Token {
    public:
        IdTokenType type;
        std::string id;

        IdToken(IdTokenType type, std::string id): type(type), id(id) {};
        std::string to_string() override;
};

class EofToken : public Token {
    public:
        std::string to_string() override;
        bool isEof() override { return true; }
};