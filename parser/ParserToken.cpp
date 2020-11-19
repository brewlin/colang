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
    char cn = peekNextChar();
    char c  = first;
    //每一次遍历先判断下一个数是不是数字，如果不是则中断当前解析，不然会浪费下一个字符
    //peek 则不会出现这种问题
    while((cn >= '0' && cn <= '9') || (!isDouble && cn == '.')){
        if(c == '.')
            isDouble = true;
        c = getNextChar();
        cn = peekNextChar();
        lexeme += c;
    }
    return !isDouble ? make_tuple(LIT_INT,lexeme)
                     : make_tuple(LIT_DOUBLE,lexeme);
}
std::tuple<Token,std::string> Parser::parseKeyword(char c)
{
    std::string lexeme{c};
    char cn,cn1,cn2;

    cn = peekNextChar();
    while((cn >= 'a' && cn <= 'z') || (cn >= 'A' && cn <= 'Z') || cn == '_' || (cn >= '0' && cn <= '9')){
        c = getNextChar();
        lexeme += c;
        cn = peekNextChar();
    }
    cn1 = peekNextChar();
    cn2 = peekNextChar();
    //解析结构体的成员访问和赋值
    if(cn == '.' && cn1 != '.'){
        c = getNextChar();
        return std::make_tuple(TK_DOT,lexeme);
    }
    //... eat 2 dot
    if(cn == '.' && cn1 == '.'){
        if(cn2 != '.')
            parse_err("SynxaxError: tri-dot error\n");
        //eat 2 dot ,now left 1 dot
        c = getNextChar();
        c = getNextChar();
    }
    //返回标识符
    auto result = keywords.find(lexeme);
    return result != keywords.end()
           ? std::make_tuple(result->second,lexeme)
           : std::make_tuple(TK_IDENT,      lexeme);
}
//逐字解析 直到找到合法的token
std::tuple<Token,std::string> Parser::next() {
    char c = getNextChar();
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
            c = getNextChar();
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
            c = getNextChar();
        //如果代码有空行则跳过行
        while(c == '\n'){
            line++;
            column = 0;
            c = getNextChar();
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
    };

    //字符解析 只支持单个字符:'c'
    if (c == '\'') {
        std::string lexeme;
        lexeme += getNextChar();
        if (peekNextChar() != '\'') {
            parse_err("SynxaxError: a character literal should surround with single-quote\n");
        }
        c = getNextChar();
        return std::make_tuple(LIT_CHAR, lexeme);
    }
    //字符串解析 str = " .... "
    if(c == '\"'){
        std::string lexeme;
        char cn = peekNextChar();
        while(cn != '"'){
            c = getNextChar();
            lexeme += c;
            cn = peekNextChar();
        }
        c = getNextChar();
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
        char cn = peekNextChar();
        if(cn == '='){
            c = getNextChar();
            return std::make_tuple(TK_PLUS_AGN,"+=");
        }
        return std::make_tuple(TK_PLUS        ,"+");
    }
    if(c == '-'){
        char cn = peekNextChar();
        if(cn == '='){
            c = getNextChar();
            return std::make_tuple(TK_MINUS_AGN,"-=");
        }else if(cn >= '0' && cn <= '9'){
            //负数
            return parseNumber('-');
        }
        return std::make_tuple(TK_MINUS,"-");
    }
    if(c == '*') {
        char cn = peekNextChar();
        if (cn == '=') {
            c = getNextChar();
            return std::make_tuple(TK_MUL_AGN, "*=");
        }
        return std::make_tuple(TK_MUL, "*");
    }
    if(c == '/') {
        char cn = peekNextChar();
        if (cn == '=') {
            c = getNextChar();
            return std::make_tuple(TK_DIV_AGN, "/=");
        }
        return std::make_tuple(TK_DIV, "/");
    }
    if(c == '%') {
        char cn = peekNextChar();
        if (cn == '=') {
            c = getNextChar();
            return std::make_tuple(TK_MOD_AGN, "%=");
        }
        return std::make_tuple(TK_MOD, "%");
    }
    //parse ~ = == ! | &  > <
    if (c == '~') return std::make_tuple(TK_BITNOT,"~");
    if (c == '=') {
        if (peekNextChar() == '=') {
            c = getNextChar();
            return std::make_tuple(TK_EQ, "==");
        }
        return std::make_tuple(TK_ASSIGN, "=");
    }
    if (c == '!') {
        if (peekNextChar() == '=') {
            c = getNextChar();
            return std::make_tuple(TK_NE, "!=");
        }
        return std::make_tuple(TK_LOGNOT, "!");
    }
    if (c == '|') {
        if (peekNextChar() == '|') {
            c = getNextChar();
            return std::make_tuple(TK_LOGOR, "||");
        }
        return std::make_tuple(TK_BITOR, "|");
    }
    if (c == '&') {
        if (peekNextChar() == '&') {
            c = getNextChar();
            return std::make_tuple(TK_LOGAND, "&&");
        }
        return std::make_tuple(TK_BITAND, "&");
    }
    if (c == '>') {
        if (peekNextChar() == '=') {
            c = getNextChar();
            return std::make_tuple(TK_GE, ">=");
        }
        return std::make_tuple(TK_GT, ">");
    }
    if (c == '<') {
        if (peekNextChar() == '=') {
            c = getNextChar();
            return std::make_tuple(TK_LE, "<=");
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
    currentToken = next();
    node->stmts = parseStatementList();
    //判断是否 {} 闭合
    assert(getCurrentToken() == TK_RBRACE);
    currentToken = next();
    return node;
}
/**
 * 解析函数调用的参数列表 func(arg1,arg2,arg3) => [arg1,arg2,arg3]
 * @return
 */
std::vector<std::string> Parser::parseParameterList()
{
    std::vector<std::string> node;
    currentToken = next();
    //是否解析到 ')'
    if(getCurrentToken() == TK_RPAREN){
        currentToken = next();
        return std::move(node);
    }

    //解析所有括号内的参数 (..,..,..)
    while(getCurrentToken() != TK_RPAREN){
        //所有的参数都必须是 ident 或者 逗号,
        if(getCurrentToken() == TK_IDENT){
            char cn = peekNextChar();
            //将参数单独保存一份 需要计算 栈偏移量
            if(currentFunc){
                IdentExpr* var = new IdentExpr(getCurrentLexeme(),line,column);
                if(cn == '.'){
                    //当前函数有可变参数函数
                    currentFunc->is_multi = true;
                    var->is_multi         = true;
                    //eat . dot
                    getNextChar();
                }
                currentFunc->params_var[getCurrentLexeme()] = var;
                currentFunc->params_order_var.push_back(var);
            }
            node.push_back(getCurrentLexeme());
        }
        else{
            assert(getCurrentToken() == TK_COMMA);
        }
        //继续下一个token读取
        currentToken = next();
    }
    //是否闭合
    assert(getCurrentToken() == TK_RPAREN);
    currentToken = next();
    return move(node);
}