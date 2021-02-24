/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef CO_LANG_STATEMENT_H
#define CO_LANG_STATEMENT_H

#include "Ast.h"
#include "Value.h"
class Context;
class Runtime;

struct Statement : public Ast {
    using Ast::Ast;

    virtual ~Statement() = default;

    virtual void         asmgen(std::deque<Context*> ctx) = 0;
    virtual std::string  toString() = 0;

};

struct BreakStmt : public Statement {
    explicit     BreakStmt(int line, int column) : Statement(line, column) {}

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct ContinueStmt : public Statement {
    explicit     ContinueStmt(int line, int column) : Statement(line, column) {}

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};


struct ExpressionStmt : public Statement {
    explicit     ExpressionStmt(Expression* expr, int line, int column)
                 :Statement(line, column), expr(expr) {}

    Expression*  expr{};

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct ReturnStmt : public Statement {
    explicit     ReturnStmt(int line, int column) : Statement(line, column) {}
    Expression*  ret{};

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct IfStmt : public Statement {
    explicit     IfStmt(int line, int column) : Statement(line, column) {}

    Expression*  cond{};
    Block*       block{};
    Block*       elseBlock{};

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct WhileStmt : public Statement {
    explicit     WhileStmt(int line, int column) : Statement(line, column) {}
    Expression*  cond{};
    Block*       block{};

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};

#endif //CO_LANG_STATEMENT_H
