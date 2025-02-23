#include "parser/parser.h"
#include "parser/parser_error.h"

void Parser::getNextToken() {
    currentToken = std::move(lexer.getNextToken());
}

bool Parser::parse() {
    try {
        AST = std::move(parseStmt());
        return true;
    } catch (ParserError& e) {
        error = "Error: " + std::string(e.what());
        return false;
    }
}

std::unique_ptr<StmtAST> Parser::parseStmt() {
    std::unique_ptr<StmtAST> stmt;

    // Load the first token of the statement.
    getNextToken();

    if (currentToken->isId(IdTokenType::DEF)) {
        stmt = std::move(parseFuncDef());
    } else if (currentToken->isId(IdTokenType::EXTERN)) {
        stmt = std::move(parseExternDef());
    } else {
        stmt = std::move(parseExpr());
    }

    // We expect a `;` between statements.
    if (!currentToken->isId(IdTokenType::SEMICOLON)) {
        throw ParserError("Expected ';' at the end of the statement.");
    }

    return stmt;
}

std::unique_ptr<ExprAST> Parser::parseExpr() {
    if (currentToken->isId(IdTokenType::USER_DEFINED)) {
        return parseIdExpr();
    }

    if (currentToken->isNum()) {
        return parseNum();
    }

    throw ParserError("Invalid expression.");
}

std::unique_ptr<ExprAST> Parser::parseIdExpr() {
    std::string id;
    {
        // We know the current token has type `std::unique_ptr<IdToken>`.
        IdToken* idToken = static_cast<IdToken*>(currentToken.get());
        id = idToken->id;
    }

    getNextToken(); // Eat the user-defined identifier.

    // Check if the id expression is an identifier.
    if (!currentToken->isId(IdTokenType::LEFT_PARANTHESIS)) {
        return std::make_unique<IdAST>(std::move(id));
    }

    getNextToken(); // Eat the '('

    std::vector<std::unique_ptr<ExprAST>> args;
    
    // Handle function calls with >0 arguments.
    if (!currentToken->isId(IdTokenType::RIGHT_PARANTHESIS)) {
        while (true) {
            args.push_back(parseExpr());

            if (currentToken->isId(IdTokenType::RIGHT_PARANTHESIS)) {
                break;
            }

            // We expect ',' between function call arguments.
            if (!currentToken->isId(IdTokenType::COMMA)) {
                throw ParserError("Expected ',' between function call arguments.");
            }

            getNextToken(); // Eat the ','.
        }
    }

    getNextToken(); // Eat the `)`

    return std::make_unique<CallAST>(id, std::move(args));
}

std::unique_ptr<NumAST> Parser::parseNum() {
    double value;
    {
        // We know the current token has type `std::unique_ptr<NumToken`.
        NumToken* numToken = static_cast<NumToken*>(currentToken.get());
        value = numToken->value; 
    }

    getNextToken(); // Eat the num token.

    return std::make_unique<NumAST>(value);
}

std::unique_ptr<FuncSignAST> Parser::parseFuncSign() {
    if (!currentToken->isId(IdTokenType::USER_DEFINED)) {
        throw ParserError("Invalid function name token.");
    }

    std::string id = static_cast<IdToken*>(currentToken.get())->id;
    getNextToken(); // Eat the user-defined token.

    if (!currentToken->isId(IdTokenType::LEFT_PARANTHESIS)) {
        throw ParserError("Expected '(' after function name.");
    }

    getNextToken(); // Eat the `(`

    std::vector<std::string> params;

    // Handle function signatures with >0 parameters.
    if (!currentToken->isId(IdTokenType::RIGHT_PARANTHESIS)) {
        while (true) {
            if (!currentToken->isId(IdTokenType::USER_DEFINED)) {
                throw ParserError("Invalid function parameter token.");
            }

            std::string param = static_cast<IdToken*>(currentToken.get())->id;
            params.push_back(param);
            getNextToken(); // Eat the user-defined token.

            if (currentToken->isId(IdTokenType::RIGHT_PARANTHESIS)) {
                break;
            }
            
            // We expect ',' between function parameters.
            if (!currentToken->isId(IdTokenType::COMMA)) {
                throw ParserError("Expected ',' or ')' after function parameter.");
            }

            getNextToken(); // Eat the `,`.
        }
    }

    getNextToken(); // Eat the `)`

    return std::make_unique<FuncSignAST>(std::move(id), std::move(params));
}

std::unique_ptr<FuncDefAST> Parser::parseFuncDef() {
    getNextToken(); // Eat the `def`.

    std::unique_ptr<FuncSignAST> funcSign = parseFuncSign();

    if (!currentToken->isId(IdTokenType::LEFT_CURLY_BRACKET)) {
        throw ParserError("Expected '{' after function signature.");
    }
    
    getNextToken(); // Eat the `{`

    std::unique_ptr<ExprAST> expr = parseExpr();

    if (!currentToken->isId(IdTokenType::RIGHT_CURLY_BRACKET)) {
        throw ParserError("Expected '}' after function body.");
    }

    getNextToken(); // Eat the `}`

    return std::make_unique<FuncDefAST>(std::move(funcSign), std::move(expr));
}

std::unique_ptr<ExternDefAST> Parser::parseExternDef() {
    getNextToken(); // Eat the `extern`.

    std::unique_ptr<FuncSignAST> funcSign = parseFuncSign();

    return std::make_unique<ExternDefAST>(std::move(funcSign));
}