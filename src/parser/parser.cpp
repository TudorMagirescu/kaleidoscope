#include "parser/parser.h"

std::unique_ptr<NodeAST> Parser::parse() {
    return std::make_unique<NumAST>(3.0);
}