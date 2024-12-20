#include <iostream>
#include "lexer/lexer.h"
#include "parser/node_ast.h"

int main(int argc, char* argv[]) {

    ////////////////
    // LEXER TEST //
    ////////////////
    std::string filename = std::string(KALEIDOSCOPE_EXAMPLES_DIR) + "/example_01.kl";
    std::unique_ptr<InputReader> reader = std::make_unique<InputReader>(filename);
    Lexer lexer{std::move(reader)};

    std::unique_ptr<Token> nextToken = lexer.getNextToken();
    while(!nextToken->isEof()) {
        std::cout << nextToken->to_string() << '\n';
        nextToken = lexer.getNextToken();
    }

    /////////////////
    // PARSER TEST //
    /////////////////

    // Print the `prettyString` for the code in examples/example_01.kl given its AST structure.
    std::vector<std::unique_ptr<StmtAST>> stmts;

    // def identity(x)
    //     x
    stmts.push_back(
        std::make_unique<FuncDefAST>(
            std::make_unique<FuncSignAST>(std::string("identity"), std::vector<std::string>({std::string("x")})),
            std::make_unique<IdAST>("x")
        )
    );

    // identity(x)
    std::vector<std::unique_ptr<ExprAST>> callArgs;
    callArgs.push_back(std::make_unique<IdAST>(std::string("x")));
    stmts.push_back(
        std::make_unique<CallAST>(
            std::string("identity"),
            std::move(callArgs)
        )
    );

    std::unique_ptr<NodeAST> root = std::make_unique<RootAST>(std::move(stmts));
    std::cout << root->prettyPrint();
    return 0;
}