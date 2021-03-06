/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef CO_LANG_PARSER_H
#define CO_LANG_PARSER_H
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "Ast.h"
#include <memory>
#include <unordered_map>
#include "Utils.h"
#include <vector>
#include <cassert>
#include "Expression.h"
#include "Statement.h"
#include <cstdlib>
#include "Package.h"
#include "Scanner.h"
using namespace std;

struct Function;
struct Block;
/**
 * 词法分析骨架
 */
class Parser {
public:
    /**
     * @param filename  要打开的文件名
     * @param rt        全局table表 存储了所有的函数、变量等
     * @param package   当前文件对应的包名
     */
    explicit Parser(const string& filepath,Package* rt,string package,string full_package);
    ~Parser();
    //获取包名
    string getpkgname();
    void parse();
    void asmgen();

    //全局变量
    unordered_map<string,VarExpr*>   gvars;
    //存储全局函数
    unordered_map<string,Function*>  funcs;
    unordered_map<string,Function*>  extern_funcs;
    //保存全局 静态字符串
    vector<StringExpr*>                   strs;
    //保存全局的 link 连接附加信息
    vector<string>                   links;
public:
    void            addFunc(const string &name,   Function *f);
    bool            hasFunc(const string &name,   bool is_extern = false);
    Function*       getFunc(const string &name,   bool is_extern);

private:
    //parse keywords
    void 			parseImportDef();
    Function*       parseFuncDef(bool member = false,bool closure = false);
    Function*       parseExternDef();
    void            parseClassDef();
    void            parseStructDef();
    void            parsePackageDef();
    void            parseGlobalDef();
    void            parseExtra();

    //parse statement
    Statement*      parseStatement();
    ExpressionStmt* parseExpressionStmt();
    IfStmt*         parseIfStmt();
    ForStmt*        parseForStmt();
    WhileStmt*      parseWhileStmt();
    ReturnStmt*     parseReturnStmt();

    //parse expression
    Expression*     parseExpression(short oldPrecedence = 1);
    Expression*     parseUnaryExpr();
    Expression*     parsePrimaryExpr();
    Expression*     parseVarExpr(string var);
    Expression*     parseFuncallExpr(string callname);
    Expression*     parseIndexExpr(string varname);
    Expression*     parseNewExpr();

    Block*          parseBlock();

    vector<string> parseParameterList();
    vector<Statement*>  parseStatementList();

    void            check(bool check);
public:
    static int count;
    //记录当前词法分析行|列
    int line = 1;
    int column = 0;
    int fileno = 1;
    //当前所属的包
    Package* pkg;
	//当前function
	Function* currentFunc;
	//当前包名
    string    full_package;
	string    package;
    string    filename;
    string    asmfile;
    string    filepath;
    //当前scanner
    Scanner*  scanner;
    //引入的包名做一个映射以支持多级包名调用
    unordered_map<string,string> import;
};
#endif //CO_LANG_PARSER_H
