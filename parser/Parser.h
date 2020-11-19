/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef LANG_PARSER_H
#define LANG_PARSER_H
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
    explicit Parser(const std::string& filename,Runtime* rt,std::string package);
    static void printLex(const std::string& filename);
    ~Parser();

    //获取包名
    std::string getpkgname();
    //执行文件解析生成ast树
    void parse();

private:
    //读取下一个字符
    inline char getNextChar(){
        column++;
        return static_cast<char>(fs.get());
    }
    //读取下一个字符 且指针不改变位置
    inline char peekNextChar(){ return static_cast<char>(fs.peek());}
    inline Token getCurrentToken()const{ return std::get<Token >(currentToken);}
    inline std::string getCurrentLexeme()const{ return std::get<std::string>(currentToken);}

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

    //parse keywords
    void 			parseImport();
    Function*       parseFuncDef(Runtime* rt);
    Function*       parseExternDef(Runtime* rt);
    void            parseStructDef();
    void            parsePackageDef();

    short           precedence(Token op);
    Block*          parseBlock();

    std::tuple <Token ,std::string> parseNumber(char first);
    std::tuple <Token ,std::string> parseKeyword(char c);

    std::tuple <Token ,std::string> next();
    std::vector<std::string> parseParameterList();
    std::vector<Statement*> parseStatementList();
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
	//全局ast树运行时
	Runtime* rt;
	//当前function
	Function* currentFunc;
	//当前包名
	std::string package;
};



#endif //LANG_PARSER_H
