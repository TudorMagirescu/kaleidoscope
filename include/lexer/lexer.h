#pragma once

#include <memory>
#include "token.h"
#include "lexer/input_reader.h"

class Lexer {

    private:
        InputReader reader;
        std::unique_ptr<Token> parseNumToken();
        std::unique_ptr<Token> parseIdToken();

    public:
        Lexer(InputReader&& reader): reader(std::move(reader)) {};
        std::unique_ptr<Token> getNextToken();
};