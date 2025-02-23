#pragma once

#include <memory>
#include "parser/parser.h"

class Repl {
    private:
        Parser parser;
        static Parser createParser();

    public:
        Repl(): parser(createParser()) {}
        void run();
};