#include "parser/node_ast.h"

std::string NumAST::prettyPrint(int depth) const {
    return indent(depth) + std::string("NumAST(val=") + std::to_string(val) + ")";
}

std::string IdAST::prettyPrint(int depth) const {
    return indent(depth) + std::string("IdAST(id=") + id + ")";
}

std::string CallAST::prettyPrint(int depth) const {
    std::string prettyString = indent(depth) + std::string("CallAST(id=") + id + ")";
    const size_t argsCount = args.size();

    for (size_t i = 0; i < argsCount; i++) {
        prettyString += "\n" + args[i]->prettyPrint(depth + 1);
    }

    return prettyString;
}

std::string FuncSignAST::prettyPrint(int depth) const {
    std::string prettyString = indent(depth) + std::string("FuncSignAST(id=") + id;

    std::size_t paramIndex = 0;
    for (const std::string& param : params) {
        prettyString = prettyString + ", param" + std::to_string(paramIndex) + "=" + param;
        paramIndex++;
    }
    prettyString += ")";

    return prettyString;
}

std::string FuncDefAST::prettyPrint(int depth) const {
    return indent(depth) + std::string("FuncDefAST") + '\n'
        + funcSign->prettyPrint(depth + 1) + '\n' 
        + body->prettyPrint(depth + 1);
}

std::string ExternDefAST::prettyPrint(int depth) const {
    return indent(depth) + std::string("ExternDefAST") + '\n'
        + funcSign->prettyPrint(depth + 1);
}