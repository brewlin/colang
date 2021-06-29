/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef CO_LANG_EXPRESSION_H
#define CO_LANG_EXPRESSION_H
#include "Ast.h"
#include "Value.h"
class Context;
class Runtime;

using namespace std;

struct  Expression : public Ast {
    using Ast::Ast;
    virtual              ~Expression() = default;

    virtual void              asmgen(std::deque<Context*> ctx) = 0;
    virtual std::string       toString() = 0;
};

struct BoolExpr : public Expression{
    explicit BoolExpr(int line,int column):Expression(line,column){}
    bool literal;

    void         asmgen(std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct CharExpr : public Expression {
    explicit CharExpr(int line, int column) : Expression(line, column) {}
    char literal;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct NullExpr : public Expression {
    explicit     NullExpr(int line, int column) : Expression(line, column) {}

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct IntExpr : public Expression {
    explicit     IntExpr(int line, int column) : Expression(line, column) {}
    int          literal;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct DoubleExpr : public Expression {
    explicit     DoubleExpr(int line, int column) : Expression(line, column) {}

    double       literal;

    void         asmgen( std::deque<Context*> ctx) override;
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

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct ArrayExpr : public Expression {
    explicit     ArrayExpr(int line, int column) : Expression(line, column) {}
    std::vector<Expression*> literal;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct MapExpr : public Expression {
    explicit     MapExpr(int line, int column) : Expression(line, column) {}
    std::vector<Expression*> literal;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct KVExpr : public Expression {
    explicit KVExpr(int line, int column) : Expression(line, column) {}

    Expression*  key{};
    Expression*  value{};

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct ChainExpr : public Expression {
    explicit ChainExpr(int line,int column): Expression(line,column){}

    Expression* lhs{};
    Expression* rhs{};

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct VarExpr : public Expression {
    explicit VarExpr(std::string varname, int line, int column)
            : Expression(line, column),
            varname(std::move(varname)),
            is_local(true),
            is_variadic(false),
            is_delref(false),
            structtype(false){}
    std::string  varname;
    //在 asm generate 时 作为 bp 偏移量
    int          offset;
    //在asm  generate 时作为 唯一标号
    string       name;
    bool         is_local;
    bool         is_variadic;
    bool         is_delref;
    //当前变量为全局变量时 所属包名
    string       package;
    //当前变量被强制申请为 struct内存结构
    string       structname;
    bool         structtype;

    void         asmgen( std::deque<Context*> ctx) override;
    string       toString() override;
};
struct ClosureExpr : public Expression {
    explicit ClosureExpr(std::string varname, int line, int column)
            : Expression(line, column),
              varname(std::move(varname)){}
    std::string  varname;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct IndexExpr : public Expression {
    explicit IndexExpr(int line, int column) 
    : Expression(line, column),is_pkgcall(false) {}

    std::string varname;
    Expression* index{};
    //可能进行包变量调用
    bool        is_pkgcall;
    std::string package;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct BinaryExpr : public Expression {
    explicit BinaryExpr(int line, int column) : Expression(line, column) {}
    Expression*  lhs{};
    Token        opt{};
    Expression*  rhs{};

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct FunCallExpr : public Expression {
    explicit FunCallExpr(int line, int column)
    : Expression(line, column),is_pkgcall(false) {}
    std::string funcname;
    std::string package;
    std::vector<Expression*> args;

    bool         is_pkgcall;
    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct AssignExpr : public Expression {
    explicit AssignExpr(int line, int column) : Expression(line, column) {}

    Expression*  lhs{};
    Token        opt;
    Expression*  rhs{};


    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};

struct NewClassExpr : public Expression {
    explicit NewClassExpr(int line, int column) : Expression(line, column) {}
    std::string package;
    std::string name;

    std::vector<Expression*> args;
    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct NewExpr : public Expression {
    explicit NewExpr(int line, int column) : Expression(line, column) {}
    std::string package;
    std::string name;

    int         len;//申请的字节大小

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};


struct MemberExpr : public Expression {
    explicit MemberExpr(int line, int column) : Expression(line, column) {}
    std::string  varname;
    std::string  membername;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};
struct MemberCallExpr : public Expression {
    explicit MemberCallExpr(int line, int column) : Expression(line, column) {}
    std::string  varname;
    std::string  membername;

    std::vector<Expression*> args;

    void         asmgen( std::deque<Context*> ctx) override;
    std::string  toString() override;
};


#endif //CO_LANG_EXPRESSION_H
