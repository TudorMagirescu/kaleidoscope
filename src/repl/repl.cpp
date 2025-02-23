#include "repl/repl.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "lexer/input_reader.h"

Repl::Repl() {
    InputReader reader;

    Lexer lexer{std::move(reader)};
    Parser parser{std::move(lexer)};

    if (parser.parse()) {
        std::cout << parser.getAST().prettyPrint() << '\n';
    } else {
        std::cout << parser.getError() << '\n';
    }
}

void Repl::run() {
    while(1) {}
}