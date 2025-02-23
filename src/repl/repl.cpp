#include "repl/repl.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "lexer/input_reader.h"

Parser Repl::createParser() {
    InputReader reader;
    Lexer lexer{std::move(reader)};
    return Parser{std::move(lexer)};
}

void Repl::run() {
    while(1) {
        std::cout << "kaleidoscope> ";

        if (parser.parse()) {
            std::cout << parser.getAST().prettyPrint() << '\n';
        } else {
            std::cout << parser.getError() << '\n';
        }
    }
}