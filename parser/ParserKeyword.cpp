/**
 *@ClassName ParserFunc
 *@Author brewlin
 *@Date 2020/9/27 0027 上午 11:41
 *@Version 1.0
 **/

#include "Parser.h"
#include "Log.h"
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
            panic("SynatxError: token:%d string:%s  line:%d column:%d\n",
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
 * @param ctx
 * @return
 */
Function* Parser::parseFuncDef(Context *ctx)
{
    Debug("found function. start parser..");
    //当前是否已经解析到 func 关键字
    assert(getCurrentToken() == KW_FUNC);
    //获取函数名
    currentToken = next();
    //检查是否重复定义
    if(ctx->hasFunc(getCurrentLexeme()))
        panic("SyntaxError: already define function :%s\n",getCurrentLexeme().c_str());
    auto* node = new Function;
    node->name = getCurrentLexeme();
    //指向 func name'(') 括号
    currentToken = next();
    assert(getCurrentToken() == TK_LPAREN);
    //解析函数参数
    node->params = parseParameterList();
    //将变量名单独保存一份 for asm generate
    for(auto &s:node->params){
        auto p = new StringExpr(line,column);
        p->literal = s;
        node->params_var.push_back(p);
    }
    //解析block 函数主体表达式
    node->block = parseBlock();

    //需要将 block 里的 本地变量保存一份，在 asm create 需要计算栈空间
    for(auto* p:node->block->stmts){
        if(typeid(*p) == typeid(ExpressionStmt)){
            ExpressionStmt* st = dynamic_cast<ExpressionStmt*>(p);
            if(typeid(st->expr) == typeid(IdentExpr))
                node->locals.push_back(st->expr);
        }
    }
    return node;
}

/**
 * 解析函数表达式
 * @param ctx
 * @return
 */
Function* Parser::parseExternDef(Context *ctx)
{
    Debug("found extern .start parser..");
    //当前是否已经解析到 func 关键字
    assert(getCurrentToken() == KW_EXTERN);
    auto* node = new Function;
    node->isExtern = true;

    //extern 一般是调用系统库 所以 需要固定返回类型
    currentToken = next();
    node->rettype = getCurrentLexeme();

    //获取函数名
    currentToken = next();
    node->name = getCurrentLexeme();

    //指向 func name'(') 括号
    currentToken = next();
    assert(getCurrentToken() == TK_LPAREN);
    //解析函数参数
    node->params = parseParameterList();
    //解析block 函数主体表达式
    node->block = nullptr;
    return node;
}

/**
 * 解析 import: import "string"
 * 1. 解析 import {name}
 * 2. new Parser(name)
 */
void Parser::parseImport()
{
    Debug("found import.start parser..");
    assert(getCurrentToken() == KW_IMPORT);
    //next one
    currentToken =  next();
    //must tk_ident
    assert(getCurrentToken() == TK_IDENT);
    //parser
    std::string srcpath = std::getenv("DO_SRC");
    Debug("Parser: ENV PATH  DO_SRC:%s",srcpath.c_str());
    if(srcpath.empty())
        srcpath = "./";
    std::string abpath  = srcpath+"/"+getCurrentLexeme();
    Debug("Parser: new import file:%s",abpath.c_str());
    Parser ipt(abpath,rt);
    currentToken = next();
    ipt.parse();

}
