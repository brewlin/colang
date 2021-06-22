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
    explicit Parser(const std::string& filepath,Package* rt,std::string package);
    ~Parser();
    //获取包名
    std::string getpkgname();
    //执行文件解析生成ast树
    std::string printToken();
    void parse();
    void asmgen();

    //存储结构体定义
    std::unordered_map<std::string,Class*>     classs;
    //全局变量
    std::unordered_map<std::string,VarExpr*>   gvars;
    //存储全局函数
    std::unordered_map<std::string,Function*>  funcs;
    std::unordered_map<std::string,Function*>  extern_funcs;
    //保存全局 静态字符串
    std::vector<StringExpr*>                   strs;
    //保存全局的 link 连接附加信息
    std::vector<std::string>                   links;
public:
    void            addFunc(const std::string &name,   Function *f);
    bool            hasFunc(const std::string &name,   bool is_extern = false);
    Function*       getFunc(const std::string &name,   bool is_extern);
    void            addClass(const std::string &name, Class *f);
    bool            hasClass(const std::string &name);
    Class*          getClass(const std::string &name);

private:
    //get|peek next char
    char            next();
    char            peek();
    std::string     getline();
    Token           getCurrentToken()const;
    Token           getPrevToken()const ;
    std::string     getCurrentLexeme()const;

    //parse keywords
    void 			parseImportDef();
    Function*       parseFuncDef(bool member = false,bool closure = false);
    Function*       parseExternDef();
    void            parseClassDef();
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
    Expression*     parseVarExpr(std::string var);
    Expression*     parseFuncallExpr(std::string callname);
    Expression*     parseIndexExpr(std::string varname);

    short           precedence(Token op);
    Block*          parseBlock();

    void                            scan();
    std::tuple <Token ,std::string> get_next();
    std::tuple <Token ,std::string> parseNumber(char first);
    std::tuple <Token ,std::string> parseKeyword(char c);
    std::tuple <Token ,std::string> parseMulOrDelref(char c);

    std::vector<std::string> parseParameterList();
    std::vector<Statement*>  parseStatementList();
public:
    static int count;
    //记录当前词法分析行|列
    int line = 1;
    int column = 0;
    int fileno = 1;
    //打开脚本文件
    std::fstream fs;
    //保存关键字
    std::unordered_map<std::string,Token > keywords;
    //当前token
    std::string curLex;
    Token       curToken;
    //之前的token
    std::string preLex;
    Token       preToken;
    //当前所属的包
    Package* pkg;
	//当前function
	Function* currentFunc;
	//当前包名
	std::string package;
    std::string filename;
    std::string asmfile;
    std::string filepath;

};



#endif //CO_LANG_PARSER_H
