/**
 *@ClassName ParserFunc
 *@Author brewlin
 *@Date 2020/9/27 0027 上午 11:41
 *@Version 1.0
 **/

#include "Parser.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Package.h"
/**
 * 解析包名是否正确
 */
void Parser::parsePackageDef()
{
    Debug("check package is correct..");
    if(getCurrentToken() != KW_PACKAGE)
        parse_err("SynatxError: need :package but got :%s  line:%d column:%d\n",
                  getCurrentLexeme().c_str(),
                  line,column);

    //解析包名
    currentToken = scan();
    assert(getCurrentToken() == TK_VAR);
    std::string pkgname = getCurrentLexeme();
    if(pkgname != this->package){
        parse_err("SynatxError: inconsistent package name token:%d string:%s  line:%d column:%d\n",
                  getCurrentToken(),
                  getCurrentLexeme().c_str(),
                  line,column);
    }
    //eat scan
    currentToken = scan();
}

/**
 * 解析结构体定义
 */
void Parser::parseClassDef()
{
    Debug("found struct.start parser..");
    assert(getCurrentToken() == KW_CLASS);
    //解析结构体名
    currentToken = scan();
    //must TK_VAR
    assert(getCurrentToken() == TK_VAR);
    Class *s = new Class();
    s->name  = getCurrentLexeme();
    currentToken = scan();

    //must {
    assert(getCurrentToken() == TK_LBRACE);

    currentToken = scan();
    //end for }
    while(getCurrentToken() != TK_RBRACE){
        //定义成员变量
        if(getCurrentToken() == TK_VAR){
            s->members.push_back(getCurrentLexeme());
            currentToken = scan();

        // 定义成员函数函数
        }else if(getCurrentToken() == KW_FUNC){
            //解析成员函数
            Function *f = parseFuncDef(true);
            assert(f != nullptr);
            //成员函数
            f->isObj = true;
            f->structname = s->name;
            s->funcs.push_back(f);
        }else{
            parse_err("SynatxError: token:%d string:%s  line:%d column:%d\n",
                getCurrentToken(),
                getCurrentLexeme().c_str(),
                line,column);
        }

    }
    this->addClass(s->name,s);
    //eat }
    currentToken = scan();
}
/**
 * 解析函数表达式
 * @param member 表示当前函数是否为成员函数
 * @return
 */
Function* Parser::parseFuncDef(bool member,bool closure)
{
    Debug("found function. start parser..");
    //当前是否已经解析到 func 关键字
    assert(getCurrentToken() == KW_FUNC);
    //获取函数名|或者直接跳过
    currentToken = scan();
    auto* node = new Function;
    //set parser
    node->parser = this;
    //start parse function
    currentFunc = node;

    //闭包没有函数名
    if(!closure){
        //检查是否重复定义
        if(hasFunc(getCurrentLexeme()))
            parse_err("SyntaxError: already define function :%s\n",getCurrentLexeme().c_str());
        node->name = getCurrentLexeme();
        //指向 func name'(') 括号
        currentToken = scan();
    }

    assert(getCurrentToken() == TK_LPAREN);

    //如果为成员函数需要填充第一个 this 参数
    if(member){
        VarExpr* var = new VarExpr("this",line,column);
        node->params_var["this"] = var;
        node->params_order_var.push_back(var);
        node->params.push_back("this");
    }

    auto params  = parseParameterList();
    //解析函数参数
    node->params.insert(node->params.end(),params.begin(),params.end());
    //解析block 函数主体表达式
    node->block = parseBlock();
    //leave parse function
    currentFunc = nullptr;
    return node;
}

/**
 * 解析函数表达式
 * @param rt
 * @return
 */
Function* Parser::parseExternDef()
{
    Debug("found extern .start parser..");
    //当前是否已经解析到 func 关键字
    assert(getCurrentToken() == KW_EXTERN);
    auto* node     = new Function;
    node->isExtern = true;
    node->parser   = this;

    //extern 一般是调用系统库 所以 需要固定返回类型
    currentToken   = scan();
    node->rettype  = getCurrentLexeme();

    //获取函数名
    currentToken   = scan();
    node->name     = getCurrentLexeme();

    //指向 func name'(') 括号
    currentToken   = scan();
    assert(getCurrentToken() == TK_LPAREN);
    //解析函数参数
    node->params   = parseParameterList();
    //解析block 函数主体表达式
    node->block    = nullptr;
    return node;
}
/**
 * 解析注释里的附加信息如:
 * 1. #:link -lhttp
 * 在编译链接过程会将http静态库链接，且路径默认为 /usr/local/lib/colib ,也可以手动指定
 */
void Parser::parseExtra() {
    Debug("found #: parser..");
    assert(getCurrentToken() == KW_EXTRA);
    //scan one
    currentToken = scan();
    //解析到了链接信息
    if(getCurrentLexeme() == "link"){
        auto lines = getline();
        lines = lines.substr(0,lines.size());
        //推到数组里去
        links.push_back(lines);
        return;
    }
    //没有命中 说明格式错了, 直接去掉当前行
    getline();
}

/**
 * 解析 import: import "string"
 * 1. 解析 import {name}
 * 2. new Parser(name)
 */
void Parser::parseImportDef()
{
    Debug("found import.start parser..");
    assert(getCurrentToken() == KW_IMPORT);
    //scan one
    currentToken =  scan();
    //must tk_var
    assert(getCurrentToken() == TK_VAR);
    std::string package = getCurrentLexeme();
    //检查包是否已经解析过了
    if(!Package::packages[package]){
        Package *pkg = new Package(package);
        //扫描包下的源码，进行解析
        if(!pkg->parse()){
            parse_err("SyntaxError: package:%s not exist in local or global "
                      " line:%d column:%d\n",
                package.c_str(),line,column);
        }
        Package::packages[package] = pkg;
    }
    //eat next scan
    currentToken = scan();

}
/**
 * 解析 全局定义
 * package import func 之外的部分
 * 
 */
void Parser::parseGlobalDef()
{
    if(getCurrentToken() != TK_VAR){
        parse_err("SyntaxError: global var define invalid  "
                      " line:%d column:%d\n",line,column);
    }
    auto var = getCurrentLexeme();
    //去掉标识符
    currentToken = scan();

    VarExpr* varexpr = new VarExpr(var,line,column);
    //没有在函数作用内之外的都为全局变量，存储在静态代码区
    gvars[var] = varexpr;
    varexpr->is_local = false;
    varexpr->package  = this->package;
}