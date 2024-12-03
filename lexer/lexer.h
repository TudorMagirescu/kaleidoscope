#include <memory>
#include "token.h"
#include "input_reader.h"

class Lexer {

    private:
        std::unique_ptr<InputReader> reader;
        std::unique_ptr<Token> parseNumToken();
        std::unique_ptr<Token> createSpecialCharacterToken(IdTokenType type, std::string symbol);
        std::unique_ptr<Token> parseIdToken();

    public:
        Lexer(std::unique_ptr<InputReader> reader): reader(std::move(reader)) {};
        std::unique_ptr<Token> getNextToken();
};