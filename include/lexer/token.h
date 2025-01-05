#pragma once

#include <string>
#include <unordered_map>

enum class IdTokenType{
    DEF,
    EXTERN,
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    LEFT_PARANTHESIS,
    RIGHT_PARANTHESIS,
    LEFT_CURLY_BRACKET,
    RIGHT_CURLY_BRACKET,
    USER_DEFINED,
    COMMA,
    SEMICOLON,
    UNKNOWN,
};

class Token {
    public:
        virtual std::string to_string()=0;
        virtual bool isEof() { return false; }
        virtual bool isNum() { return false; }
        virtual bool isId() { return false; }
        virtual bool isId(IdTokenType type) { return false; }
};

class NumToken : public Token {
    public:
        double value;

        NumToken(double value): value(value) {};
        std::string to_string() override;
        bool isNum() override { return true; }
};

class IdToken : public Token {
    private:
        IdToken(std::string id, IdTokenType type): id(id), type(type) {}; 
        static std::unordered_map<std::string, IdToken> stringToIdToken;

    public:
        IdTokenType type;
        std::string id;

        IdToken(): id(""), type(IdTokenType::UNKNOWN) {};
        IdToken(std::string id);
        std::string to_string() override;
        bool isId() override { return true; }
        bool isId(IdTokenType type) override { return this->type == type; }
};

class EofToken : public Token {
    public:
        std::string to_string() override;
        bool isEof() override { return true; }
};