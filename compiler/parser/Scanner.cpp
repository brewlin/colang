#include "Scanner.h"
using namespace std;

unordered_map<std::string,Token > keywords = 
{
    {"if",KW_IF},         {"else",KW_ELSE},     {"else",KW_ELSE},
    {"while", KW_WHILE},  {"for", KW_FOR},      {"false", KW_FALSE},
    {"true", KW_TRUE},    {"null", KW_NULL},    {"func", KW_FUNC},
    {"return", KW_RETURN},{"break", KW_BREAK},  {"continue", KW_CONTINUE},
    {"import", KW_IMPORT},{"extern", KW_EXTERN},{"class", KW_CLASS},
    {"new", KW_NEW},      {"go", KW_GO},        {"package", KW_PACKAGE},
    {"struct",KW_STRUCT}, 
    {"i8",KW_I8},         {"i16",KW_I16},       {"i32",KW_I32},       {"i64",KW_I64},
    {"u8",KW_U8},         {"u16",KW_U16},       {"u32",KW_U32},       {"u64",KW_U64},
};

Scanner::Scanner(const string filepath):
fs(filepath),pos(0)
{
	buffer << fs.rdbuf();
}
Scanner::~Scanner(){
    fs.close();
}
char Scanner::next() {
    column++;
	return  buffer.str()[pos++];
}
char Scanner::peek() {
	int p = pos;
	return buffer.str()[p];
}
/**
 * consumeline 
 */
string Scanner::consumeLine()
{
    int c;
    string ret;
    while( (c = next()) != EOF && c != '\n' ){
        ret += c;
    }
    return ret;
}
// parseNumber
tuple<Token,string> Scanner::parseNumber(char first)
{
    string lexeme{first};
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
tuple<Token,string> Scanner::parseKeyword(char c)
{
    string lexeme{c};
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
           ? make_tuple(result->second,lexeme)
           : make_tuple(TK_VAR,      lexeme);
}
//解析 * 运算符号 或者是解引用
//解引用非常危险 需要注意只能在和c函数调用中而存在
tuple<Token,string> Scanner::parseMulOrDelref(char c)
{
    char cn = peek();
    // a *= b
    if (cn == '=') {
        c = next();
        return make_tuple(TK_MUL_AGN, "*=");
    }
    //说明是个解引用操作
    // call(*a,*b)
    if((cn >= 'a' && cn <= 'z') || (cn >= 'A' && cn <= 'Z')){
        return make_tuple(TK_DELREF, "*");
    }
    return make_tuple(TK_MUL, "*");
}
//扫描下一个
Token Scanner::scan(){
    prevLex   = curLex;
    prevToken = curToken;

    auto tk   = get_next();
    curLex    = get<string>(tk);
    curToken  = get<Token>(tk);
}
//逐字解析 直到找到合法的token
tuple<Token,string> Scanner::get_next() {
    char c = next();
    //make_*开头一般是创建一个 智能指针
    if(c == EOF)
        return make_tuple(TK_EOF,"");

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
            return make_tuple(TK_EOF,"");
    }
    //    去掉注释
    //TODO: support // or /* */
    if(c == '#'){
        //看看是否是有链接信息
        char cn = peek();
        if(cn == ':') {
            //eat :
            c = next();
            return make_tuple(KW_EXTRA,"");
        }
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
            return make_tuple(TK_EOF,"");
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
        string lexeme;
        lexeme += c;
        return make_tuple(TK_DOT,lexeme);
    }
    if(c == ':'){
        string lexeme;
        lexeme += c;
        return make_tuple(TK_COLON,lexeme);
    }
    if(c == ';'){
        string lexeme;
        lexeme += c;
        return make_tuple(TK_SEMICOLON,lexeme);
    }
    //字符解析 只支持单个字符:'c'
    if (c == '\'') {
        string lexeme;
        lexeme += next();
        if (peek() != '\'') {
            parse_err("SynxaxError: a character literal should surround with single-quote\n");
        }
        c = next();
        return make_tuple(LIT_CHAR, lexeme);
    }
    //字符串解析 str = " .... "
    if(c == '\"'){
        string lexeme;
        char cn = peek();
        while(cn != '"'){
            c = next();
            lexeme += c;
            cn = peek();
        }
        c = next();
        return make_tuple(LIT_STR,lexeme);
    }
    //parser [] {} () ,
    if(c == '[') return make_tuple(TK_LBRACKET,"[");
    if(c == ']') return make_tuple(TK_RBRACKET,"]");
    if(c == '{') return make_tuple(TK_LBRACE  ,"{");
    if(c == '}') return make_tuple(TK_RBRACE  ,"}");
    if(c == '(') return make_tuple(TK_LPAREN  ,"(");
    if(c == ')') return make_tuple(TK_RPAREN  ,")");
    if(c == ',') return make_tuple(TK_COMMA   ,",");

    //parser + += - -= * *= / /+
    if(c == '+'){
        char cn = peek();
        if(cn == '='){
            c = next();
            return make_tuple(TK_PLUS_AGN,"+=");
        }
        return make_tuple(TK_PLUS        ,"+");
    }
    if(c == '-'){
        char cn = peek();
        if(cn == '='){
            c = next();
            return make_tuple(TK_MINUS_AGN,"-=");
        }else if(cn >= '0' && cn <= '9'){
            //负数
            return parseNumber('-');
        }
        return make_tuple(TK_MINUS,"-");
    }
    if(c == '*')
        return parseMulOrDelref(c);

    if(c == '/') {
        char cn = peek();
        if (cn == '=') {
            c = next();
            return make_tuple(TK_DIV_AGN, "/=");
        }
        return make_tuple(TK_DIV, "/");
    }
    if(c == '%') {
        char cn = peek();
        if (cn == '=') {
            c = next();
            return make_tuple(TK_MOD_AGN, "%=");
        }
        return make_tuple(TK_MOD, "%");
    }
    //parse ~ = == ! | &  > <
    if (c == '~') return make_tuple(TK_BITNOT,"~");
    if (c == '=') {
        if (peek() == '=') {
            c = next();
            return make_tuple(TK_EQ, "==");
        }
        return make_tuple(TK_ASSIGN, "=");
    }
    if (c == '!') {
        if (peek() == '=') {
            c = next();
            return make_tuple(TK_NE, "!=");
        }
        return make_tuple(TK_LOGNOT, "!");
    }
    if (c == '|') {
        if (peek() == '|') {
            c = next();
            return make_tuple(TK_LOGOR, "||");
        }
        if (peek() == '=') {
            c = next();
            return make_tuple(TK_BITOR_AGN, "|=");
        }
        return make_tuple(TK_BITOR, "|");
    }
    if (c == '&') {
        if (peek() == '&') {
            c = next();
            return make_tuple(TK_LOGAND, "&&");
        }
        if (peek() == '=') {
            c = next();
            return make_tuple(TK_BITAND_AGN, "&=");
        }
        return make_tuple(TK_BITAND, "&");
    }
    if (c == '>') {
        //>=
        if (peek() == '=') {
            c = next();
            return make_tuple(TK_GE, ">=");
        }
        //>>
        if (peek() == '>') {
            c = next();
            //>>=
            if (peek() == '=') {
                c = next();
                return make_tuple(TK_SHIFTR_AGN, ">>=");
            }
            return make_tuple(TK_SHIFTR, ">>");
        }

        return make_tuple(TK_GT, ">");
    }
    if (c == '<') {
        if (peek() == '=') {
            c = next();
            return make_tuple(TK_LE, "<=");
        }
        if (peek() == '<') {
            c = next();
            //<<=
            if (peek() == '=') {
                c = next();
                return make_tuple(TK_SHIFTL_AGN, "<<=");
            }
            return make_tuple(TK_SHIFTL, "<<");
        }
        return make_tuple(TK_LT, "<");
    }
    //匹配失败 直接print后 exit
    parse_err("SynxaxError: unknown token '%c' line:%d column:%d\n",c,line,column);
    return make_tuple(INVALID,"invalid");
}
/**
 * 解析优先级
 * @param op
 * @return
 */
short Scanner::precedence(Token op)
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
 * 测试token解析
 * @param filename
 */
void Scanner::print()
{
    auto  tk = get_next();
    while(std::get<0>(tk) != TK_EOF){
        std::cout << "" << getTokenString(std::get<0>(tk)) << " => " << std::get<1>(tk) << "\n";
        tk = get_next();
    }

}