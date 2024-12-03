#include "lexer/token.h"

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