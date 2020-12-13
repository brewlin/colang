#include "Scanner.h"
#include "Util.h"
using namespace asm::Token;

asm::Scanner::Scanner(const std::string filepath)
{
    keywords[".comm"]       = KW_COMM;
    keywords[".global"]     = KW_GLOBAL;
    keywords[".text"]       = KW_TEXT;
    keywords[".type"]       = KW_TYPE;
    keywords[".string"]    = KW_STRING;
    keywords["push"]     = KW_PUSH;
    keywords["pop"]     = KW_POP;
    keywords["mov"]     = KW_MOV;
    keywords["sub"]   = KW_SUB;
    keywords["call"]    = KW_call;
    keywords["ret"] = KW_RET;
    keywords["lea"]   = KW_LEA;
    keywords["cmp"]   = KW_CMP;
    keywords["je"]   = KW_JE;

    keywords["%rax"]      = KW_RAX;
    keywords["%rbx"]       = KW_RBX;
    keywords["%rcx"]  = KW_RCX;
    keywords["%rdx"]  = KW_RDX;
    keywords["%rdi"]  = KW_RDI;
    keywords["%rsi"]  = KW_RSI;
    keywords["%r8"]  = KW_R8;
    keywords["%r9"]  = KW_R9;
    keywords["%r10"]  = KW_R10;
    keywords["%rsp"]  = KW_RSP;
    keywords["%rbp"]  = KW_RBP;
    fs.open(filepath);
    if(!fs.is_open()){
        parse_err("ParserError: can not open script file :%s\n",filepath.c_str());
    }
}
asm::Scanner::~Scanner(){
    fs.close();
}
char asm::Scanner::next() {
    column++;
    return static_cast<char>(fs.get());
}
char asm::Scanner::peek() {
    return static_cast<char>(fs.peek());
}
Token asm::Scanner::token()const {
    return std::get<Token >(currentToken);
}
std::string asm::Scanner::value()const {
    return std::get<std::string>(currentToken);
}
std::tuple<Token,std::string> asm::Scanner::scan(){
    auto tk = next();
    currentToken = tk;
    return tk;
}
// parseNumber
std::tuple<Token,std::string> asm::Scanner::parseNumber(char first)
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
std::tuple<Token,std::string> asm::Scanner::parseKeyword(char c)
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
           : std::make_tuple(TK_VAR,      lexeme);
}
//解析 * 运算符号 或者是解引用
//解引用非常危险 需要注意只能在和c函数调用中而存在
std::tuple<Token,std::string> asm::Scanner::parseMulOrDelref(char c)
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
std::tuple<Token,std::string> asm::Scanner::scan() {
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
