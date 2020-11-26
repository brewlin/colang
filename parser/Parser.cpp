/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Parser.h"
#include "Block.h"
#include "Log.h"

/**
 * 解析 脚本文件
 * @param filename
 */
Parser::Parser(const std::string &filename,Runtime* rt,std::string package):
rt(rt),
//clear
currentFunc(nullptr),
package(package)
{
    keywords["if"]       = KW_IF;
    keywords["else"]     = KW_ELSE;
    keywords["while"]    = KW_WHILE;
    keywords["for"]      = KW_FOR;
    keywords["false"]    = KW_FALSE;
    keywords["true"]     = KW_TRUE;
    keywords["null"]     = KW_NULL;
    keywords["func"]     = KW_FUNC;
    keywords["return"]   = KW_RETURN;
    keywords["break"]    = KW_BREAK;
    keywords["continue"] = KW_CONTINUE;
    keywords["import"]   = KW_IMPORT;
    keywords["extern"]   = KW_EXTERN;
    keywords["struct"]   = KW_STRUCT;
    keywords["new"]      = KW_NEW;
    keywords["go"]       = KW_GO;
    keywords["package"]  = KW_PACKAGE;
    fs.open(filename);

    if(!fs.is_open()){
        parse_err("ParserError: can not open script file :%s\n",filename.c_str());
    }
}
Parser::~Parser()
{
    fs.close();
}

/**
 * @param rt
 */
void Parser::parse()
{
    //第一行必须得是包名
    currentToken = scan();
    parsePackageDef();

    if(getCurrentToken() == TK_EOF) return;
    do{
        //import 引入文件解析
        //解析函数定义
        if(getCurrentToken() == KW_FUNC)
        {
            auto* f = parseFuncDef(rt);
            rt->addFunc(f->name,f);
        //解析外部函数申明 extern与interpret没关系，只影响 irgen
        } else if(getCurrentToken() == KW_EXTERN){
            auto* f = parseExternDef(rt);
            rt->addFunc(f->name,f);
		//解析import
        } else if(getCurrentToken() == KW_IMPORT){
			parseImportDef();
		//解析结构体类定义
		} else if(getCurrentToken() == KW_STRUCT){
            parseStructDef();
        }else{
        //判断 StringExpr ，需要保存一份 asm 生成的时候需要提前注册到数据段
            Statement* stmt = parseStatement();
            rt->addStatement(stmt);
        }

    }while(getCurrentToken() != TK_EOF);


}
char Parser::next() {
    column++;
    return static_cast<char>(fs.get());
}
char Parser::peek() {
    return static_cast<char>(fs.peek());
}
Token Parser::getCurrentToken()const {
    return std::get<Token >(currentToken);
}
std::string Parser::getCurrentLexeme()const {
    return std::get<std::string>(currentToken);
}
/**
 * @return string package name
 */
std::string Parser::getpkgname()
{
    return package;
}
/**
 * 测试token解析
 * @param filename
 */
std::string Parser::printToken()
{
    auto  tk = scan();
    while(std::get<0>(tk) != TK_EOF){
        std::cout << "" << getTokenString(std::get<0>(tk)) << " => " << std::get<1>(tk) << "\n";
        tk = scan();
    }

}
