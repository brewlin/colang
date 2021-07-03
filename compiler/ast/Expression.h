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

    virtual void         asmgen(deque<Context*> ctx) = 0;
    virtual string       toString() = 0;
};

struct BoolExpr : public Expression{
    explicit BoolExpr(int line,int column):Expression(line,column){}
    bool literal;

    void    asmgen(deque<Context*> ctx) override;
    string  toString() override;
};

struct CharExpr : public Expression {
    explicit CharExpr(int line, int column) : Expression(line, column) {}
    char literal;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct NullExpr : public Expression {
    explicit     NullExpr(int line, int column) : Expression(line, column) {}

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct IntExpr : public Expression {
    explicit     IntExpr(int line, int column) : Expression(line, column) {}
    int          literal;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct DoubleExpr : public Expression {
    explicit     DoubleExpr(int line, int column) : Expression(line, column) {}

    double       literal;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
/**
 * 纯字符表示
 */
struct StringExpr : public Expression {
    explicit     StringExpr(int line, int column) : Expression(line, column) {}

    string  literal;
    //在asm 阶段会自动标记生成
    string  name;
    int          offset;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct ArrayExpr : public Expression {
    explicit     ArrayExpr(int line, int column) : Expression(line, column) {}
    vector<Expression*> literal;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
struct MapExpr : public Expression {
    explicit     MapExpr(int line, int column) : Expression(line, column) {}
    vector<Expression*> literal;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
struct KVExpr : public Expression {
    explicit KVExpr(int line, int column) : Expression(line, column) {}

    Expression*  key{};
    Expression*  value{};

    void         asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
struct ChainExpr : public Expression {
    explicit ChainExpr(int line,int column): Expression(line,column){}

    Expression* lhs{};
    Expression* rhs{};

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct VarExpr : public Expression {
    explicit VarExpr(string varname, int line, int column)
            : Expression(line, column),
            varname(move(varname)),
            is_local(true),
            is_variadic(false),
            structtype(false){}
    string  varname;
    //在 asm generate 时 作为 bp 偏移量
    int          offset;
    //在asm  generate 时作为 唯一标号
    string       name;
    bool         is_local;
    bool         is_variadic;
    //当前变量为全局变量时 所属包名
    string       package;
    //当前变量被强制申请为 struct内存结构
    string       structname;
    bool         structtype;

    void         asmgen( deque<Context*> ctx) override;
    string       toString() override;
};
struct ClosureExpr : public Expression {
    explicit ClosureExpr(string varname, int line, int column)
            : Expression(line, column),
              varname(move(varname)){}
    string  varname;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct StructMemberExpr : public Expression {
    explicit StructMemberExpr(string varname ,int line,int column)
            : Expression(line,column){}
    string  varname;
    string  member;
    string  structname;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
struct DelRefExpr : public Expression {
    explicit DelRefExpr(int line,int column)
            : Expression(line,column){}
    Expression* expr;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct IndexExpr : public Expression {
    explicit IndexExpr(int line, int column) 
    : Expression(line, column),is_pkgcall(false) {}

    string varname;
    Expression* index{};
    //可能进行包变量调用
    bool        is_pkgcall;
    string package;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct BinaryExpr : public Expression {
    explicit BinaryExpr(int line, int column) : Expression(line, column) {}
    Expression*  lhs{};
    Token        opt{};
    Expression*  rhs{};

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct FunCallExpr : public Expression {
    explicit FunCallExpr(int line, int column)
    : Expression(line, column),
      is_pkgcall(false) ,
      is_extern(false),
      is_delref(false)
    {}
    string funcname;
    string package;
    vector<Expression*> args;
    bool    is_pkgcall;
    bool    is_extern;
    bool    is_delref;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct AssignExpr : public Expression {
    explicit AssignExpr(int line, int column) : Expression(line, column) {}

    Expression*  lhs{};
    Token        opt;
    Expression*  rhs{};


    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};

struct NewClassExpr : public Expression {
    explicit NewClassExpr(int line, int column) : Expression(line, column) {}
    string package;
    string name;
    vector<Expression*> args;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
struct NewExpr : public Expression {
    explicit NewExpr(int line, int column) : Expression(line, column) {}
    string package;
    string name;

    int    len;//申请的字节大小

    void   asmgen( deque<Context*> ctx) override;
    string toString() override;
};


struct MemberExpr : public Expression {
    explicit MemberExpr(int line, int column) : Expression(line, column) {}
    string  varname;
    string  membername;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};
struct MemberCallExpr : public Expression {
    explicit MemberCallExpr(int line, int column) : Expression(line, column) {}
    string  varname;
    string  membername;

    vector<Expression*> args;

    void    asmgen( deque<Context*> ctx) override;
    string  toString() override;
};


#endif //CO_LANG_EXPRESSION_H
