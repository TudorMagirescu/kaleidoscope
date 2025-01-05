#include "lexer/token.h"

std::unordered_map<std::string, IdToken> IdToken::stringToIdToken = {
    {"+", IdToken("+", IdTokenType::PLUS)},
    {"-", IdToken("-", IdTokenType::MINUS)},
    {"*", IdToken("*", IdTokenType::MULTIPLICATION)},
    {"/", IdToken("/", IdTokenType::DIVISION)},
    {"(", IdToken("(", IdTokenType::LEFT_PARANTHESIS)},
    {")", IdToken(")", IdTokenType::RIGHT_PARANTHESIS)},
    {"{", IdToken("{", IdTokenType::LEFT_CURLY_BRACKET)},
    {"}", IdToken("}", IdTokenType::RIGHT_CURLY_BRACKET)},
    {",", IdToken(",", IdTokenType::COMMA)},
    {";", IdToken(";", IdTokenType::SEMICOLON)},
    {"def", IdToken("DEF", IdTokenType::DEF)},
    {"extern", IdToken("EXTERN", IdTokenType::EXTERN)},
};

IdToken::IdToken(std::string id) {
    if (stringToIdToken.find(id) != stringToIdToken.end()) {
        *this = stringToIdToken[id];
        return;
    }
    
    this->id = id;
    this->type = IdTokenType::USER_DEFINED;
}

std::string NumToken::to_string() {
    return std::string("<")
        + "NUM,"
        + std::to_string(value)
        + ">";
}

std::string IdToken::to_string() {
    return std::string("<")
        + "ID,"
        + id
        + ">";
}

std::string EofToken::to_string() {
    return std::string("<")
        + "EOF>";
}