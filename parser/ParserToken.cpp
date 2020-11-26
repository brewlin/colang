/**
 *@ClassName ParserToken
 *@Author brewlin
 *@Date 2020/11/19 0019 上午 11:05
 *@Version 1.0
 **/

#include "Parser.h"
#include "Block.h"
#include "Log.h"


// parseNumber
std::tuple<Token,std::string> Parser::parseNumber(char first)
{
    std::string lexeme{first};
    bool isDouble = false;
    char cn = peek();
    char c  = first;
    //每一次遍历先判断下一个数是不是数字，如果不是则中断当前解析，不然会浪费下一个字符
    //peek 则不会出现这种问题
    while((cn >= '0' && cn <= '9') || (!isDouble && cn == '.')){
        if(c == '.')
            isDouble = true;
        c = next();
        cn = peek();
        lexeme += c;
    }
    return !isDouble ? make_tuple(LIT_INT,lexeme)
                     : make_tuple(LIT_DOUBLE,lexeme);
}
std::tuple<Token,std::string> Parser::parseKeyword(char c)
{
    std::string lexeme{c};
    char cn;

    cn = peek();
    while((cn >= 'a' && cn <= 'z') || (cn >= 'A' && cn <= 'Z') || cn == '_' || (cn >= '0' && cn <= '9')){
        c = next();
        lexeme += c;
        cn = peek();
    }
    //返回标识符
    auto result = keywords.find(lexeme);
    return result != keywords.end()
           ? std::make_tuple(result->second,lexeme)
           : std::make_tuple(TK_IDENT,      lexeme);
}
//解析 * 运算符号 或者是解引用
//解引用非常危险 需要注意只能在和c函数调用中而存在
std::tuple<Token,std::string> Parser::parseMulOrDelref(char c)
{
    char cn = peek();
    // a *= b
    if (cn == '=') {
        c = next();
        return std::make_tuple(TK_MUL_AGN, "*=");
    }
    //说明是个解引用操作
    // call(*a,*b)
    if((cn >= 'a' && cn <= 'z') || (cn >= 'A' && cn <= 'Z')){
        return std::make_tuple(TK_DELREF, "*");
    }
    return std::make_tuple(TK_MUL, "*");
}
//逐字解析 直到找到合法的token
std::tuple<Token,std::string> Parser::scan() {
    char c = next();
    //make_*开头一般是创建一个 智能指针
    if(c == EOF)
        return std::make_tuple(TK_EOF,"");

    //忽略回车、换行、空格、tab
    blank:
    if(c == ' ' || c == '\n' || c == '\r' || c == '\t'){
        while(c == ' ' || c == '\n' ||c == '\r' || c == '\t'){
            if(c == '\n'){
                line++;
                column = 0;
            }
            c = next();
        }
        //读取到了文件结尾了
        if(c == EOF)
            return std::make_tuple(TK_EOF,"");
    }
    //    去掉注释
    //TODO: support // or /* */
    if(c == '#'){
        comment:
        while(c != '\n' && c != EOF)
            c = next();
        //如果代码有空行则跳过行
        while(c == '\n'){
            line++;
            column = 0;
            c = next();
        }
        if(c == '#')
            goto comment;
        if(c == EOF)
            return std::make_tuple(TK_EOF,"");
        //从头解析
        goto blank;

    }
    //解析数字 int or double
    if(c >= '0' && c <= '9'){
        return parseNumber(c);
    }
    //解析关键字
    if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'){
        return parseKeyword(c);
    }
    //解析 .
    if(c == '.'){
        std::string lexeme;
        lexeme += c;
        return std::make_tuple(TK_DOT,lexeme);
    }
    if(c == ':'){
        std::string lexeme;
        lexeme += c;
        return std::make_tuple(TK_COLON,lexeme);
    }
    //字符解析 只支持单个字符:'c'
    if (c == '\'') {
        std::string lexeme;
        lexeme += next();
        if (peek() != '\'') {
            parse_err("SynxaxError: a character literal should surround with single-quote\n");
        }
        c = next();
        return std::make_tuple(LIT_CHAR, lexeme);
    }
    //字符串解析 str = " .... "
    if(c == '\"'){
        std::string lexeme;
        char cn = peek();
        while(cn != '"'){
            c = next();
            lexeme += c;
            cn = peek();
        }
        c = next();
        return std::make_tuple(LIT_STR,lexeme);
    }
    //parser [] {} () ,
    if(c == '[') return std::make_tuple(TK_LBRACKET,"[");
    if(c == ']') return std::make_tuple(TK_RBRACKET,"]");
    if(c == '{') return std::make_tuple(TK_LBRACE  ,"{");
    if(c == '}') return std::make_tuple(TK_RBRACE  ,"}");
    if(c == '(') return std::make_tuple(TK_LPAREN  ,"(");
    if(c == ')') return std::make_tuple(TK_RPAREN  ,")");
    if(c == ',') return std::make_tuple(TK_COMMA   ,",");

    //parser + += - -= * *= / /+
    if(c == '+'){
        char cn = peek();
        if(cn == '='){
            c = next();
            return std::make_tuple(TK_PLUS_AGN,"+=");
        }
        return std::make_tuple(TK_PLUS        ,"+");
    }
    if(c == '-'){
        char cn = peek();
        if(cn == '='){
            c = next();
            return std::make_tuple(TK_MINUS_AGN,"-=");
        }else if(cn >= '0' && cn <= '9'){
            //负数
            return parseNumber('-');
        }
        return std::make_tuple(TK_MINUS,"-");
    }
    if(c == '*')
        return parseMulOrDelref(c);

    if(c == '/') {
        char cn = peek();
        if (cn == '=') {
            c = next();
            return std::make_tuple(TK_DIV_AGN, "/=");
        }
        return std::make_tuple(TK_DIV, "/");
    }
    if(c == '%') {
        char cn = peek();
        if (cn == '=') {
            c = next();
            return std::make_tuple(TK_MOD_AGN, "%=");
        }
        return std::make_tuple(TK_MOD, "%");
    }
    //parse ~ = == ! | &  > <
    if (c == '~') return std::make_tuple(TK_BITNOT,"~");
    if (c == '=') {
        if (peek() == '=') {
            c = next();
            return std::make_tuple(TK_EQ, "==");
        }
        return std::make_tuple(TK_ASSIGN, "=");
    }
    if (c == '!') {
        if (peek() == '=') {
            c = next();
            return std::make_tuple(TK_NE, "!=");
        }
        return std::make_tuple(TK_LOGNOT, "!");
    }
    if (c == '|') {
        if (peek() == '|') {
            c = next();
            return std::make_tuple(TK_LOGOR, "||");
        }
        if (peek() == '=') {
            c = next();
            return std::make_tuple(TK_BITOR_AGN, "|=");
        }
        return std::make_tuple(TK_BITOR, "|");
    }
    if (c == '&') {
        if (peek() == '&') {
            c = next();
            return std::make_tuple(TK_LOGAND, "&&");
        }
        if (peek() == '=') {
            c = next();
            return std::make_tuple(TK_BITAND_AGN, "&=");
        }
        return std::make_tuple(TK_BITAND, "&");
    }
    if (c == '>') {
        //>=
        if (peek() == '=') {
            c = next();
            return std::make_tuple(TK_GE, ">=");
        }
        //>>
        if (peek() == '>') {
            c = next();
            //>>=
            if (peek() == '=') {
                c = next();
                return std::make_tuple(TK_SHIFTR_AGN, ">>=");
            }
            return std::make_tuple(TK_SHIFTR, ">>");
        }

        return std::make_tuple(TK_GT, ">");
    }
    if (c == '<') {
        if (peek() == '=') {
            c = next();
            return std::make_tuple(TK_LE, "<=");
        }
        if (peek() == '<') {
            c = next();
            //<<=
            if (peek() == '=') {
                c = next();
                return std::make_tuple(TK_SHIFTL_AGN, "<<=");
            }
            return std::make_tuple(TK_SHIFTL, "<<");
        }
        return std::make_tuple(TK_LT, "<");
    }
    //匹配失败 直接print后 exit
    parse_err("SynxaxError: unknown token '%c' line:%d column:%d\n",c,line,column);
    return std::make_tuple(INVALID,"invalid");
}
/**
 * 解析优先级
 * @param op
 * @return
 */
short Parser::precedence(Token op)
{
    switch (op) {
        case TK_LOGOR:
            return 1;
        case TK_LOGAND:
            return 2;
        case TK_EQ:
        case TK_NE:
        case TK_GT:
        case TK_GE:
        case TK_LT:
        case TK_LE:
            return 3;
        case TK_PLUS:
        case TK_MINUS:
        case TK_BITOR:
            return 4;
        case TK_MUL:
        case TK_MOD:
        case TK_DIV:
        case TK_BITAND:
        case TK_SHIFTL:
        case TK_SHIFTR:
            return 5;
        default:
            // Lowest precedence
            return 0;
    }

}


/**
 * 一般解析函数内 {}里的语句列表
 * 逐行记录到 vector中
 * @return
 */
std::vector<Statement*> Parser::parseStatementList()
{
    std::vector<Statement*> node;
    Statement* p;
    while((p = parseStatement()) != nullptr)
        node.push_back(p);
    return node;
}
/**
 * 解析 {} 里的逻辑块
 * @return
 */
Block* Parser::parseBlock()
{
    Block* node{new Block};
    currentToken = scan();
    node->stmts = parseStatementList();
    //判断是否 {} 闭合
    assert(getCurrentToken() == TK_RBRACE);
    currentToken = scan();
    return node;
}
/**
 * 解析函数调用的参数列表 func(arg1,arg2,arg3) => [arg1,arg2,arg3]
 * @return
 */
std::vector<std::string> Parser::parseParameterList()
{
    std::vector<std::string> node;
    currentToken = scan();
    //是否解析到 ')'
    if(getCurrentToken() == TK_RPAREN){
        currentToken = scan();
        return std::move(node);
    }

    //解析所有括号内的参数 (..,..,..)
    while(getCurrentToken() != TK_RPAREN){
        //所有的参数都必须是 ident 或者 逗号,
        if(getCurrentToken() == TK_IDENT)
        {
            //将参数单独保存一份 需要计算 栈偏移量
            if(currentFunc){
                IdentExpr* var = new IdentExpr(getCurrentLexeme(),line,column);
                currentFunc->params_var[getCurrentLexeme()] = var;
                currentFunc->params_order_var.push_back(var);

                currentToken = scan();
                //不是动态参数
                if(getCurrentToken() == TK_COMMA) continue;
                if(getCurrentToken() == TK_RPAREN) continue;

                //既不是, 又不是 . （arg...）| (arg,arg2) 那就是有问题
                if(getCurrentToken() != TK_DOT){
                    parse_err("SynatxError: should be , or . but got :%s  line:%d column:%d\n",
                              getCurrentLexeme().c_str(),
                              line,column);
                }
                //去掉第二个点
                currentToken = scan();
                if(getCurrentToken() != TK_DOT){
                    parse_err("SynatxError: must be . but got :%s  line:%d column:%d\n",
                              getCurrentLexeme().c_str(),
                              line,column);
                }
                //去掉第三个点
                currentToken = scan();
                if(getCurrentToken() != TK_DOT){
                    parse_err("SynatxError: should be , or . but got :%s  line:%d column:%d\n",
                              getCurrentLexeme().c_str(),
                              line,column);
                }
                //走到这里说明一定是 tri-dot
                currentFunc->is_variadic = true;
                var->is_variadic = true;
            }
            node.push_back(getCurrentLexeme());
        }
        else{
            assert(getCurrentToken() == TK_COMMA);
        }
        //继续下一个token读取
        currentToken = scan();
    }
    //是否闭合
    assert(getCurrentToken() == TK_RPAREN);
    currentToken = scan();
    return move(node);
}