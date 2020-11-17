/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_EXPRESSION_H
#define LANG_EXPRESSION_H
#include "Ast.h"
#include "Value.h"
#include "Llvm.h"
class Context;
class Runtime;

struct  Expression : public AstNode {
    //继承AstNode 构造函数
    using AstNode::AstNode;
    virtual              ~Expression() = default;

    virtual Value        interpret(Runtime* rt,std::deque<Context*> ctx);
    virtual Value        asmgen(Runtime* rt,std::deque<Context*> ctx) = 0;
    virtual llvm::Value* irgen(Runtime* rt,std::deque<Context*> ctx) = 0;
    virtual string       toString() = 0;
};

struct BoolExpr : public Expression{
    explicit BoolExpr(int line,int column):Expression(line,column){}
    bool literal;

    Value        interpret(Runtime* rt,std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt,std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt,std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct CharExpr : public Expression {
    explicit CharExpr(int line, int column) : Expression(line, column) {}
    char literal;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct NullExpr : public Expression {
    explicit     NullExpr(int line, int column) : Expression(line, column) {}

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct IntExpr : public Expression {
    explicit     IntExpr(int line, int column) : Expression(line, column) {}
    int          literal;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct DoubleExpr : public Expression {
    explicit     DoubleExpr(int line, int column) : Expression(line, column) {}

    double       literal;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};
/**
 * 纯字符表示
 */
struct StringExpr : public Expression {
    explicit     StringExpr(int line, int column) : Expression(line, column) {}

    std::string  literal;
    //在asm 阶段会自动标记生成
    std::string  name;
    int          offset;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct ArrayExpr : public Expression {
    explicit     ArrayExpr(int line, int column) : Expression(line, column) {}
    std::vector<Expression*> literal;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct IdentExpr : public Expression {
    explicit IdentExpr(std::string identname, int line, int column)
            : Expression(line, column),
            identname(std::move(identname)),
            is_local(true),
            is_multi(false){}
    std::string  identname;
    //在 asm generate 时 作为 bp 偏移量
    int          offset;
    //在asm  generate 时作为 唯一标号
    std::string  name;
    bool         is_local;
    bool         is_multi;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct IndexExpr : public Expression {
    explicit IndexExpr(int line, int column) : Expression(line, column) {}

    std::string identname;
    Expression* index;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct BinaryExpr : public Expression {
    explicit BinaryExpr(int line, int column) : Expression(line, column) {}
    Expression*  lhs{};
    Token        opt{};
    Expression*  rhs{};

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct FunCallExpr : public Expression {
    explicit FunCallExpr(int line, int column) : Expression(line, column) {}
    std::string funcname;
    std::vector<Expression*> args;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct AssignExpr : public Expression {
    explicit AssignExpr(int line, int column) : Expression(line, column) {}

    Expression*  lhs{};
    Token        opt;
    Expression*  rhs{};


    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct NewExpr : public Expression {
    explicit NewExpr(int line, int column) : Expression(line, column) {}
    std::string type;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct MemberExpr : public Expression {
    explicit MemberExpr(int line, int column) : Expression(line, column) {}
    std::string  varname;
    std::string  membername;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct MemberCallExpr : public Expression {
    explicit MemberCallExpr(int line, int column) : Expression(line, column) {}
    std::string  varname;
    std::string  membername;

    std::vector<Expression*> args;

    Value        interpret(Runtime* rt, std::deque<Context*> ctx) override;
    Value        asmgen(Runtime* rt, std::deque<Context*> ctx) override;
    llvm::Value* irgen(Runtime* rt, std::deque<Context*> ctx) override;
    std::string  toString() override;
};;


#endif //LANG_EXPRESSION_H
