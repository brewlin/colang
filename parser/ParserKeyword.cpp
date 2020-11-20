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
namespace filesys = std::experimental::filesystem;
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
    currentToken = next();
    assert(getCurrentToken() == TK_IDENT);
    std::string pkgname = getCurrentLexeme();
    if(pkgname != this->package){
        parse_err("SynatxError: inconsistent package name token:%d string:%s  line:%d column:%d\n",
                  getCurrentToken(),
                  getCurrentLexeme().c_str(),
                  line,column);
    }
    //eat next
    currentToken = next();
}

/**
 * 解析结构体定义
 */
void Parser::parseStructDef()
{
    Debug("found struct.start parser..");
    assert(getCurrentToken() == KW_STRUCT);
    //解析结构体名
    currentToken = next();
    //must TK_IDENT
    assert(getCurrentToken() == TK_IDENT);
    Struct *s = new Struct();
    s->name  = getCurrentLexeme();
    currentToken = next();

    //must {
    assert(getCurrentToken() == TK_LBRACE);

    currentToken = next();
    //end for }
    while(getCurrentToken() != TK_RBRACE){
        //定义成员变量
        if(getCurrentToken() == TK_IDENT){
//            s->members.push_back(new IdentDeclaration(getCurrentLexeme(),line,column));
            s->members.push_back(getCurrentLexeme());
            currentToken = next();

        // 定义成员函数函数
        }else if(getCurrentToken() == KW_FUNC){
            Function *f = parseFuncDef(rt);
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
    rt->addStruct(s->name,s);
    //eat }
    currentToken = next();
}
/**
 * 解析函数表达式
 * @param rt
 * @return
 */
Function* Parser::parseFuncDef(Runtime* rt)
{
    Debug("found function. start parser..");
    //当前是否已经解析到 func 关键字
    assert(getCurrentToken() == KW_FUNC);
    //获取函数名
    currentToken = next();
    //检查是否重复定义
    if(rt->hasFunc(getCurrentLexeme()))
        parse_err("SyntaxError: already define function :%s\n",getCurrentLexeme().c_str());
    auto* node = new Function;

    //set parser
    node->parser = this;
    //start parse function
    currentFunc = node;

    node->name = getCurrentLexeme();
    //指向 func name'(') 括号
    currentToken = next();
    assert(getCurrentToken() == TK_LPAREN);
    //解析函数参数
    node->params = parseParameterList();
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
Function* Parser::parseExternDef(Runtime* rt)
{
    Debug("found extern .start parser..");
    //当前是否已经解析到 func 关键字
    assert(getCurrentToken() == KW_EXTERN);
    auto* node     = new Function;
    node->isExtern = true;
    node->parser   = this;

    //extern 一般是调用系统库 所以 需要固定返回类型
    currentToken   = next();
    node->rettype  = getCurrentLexeme();

    //获取函数名
    currentToken   = next();
    node->name     = getCurrentLexeme();

    //指向 func name'(') 括号
    currentToken   = next();
    assert(getCurrentToken() == TK_LPAREN);
    //解析函数参数
    node->params   = parseParameterList();
    //解析block 函数主体表达式
    node->block    = nullptr;
    return node;
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
    //next one
    currentToken =  next();
    //must tk_ident
    assert(getCurrentToken() == TK_IDENT);

    //parser 当前目录
    std::string abpath = filesys::current_path();
    abpath += "/" + getCurrentLexeme();
    std::error_code ec;

    //先找当前，再去找全局
    if (!filesys::is_directory(abpath, ec)){
        //去全局目录库找
        std::string srcpath = std::getenv("DO_SRC");
        Debug("Parser: ENV PATH  DO_SRC:%s",srcpath.c_str());
        if(srcpath.empty())
            srcpath = "./";
        abpath  = srcpath+"/"+getCurrentLexeme();
        Debug("Parser: package import:%s",abpath.c_str());
        if (!filesys::is_directory(abpath, ec))
            parse_err("ParserError: package:%s not exist in local or global "
                      " line:%d column:%d\n",
                getCurrentLexeme().c_str(),line,column);
    }

    //包名一般是一个目录，当前会遍历目录下所有的文件进行解析
    for(auto& p: filesys::directory_iterator(abpath)){
        std::error_code ec;
        if (filesys::is_regular_file(p.path(), ec)){
            string filepath = p.path();
            string ext = filepath.substr(filepath.size()-3,filepath.size() - 1);
            if(ext != ".do") continue;

            //不需要释放，在汇编生成的时候需要用到
            Parser *ipt = new Parser(filepath,rt,getCurrentLexeme());
            ipt->parse();
        }
        if (ec)
            parse_err("RuntimeError: package import failed :%s\n",ec.message().c_str());
    }

    //get next
    currentToken = next();

}
