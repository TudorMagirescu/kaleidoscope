#include "lexer/lexer.h"

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

std::unique_ptr<Token> Lexer::parseIdToken() {
    char peekedCharacter = reader->peekNextCharacter();

    // Check if it's a special character.
    if (!isalnum(peekedCharacter)) {
        reader->consumePeekedCharacter();
        return std::make_unique<IdToken>(std::string(1, peekedCharacter));
    }

    // Parse the next identifier. The structure of an identifier can be defined by the following
    // regular expression: [a-zA-Z][a-zA-Z0-9]*.
    std::string tokenValue;
    while (isalnum(peekedCharacter)) {
        tokenValue += peekedCharacter;
        reader->consumePeekedCharacter();
        peekedCharacter = reader->peekNextCharacter();
    }

    return std::make_unique<IdToken>(tokenValue);
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