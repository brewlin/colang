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

    virtual Expression*     asmgen(deque<Context*> ctx) = 0;
    virtual string          toString() = 0;
    virtual Token           getType(deque<Context*> ctx) = 0;
};

struct BoolExpr : public Expression{
    explicit BoolExpr(int line,int column):Expression(line,column){}
    bool literal;

    Expression*    asmgen(deque<Context*> ctx) override;
    string         toString() override;
    Token          getType(deque<Context*> ctx) override;
};

struct CharExpr : public Expression {
    explicit CharExpr(int line, int column) : Expression(line, column) {}
    char literal;

    Expression*    asmgen( deque<Context*> ctx) override;
    string         toString() override;
    Token          getType(deque<Context*> ctx) override;
};

struct NullExpr : public Expression {
    explicit     NullExpr(int line, int column) : Expression(line, column) {}

    Expression*    asmgen( deque<Context*> ctx) override;
    string         toString() override;
    Token          getType(deque<Context*> ctx) override;
};

struct IntExpr : public Expression {
    explicit     IntExpr(int line, int column) : Expression(line, column) {}
    string       literal;

    Expression*    asmgen( deque<Context*> ctx) override;
    string         toString() override;
    Token          getType(deque<Context*> ctx) override;
};

struct DoubleExpr : public Expression {
    explicit     DoubleExpr(int line, int column) : Expression(line, column) {}

    double       literal;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
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

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};

struct ArrayExpr : public Expression {
    explicit     ArrayExpr(int line, int column) : Expression(line, column) {}
    vector<Expression*> literal;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct MapExpr : public Expression {
    explicit     MapExpr(int line, int column) : Expression(line, column) {}
    vector<Expression*> literal;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct KVExpr : public Expression {
    explicit KVExpr(int line, int column) : Expression(line, column) {}

    Expression*  key{};
    Expression*  value{};

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct ChainExpr : public Expression {
    explicit ChainExpr(int line,int column): Expression(line,column){}

    Expression* lhs{};
    Expression* rhs{};

    Expression* asmgen( deque<Context*> ctx) override;
    string      toString() override;
    Token       getType(deque<Context*> ctx) override;
};

enum VarType
{
   Var_Obj_Member = 0, //成员函数调用
   Var_Extern_Global, Var_Local_Global, // 内部全局变量，外部全局变量
   Var_Local, //本地变量
   Var_Func,
};
struct VarExpr : public Expression {
    explicit VarExpr(string varname, int line, int column)
            : Expression(line, column),
            varname(move(varname)),
            is_local(true),
            is_variadic(false),
            structtype(false),
            pointer(false),
            isunsigned(false){}
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
    bool         pointer;

    //作为指针变量的时候会用到
    Token        type;
    int          size;
    bool         isunsigned;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    VarType      getVarType(deque<Context*> ctx);
    VarExpr*     getVar(deque<Context*> ctx);
    Token        getType(deque<Context*> ctx) override;
    //给返回值使用
    VarExpr*     ret;
    string       funcpkg;
    string       funcname;
};
struct ClosureExpr : public Expression {
    explicit ClosureExpr(string varname, int line, int column)
            : Expression(line, column),
              varname(move(varname)){}
    string  varname;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};

struct StructMemberExpr : public Expression {
    explicit StructMemberExpr(string varname ,int line,int column)
            : Expression(line,column),assign(false){}
    string  varname;
    string  member;
    //varname 对应的 expr
    VarExpr* var;
    bool    assign;

    Expression*    asmgen( deque<Context*> ctx) override;
    string         toString() override;
    Member*        getMember();
    Struct*        getStruct();
    Token          getType(deque<Context*> ctx) override;

    Member*   ret;
};
//&a || &p.b
struct AddrExpr   : public Expression {
    explicit AddrExpr(int line,int column)
            :Expression(line,column){}
    string package;
    string varname;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct DelRefExpr : public Expression {
    explicit DelRefExpr(int line,int column)
            : Expression(line,column){}
    Expression* expr;

    Expression* asmgen( deque<Context*> ctx) override;
    string      toString() override;
    Token       getType(deque<Context*> ctx) override;
};

struct IndexExpr : public Expression {
    explicit IndexExpr(int line, int column) 
    : Expression(line, column),is_pkgcall(false) {}

    string varname;
    Expression* index{};
    //可能进行包变量调用
    bool        is_pkgcall;
    string package;

    Expression* asmgen( deque<Context*> ctx) override;
    string      toString() override;
    Token       getType(deque<Context*> ctx) override;
};

struct BinaryExpr : public Expression {
    explicit BinaryExpr(int line, int column) : Expression(line, column) {}
    Expression*  lhs{};
    Token        opt{};
    Expression*  rhs{};

    Expression* asmgen( deque<Context*> ctx) override;
    string      toString() override;
    Token       getType(deque<Context*> ctx) override;
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

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};

struct AssignExpr : public Expression {
    explicit AssignExpr(int line, int column) : Expression(line, column) {}

    Expression*  lhs{};
    Token        opt;
    Expression*  rhs{};


    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};

struct NewClassExpr : public Expression {
    explicit NewClassExpr(int line, int column) : Expression(line, column) {}
    string package;
    string name;
    vector<Expression*> args;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct BuiltinFuncExpr : public Expression {
    explicit BuiltinFuncExpr(string name,int line,int column) 
    : Expression(line,column),funcname(name){}
    string funcname;
    Expression* expr;

    Token  from;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct NewExpr : public Expression {
    explicit NewExpr(int line, int column) : Expression(line, column) {}
    string package;
    string name;

    int    len;//申请的字节大小

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};


struct MemberExpr : public Expression {
    explicit MemberExpr(int line, int column) : Expression(line, column) {}
    string  varname;
    string  membername;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};
struct MemberCallExpr : public Expression {
    explicit MemberCallExpr(int line, int column) : Expression(line, column) {}
    string  varname;
    string  membername;

    vector<Expression*> args;

    Expression*  asmgen( deque<Context*> ctx) override;
    string       toString() override;
    Token        getType(deque<Context*> ctx) override;
};


#endif //CO_LANG_EXPRESSION_H
