#include <iostream>
#include "lexer/lexer.h"

int main(int argc, char* argv[]) {
    std::string filename = std::string(KALEIDOSCOPE_EXAMPLES_DIR) + "/example.kl";
    std::unique_ptr<InputReader> reader = std::make_unique<InputReader>(filename);
    Lexer lexer{std::move(reader)};

    std::unique_ptr<Token> nextToken = lexer.getNextToken();
    while(!nextToken->isEof()) {
        std::cout << nextToken->to_string() << '\n';
        nextToken = lexer.getNextToken();
    }
    return 0;
}