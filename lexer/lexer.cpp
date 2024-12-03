#include "lexer.h"

std::unique_ptr<Token> Lexer::parseNumToken() {
    std::string tokenValue;
    char peekedCharacter = reader->peekNextCharacter();
    
    while (isdigit(peekedCharacter) || peekedCharacter == '.') {
        tokenValue += peekedCharacter;

        reader->consumePeekedCharacter();
        peekedCharacter = reader->peekNextCharacter();
    }

    return std::make_unique<NumToken>(std::stod(tokenValue));
}

std::unique_ptr<Token> Lexer::createSpecialCharacterToken(IdTokenType type, std::string symbol) {
    reader->consumePeekedCharacter();
    return std::make_unique<IdToken>(type, symbol);
}

std::unique_ptr<Token> Lexer::parseIdToken() {
    char peekedCharacter = reader->peekNextCharacter();

    // Check if it's a special character.
    switch (peekedCharacter) {
        case '+':
            return createSpecialCharacterToken(IdTokenType::PLUS, "+");
        case '-':
            return createSpecialCharacterToken(IdTokenType::MINUS, "-");
        case '*':
            return createSpecialCharacterToken(IdTokenType::MULTIPLICATION, "*");
        case '/':
            return createSpecialCharacterToken(IdTokenType::DIVISION, "/");
        case '(':
            return createSpecialCharacterToken(IdTokenType::LEFT_PARANTHESIS, "(");
        case ')':
            return createSpecialCharacterToken(IdTokenType::RIGHT_PARANTHESIS, ")");
    }

    // Parse the next identifier. The structure of an identifier can be defined by the following
    // regular expression: [a-zA-Z_][a-zA-Z0-9_]*.
    std::string tokenValue;
    while (isalnum(peekedCharacter) || peekedCharacter == '_') {
        tokenValue += peekedCharacter;

        reader->consumePeekedCharacter();
        peekedCharacter = reader->peekNextCharacter();
    }

    if (tokenValue == "def") return std::make_unique<IdToken>(IdTokenType::DEF, "DEF");
    if (tokenValue == "extern") return std::make_unique<IdToken>(IdTokenType::EXTERN, "EXTERN");
    return std::make_unique<IdToken>(IdTokenType::USER_DEFINED, tokenValue);
}

std::unique_ptr<Token> Lexer::getNextToken() {
    char peekedCharacter = reader->peekNextCharacter();

    // Skip whitespace.
    while (isspace(peekedCharacter)) {
        reader->consumePeekedCharacter();
        peekedCharacter = reader->peekNextCharacter();
    }

    // Check whether to parse number token.
    if (isdigit(peekedCharacter)) {
        return parseNumToken();
    }

    // Check whether to parse EofToken.
    if (peekedCharacter == EOF) {
        return std::make_unique<EofToken>();
    }

    // Parse IdToken.
    return parseIdToken();
}