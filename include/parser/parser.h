#pragma once

#include "parser/node_ast.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include <memory>

class Parser {
    private:
        std::unique_ptr<Lexer> lexer;
        std::unique_ptr<Token> currentToken;

    public:
        Parser(std::unique_ptr<Lexer> lexer): lexer(std::move(lexer)) {};
        std::unique_ptr<NodeAST> parse();
};