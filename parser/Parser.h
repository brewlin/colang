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
#include "Runtime.h"
#include "Expression.h"
#include "Statement.h"
#include <cstdlib>

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

private:
    //get|peek next char
    char            next();
    char            peek();
    Token           getCurrentToken()const;
    std::string     getCurrentLexeme()const;

    //parse keywords
    void 			parseImportDef();
    Function*       parseFuncDef(Runtime* rt);
    Function*       parseExternDef(Runtime* rt);
    void            parseStructDef();
    void            parsePackageDef();
    void            parseGlobalDef();

    //parse statement
    Statement*      parseStatement();
    ExpressionStmt* parseExpressionStmt();
    IfStmt*         parseIfStmt();
    WhileStmt*      parseWhileStmt();
    ReturnStmt*     parseReturnStmt();

    //parse expression
    Expression*     parseExpression(short oldPrecedence = 1);
    Expression*     parseUnaryExpr();
    Expression*     parsePrimaryExpr();
    Expression*     parseVarExpr();
    Expression*     parseFuncallExpr(std::string callname);
    Expression*     parseIndexExpr(std::string varname);

    short           precedence(Token op);
    Block*          parseBlock();

    std::tuple <Token ,std::string> scan();
    std::tuple <Token ,std::string> parseNumber(char first);
    std::tuple <Token ,std::string> parseKeyword(char c);
    std::tuple <Token ,std::string> parseMulOrDelref(char c);

    std::vector<std::string> parseParameterList();
    std::vector<Statement*>  parseStatementList();
private:
    //记录当前词法分析行|列
    int line = 1;
    int column = 0;
    //打开脚本文件
    std::fstream fs;
    //保存关键字
    std::unordered_map<std::string,Token > keywords;
    //当前token
    std::tuple<Token ,std::string> currentToken;
    //当前所属的包
    Package* pkg;
	//当前function
	Function* currentFunc;
	//当前包名
	std::string package;
    std::string filename;

};



#endif //CO_LANG_PARSER_H
