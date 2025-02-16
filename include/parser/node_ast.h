#pragma once

#include <string>
#include <vector>
#include <memory>

class NodeAST {
    protected:
        std::string indent(int depth) const { return std::string(depth, '\t'); }

    public:
        virtual std::string prettyPrint(int depth) const = 0;
        std::string prettyPrint() const { return prettyPrint(0); }
        virtual ~NodeAST() = default;
};

class StmtAST : public NodeAST {};

class RootAST : public NodeAST {
    private:
        std::vector<std::unique_ptr<StmtAST>> stmts;

    public:
        RootAST(std::vector<std::unique_ptr<StmtAST>> stmts): stmts(std::move(stmts)) {}
        std::string prettyPrint(int depth) const override;
};

class ExprAST : public StmtAST {};

class NumAST : public ExprAST {
    private:
        double val;

    public:
        NumAST(const double val): val(val) {}
        std::string prettyPrint(int depth) const override;
};

class IdAST : public ExprAST {
    private:
        std::string id;

    public:
        IdAST(std::string id): id(std::move(id)) {}
        std::string prettyPrint(int depth) const override;
};

class CallAST : public ExprAST {
    private:
        std::string id;
        std::vector<std::unique_ptr<ExprAST>> args;
    
    public:
        CallAST(const std::string id, std::vector<std::unique_ptr<ExprAST>> args): id(id), args(std::move(args)) {}
        std::string prettyPrint(int depth) const override;
};

class FuncSignAST : public NodeAST {
    private:
        std::string id;
        std::vector<std::string> params;

    public:
        FuncSignAST(std::string id, std::vector<std::string> params): id(std::move(id)), params(std::move(params)) {}
        std::string prettyPrint(int depth) const override;
};

class FuncDefAST : public StmtAST {
    private:
        std::unique_ptr<FuncSignAST> funcSign;
        std::unique_ptr<ExprAST> body;

    public:
        FuncDefAST(std::unique_ptr<FuncSignAST> funcSign, std::unique_ptr<ExprAST> body) : funcSign(std::move(funcSign)), body(std::move(body)) {}
        std::string prettyPrint(int depth) const override;
};

class ExternDefAST : public StmtAST {
    private:
        std::unique_ptr<FuncSignAST> funcSign;

    public:
        ExternDefAST(std::unique_ptr<FuncSignAST> funcSign): funcSign(std::move(funcSign)) {}
        std::string prettyPrint(int depth) const override;
};