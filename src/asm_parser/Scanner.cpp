#include "Scanner.h"
#include "Utils.h"
#include <string>

namespace asmer {

Scanner::Scanner(const std::string filepath)
{
    keywords[".global"]     = KW_GLOBAL;
    keywords[".text"]       = KW_TEXT;
    keywords[".data"]       = KW_DATA;
    keywords[".string"]    = KW_STRING;
    keywords[".quad"]    = KW_QUAD;

    keywords["push"]     = KW_PUSH;
    keywords["pop"]     = KW_POP;
    keywords["int"]     = KW_INT;
    keywords["mov"]     = KW_MOV;
    keywords["sub"]   = KW_SUB;
    keywords["call"]    = KW_CALL;
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
    keywords["%rip"]  = KW_RIP;
    fs.open(filepath);
    if(!fs.is_open()){
        parse_err("ParserError: can not open script file :%s\n",filepath.c_str());
    }
}
Scanner::~Scanner(){
    fs.close();
}
char Scanner::next() {
    column++;
    return static_cast<char>(fs.get());
}
char Scanner::peek() {
    return static_cast<char>(fs.peek());
}
Token Scanner::token()const {
    return std::get<Token >(currentToken);
}
std::string Scanner::value()const {
    return std::get<std::string>(currentToken);
}
Token Scanner::scan(){
    auto tk = _scan();
    currentToken = tk;
    return token();
}
// parseNumber
std::tuple<Token,std::string> Scanner::parseNumber(char first)
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
    return !isDouble ? make_tuple(TK_NUMBER,lexeme)
                     : make_tuple(TK_DOUBLE,lexeme);
}
std::tuple<Token,std::string> Scanner::parseString(char c)
{
    std::string lexeme = "";
    char cn = peek();
    while(cn != '"'){
        c = next();
        lexeme += c;
        cn = peek();
    }
    c = next();
    return std::make_tuple(TK_STRING,lexeme);
}
std::tuple<Token,std::string> Scanner::parseKeyword(char c)
{
    std::string lexeme{c};
    char cn;

    cn = peek();
    while((cn >= 'a' && cn <= 'z') || (cn >= 'A' && cn <= 'Z') || cn == '.' || cn == '_' || (cn >= '0' && cn <= '9')){
        c = next();
        lexeme += c;
        cn = peek();
    }
    //返回标识符
    auto result = keywords.find(lexeme);
    return result != keywords.end()
           ? std::make_tuple(result->second,lexeme)
           : std::make_tuple(KW_LABEL,      lexeme);
}
//逐字解析 直到找到合法的token
std::tuple<Token,std::string> Scanner::_scan() {
    char c = next();
    if(c == EOF) return std::make_tuple(TK_EOF,"");
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
    if(c >= '0' && c <= '9') return parseNumber(c);
    if( c == '.' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') return parseKeyword(c);

    if(c == '\"') return parseString(c);
    if(c == ':')  return std::make_tuple(TK_COLON   ,":");
    if(c == '(')  return std::make_tuple(TK_LPAREN  ,"(");
    if(c == ')')  return std::make_tuple(TK_RPAREN  ,")");
    if(c == ',')  return std::make_tuple(TK_COMMA   ,",");
    if(c == '%')  return parseKeyword('%');//std::make_tuple(TK_REM     ,"%");
    if(c == '-')  return std::make_tuple(TK_SUB     ,"-");
    if(c == '*')  return std::make_tuple(TK_MUL     ,"*");
    if(c == '@')  return std::make_tuple(TK_AT      ,"@");
    if(c == '$')  return std::make_tuple(TK_IMME    ,"$");

    //匹配失败 直接print后 exit
    parse_err("SynxaxError: unknown token '%c' line:%d column:%d\n",c,line,column);
    return std::make_tuple(INVALID,"invalid");
}

};
