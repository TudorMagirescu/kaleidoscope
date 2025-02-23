#include <iostream>
#include "lexer/lexer.h"
#include "parser/node_ast.h"
#include "parser/parser.h"
#include "repl/repl.h"

int main(int argc, char* argv[]) {
    Repl{}.run();
    return 0;
}