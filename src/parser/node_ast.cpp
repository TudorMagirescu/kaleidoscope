#include "parser/node_ast.h"

std::string RootAST::prettyPrint(int depth) {
    std::string prettyString = "";
    const size_t stmtsCount = stmts.size();

    for (size_t i = 0; i + 1 < stmtsCount; i++) {
        prettyString += stmts[i]->prettyPrint(depth) + '\n';
    }
    prettyString += stmts[stmtsCount - 1]->prettyPrint(depth);

    return prettyString;
}

std::string NumAST::prettyPrint(int depth) {
    return indent(depth) + std::string("NumAST(val=") + std::to_string(val) + ")";
}

std::string IdAST::prettyPrint(int depth) {
    return indent(depth) + std::string("IdAST(id=") + id + ")";
}

std::string CallAST::prettyPrint(int depth) {
    std::string prettyString = indent(depth) + std::string("CallAST(id=") + id + ")\n";
    const size_t argsCount = args.size();

    for (size_t i = 0; i + 1 < argsCount; i++) {
        prettyString += args[i]->prettyPrint(depth + 1) + '\n';
    }
    prettyString += args[argsCount - 1]->prettyPrint(depth + 1);

    return prettyString;
}

std::string FuncSignAST::prettyPrint(int depth) {
    std::string prettyString = indent(depth) + std::string("FuncSignAST(id=") + id;

    std::size_t paramIndex = 0;
    for (const std::string& param : params) {
        prettyString = prettyString + ", param" + std::to_string(paramIndex) + "=" + param;
        paramIndex++;
    }
    prettyString += ")";

    return prettyString;
}

std::string FuncDefAST::prettyPrint(int depth) {
    return indent(depth) + std::string("FuncDefAST") + '\n'
        + funcSign->prettyPrint(depth + 1) + '\n' 
        + body->prettyPrint(depth + 1);
}

std::string ExternDefAST::prettyPrint(int depth) {
    return indent(depth) + std::string("ExternDefAST") + '\n'
        + funcSign->prettyPrint(depth + 1);
}