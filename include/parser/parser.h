#pragma once

#include "parser/node_ast.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include <memory>

class Parser {
    private:
        std::unique_ptr<Lexer> lexer;
        std::unique_ptr<Token> currentToken;
        void getNextToken();
        
        std::unique_ptr<RootAST> parseRoot();
        std::unique_ptr<StmtAST> parseStmt();
        std::unique_ptr<ExprAST> parseExpr();
        std::unique_ptr<ExprAST> parseIdExpr();
        std::unique_ptr<NumAST> parseNum();
        std::unique_ptr<FuncSignAST> parseFuncSign();
        std::unique_ptr<FuncDefAST> parseFuncDef();
        std::unique_ptr<ExternDefAST> parseExternDef();

    public:
        Parser(std::unique_ptr<Lexer> lexer): lexer(std::move(lexer)) {};
        std::unique_ptr<NodeAST> parse();
};