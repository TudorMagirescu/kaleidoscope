#include <iostream>
#include "lexer/lexer.h"
#include "parser/node_ast.h"
#include "parser/parser.h"

int main(int argc, char* argv[]) {

    ////////////////
    // LEXER TEST //
    ////////////////
    std::string filename = std::string(KALEIDOSCOPE_EXAMPLES_DIR) + "/example_00.kl";
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
    filename = std::string(KALEIDOSCOPE_EXAMPLES_DIR) + "/example_01.kl";
    reader = std::make_unique<InputReader>(filename);
    std::unique_ptr<Lexer> lexerPtr = std::make_unique<Lexer>(std::move(reader));
    std::unique_ptr<NodeAST> root = Parser(std::move(lexerPtr)).parse();

    std::cout << root->prettyPrint() << '\n';
    return 0;
}