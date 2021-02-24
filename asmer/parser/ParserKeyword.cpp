/**
 *@ClassName ParserKeyword
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 5:11
 *@Version 1.0
 **/

#include "Parser.h"
#include "asmer/ast/Sym.h"

namespace asmer{
    /**
     * 解析 global定义
     */
    void Parser::parseGlobal() {
        assert(scanner->token() == KW_GLOBAL);

        //next
        assert(scanner->scan() == KW_LABEL);

        std::string labelname = scanner->value();
        Sym* sym = new Sym(labelname, false);
        //全局符号
        sym->global = true;
        symtable->addSym(sym);

        scanner->scan();
        return;
    }
    //解析label
    void Parser::parseLabel() {
        std::string labelname = scanner->value();
        //next;
        scanner->scan();
        // :
        assert(scanner->token() == TK_COLON);

        //label下有两种情况，
        //1 数据定义
        //2 函数指令
        //next
        Sym* sym;
        switch(scanner->scan()){
            case KW_QUAD:
                parseQuad(labelname);
                return;
            case KW_STRING:
                parseString(labelname);
                return;
                /**
                 * 这里处理一下,会有下面同样也是标签的情况
                 *  L.else.11:
                 *  L.end.11:
                 */
            case KW_LABEL:{
                //记下这个标签的位置
                //记下这个标签的位置
                sym = new Sym(labelname, false);
                symtable->addSym(sym);

                Function* func = new Function(labelname);
                funcs.push_back(func);
                return;
            }
            default:{

            }
        }

        sym = new Sym(labelname, false);
        symtable->addSym(sym);
        //其他情况就是函数定义了
        Function* func = parseFunction(labelname);
        funcs.push_back(func);
        return;

    }
    /**
     * 解析 全局变量
     * @param labelname
     */
    void Parser::parseQuad(std::string labelname) {
        assert(scanner->token() == KW_QUAD);

        //下一个是变量的大小
        assert(scanner->scan() == TK_NUMBER);
        int len = std::stoi(scanner->value());

        Sym* sym = new Sym(labelname,len);
        symtable->addSym(sym);

        //next
        scanner->scan();
        return;
    }
    void Parser::parseString(std::string labelname) {
         assert(scanner->token() == KW_STRING);

        //下一个是变量的大小
        assert(scanner->scan() == TK_STRING);

        Sym* sym = new Sym(labelname,scanner->value());
        symtable->addSym(sym);

        //next
        scanner->scan();
        return;
    }
};
