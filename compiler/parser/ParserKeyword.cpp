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
using namespace std;
/**
 * 解析包名是否正确
 */
void Parser::parsePackageDef()
{
    Debug("check package is correct..");
    if(scanner->curToken != KW_PACKAGE)
        parse_err("SynatxError: need :package but got :%s  line:%d column:%d\n",
                  scanner->curLex.c_str(),
                  line,column);

    //解析包名
    scanner->scan();
    assert(scanner->curToken == TK_VAR);
    std::string pkgname = scanner->curLex;
    if(pkgname != this->package){
        parse_err("SynatxError: inconsistent package name %s:%s token:%d string:%s  line:%d column:%d\n",
                  pkgname.c_str(),
                  this->package.c_str(),
                  scanner->curToken,
                  scanner->curLex.c_str(),
                  line,column);
    }
    //eat scan
    scanner->scan();
}

/**
 * 解析class定义
 */
void Parser::parseClassDef()
{
    Debug("found class start parser..");
    assert(scanner->curToken == KW_CLASS);
    //解析class名
    scanner->scan();
    //must TK_VAR
    assert(scanner->curToken == TK_VAR);
    Class *s = new Class();
    s->name  = scanner->curLex;
    scanner->scan();

    //must {
    assert(scanner->curToken == TK_LBRACE);

    scanner->scan();
    //end for }
    while(scanner->curToken != TK_RBRACE){
        //定义成员变量
        if(scanner->curToken == TK_VAR){
            s->members.push_back(scanner->curLex);
            scanner->scan();

        // 定义成员函数函数
        }else if(scanner->curToken == KW_FUNC){
            //解析成员函数
            Function *f = parseFuncDef(true);
            assert(f != nullptr);
            //成员函数
            f->isObj = true;
            f->structname = s->name;
            s->funcs.push_back(f);
        }else{
            parse_err("SynatxError: token:%d string:%s  line:%d column:%d\n",
                scanner->curToken,
                scanner->curLex.c_str(),
                line,column);
        }

    }
    //追加到当前package 下去管理
    pkg->addClass(s->name,s);
    //eat }
    scanner->scan();
}
/**
 * 解析struct 内存结构
 */
void Parser::parseStructDef()
{
    // struct header
    // {
    // 	i8   a
    // 	i16  b
    // 	i32  c:20
    // 	i32  c:12
    // 	u64 d
    // }
    Debug("found struct start parser..");
    assert(scanner->curToken == KW_STRUCT);
    //解析结构体名
    scanner->scan();
    //must TK_VAR
    assert(scanner->curToken == TK_VAR);
    Struct* s = new Struct();
    s->name  = scanner->curLex;
    scanner->scan();
    //must {
    assert(scanner->curToken == TK_LBRACE);
    scanner->scan();
    //end for }
    int idx = 0;
    while(scanner->curToken != TK_RBRACE)
    {
        //每次都是一对一对的解析
        //key 必须是 i8 - u64的结构
        assert(scanner->curToken >= KW_I8 && scanner->curToken <= KW_U64);
        Member *member = new Member();
        member->idx    = idx ++;
        member->type = scanner->curToken;
        member->size = typesize[scanner->curToken];

        scanner->scan();
        assert(scanner->curToken == TK_VAR);
        member->name = scanner->curLex;

        //这里可能还有: 冒号  可能是一个位图
        scanner->scan();
        if(scanner->curToken == TK_COLON){
            scanner->scan();
            assert(scanner->curToken == LIT_INT);
            member->bitfield = true;
            member->bitwidth = atoi(scanner->curLex.c_str());
            scanner->scan();
        }
        s->member.push_back(member);
    }
    s->compute();
    //追加到当前package 下去管理
    pkg->addStruct(s->name,s);
    //eat }
    scanner->scan();
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
    assert(scanner->curToken == KW_FUNC);
    //获取函数名|或者直接跳过
    scanner->scan();
    auto* node = new Function;
    //set parser
    node->parser = this;
    //start parse function
    currentFunc = node;

    //闭包没有函数名
    if(!closure){
        //检查是否重复定义
        if(hasFunc(scanner->curLex))
            parse_err("SyntaxError: already define function :%s\n",scanner->curLex.c_str());
        node->name = scanner->curLex;
        //指向 func name'(') 括号
        scanner->scan();
    }

    assert(scanner->curToken == TK_LPAREN);

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
    assert(scanner->curToken == KW_EXTERN);
    auto* node     = new Function;
    node->isExtern = true;
    node->parser   = this;

    //extern 一般是调用系统库 所以 需要固定返回类型
    scanner->scan();
    node->rettype  = scanner->curLex;

    //获取函数名
    scanner->scan();
    node->name     = scanner->curLex;
    node->block    = nullptr;

    //指向 func name'(') 括号
    scanner->scan();
    assert(scanner->curToken == TK_LPAREN);
    //解析函数参数
    scanner->scan();
    //是否解析到 ')'
    if(scanner->curToken == TK_RPAREN){
        scanner->scan();
        return node;
    }
    //解析所有括号内的参数 (..,..,..)
    while(scanner->curToken != TK_RPAREN){
        //继续下一个token读取
        scanner->scan();
    }
    //是否闭合
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    return node;
}
/**
 * 解析注释里的附加信息如:
 * 1. #:link -lhttp
 * 在编译链接过程会将http静态库链接，且路径默认为 /usr/local/lib/colib ,也可以手动指定
 */
void Parser::parseExtra() {
    Debug("found #: parser..");
    assert(scanner->curToken == KW_EXTRA);
    //scan one
    scanner->scan();
    //解析到了链接信息
    if(scanner->curLex == "link"){
        auto lines = scanner->consumeLine();
        lines = lines.substr(0,lines.size());
        //推到数组里去
        links.push_back(lines);
        return;
    }
    //没有命中 说明格式错了, 直接去掉当前行
    scanner->consumeLine();
}

/**
 * 解析 import: import string
 * 1. 解析 import {name}
 * 2. new Parser(name)
 */
void Parser::parseImportDef()
{
    Debug("found import.start parser..");
    assert(scanner->curToken == KW_IMPORT);
    //scan one
     scanner->scan();
    //must tk_var
    assert(scanner->curToken == TK_VAR);
    string path = scanner->curLex;
    string package(path);
    bool multi = false;
    //可能是多级包结构，p.p1.p2.p3需要判断是否需要多层解析
    scanner->scan();
    while(scanner->curToken == TK_DOT){
        //eat .
        scanner->scan();
        // must be var
        assert(scanner->curToken == TK_VAR);
        // FIXEME: platform directory seprate
        path += "_" + scanner->curLex;
        package = scanner->curLex;
        multi = true;
        //eat one
        scanner->scan();
    }

    //检查包是否已经解析过了
    if(!Package::packages[path]){
        Package *pkg = new Package(package,path,multi);
        //扫描包下的源码，进行解析
        if(!pkg->parse()){
            parse_err("SyntaxError: package:%s not exist in local or global "
                      " line:%d column:%d\n",
                path.c_str(),line,column);
        }
        Package::packages[path] = pkg;
    }
    //每一次引入都要做一个包名映射，不是多级包的时候可能 k == v
    import[package] = path;

}
/**
 * 1. 解析 全局定义 变量
 * 2. 也有可能是 Class::func
 * package import func 之外的部分
 * 
 */
void Parser::parseGlobalDef()
{
    if(scanner->curToken != TK_VAR){
        parse_err("SyntaxError: global var define invalid  "
                      " line:%d column:%d file:%s\n",line,column,filepath.c_str());
    }
    auto var = scanner->curLex;
    //去掉标识符
    scanner->scan();
    //说明是 Class::func定义
    if(scanner->curToken == TK_COLON){
        scanner->scan();
        assert(scanner->curToken == TK_COLON);
        // 兼容funcParser 手动更新当前为kw_func
        scanner->curToken  = KW_FUNC;
        //解析成员函数
        Function *f = parseFuncDef(true);
        assert(f != nullptr);
        pkg->addClassFunc(var,f);
        return;
    }
    VarExpr* varexpr = new VarExpr(var,line,column);
    //没有在函数作用内之外的都为全局变量，存储在静态代码区
    gvars[var] = varexpr;
    varexpr->is_local = false;
    varexpr->package  = this->package;
}