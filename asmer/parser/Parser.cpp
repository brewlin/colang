#include "Parser.h"
#include "Utils.h"
#include "Log.h"

int scanLop = 1;
//有效数据长度
int dataLen = 0;

namespace asmer{

Parser::Parser(const std::string filepath,ElfFile* elf):elf(elf),data_size(0),text_size(0),ready(false)
{
    scanner = new Scanner(filepath);
    symtable = new SymTable();

    this->filepath = filepath;

    std::string fullname = filepath.substr(filepath.find_last_of('/')+1);
    filename = fullname.substr(0,fullname.size() - 2);
    outname  = filename + ".o";
}
Parser::~Parser()
{
    delete scanner;
}
void Parser::parse() {
    //扫描文件解析词法
    parseLex();

    //扫描两次，修正未计算的引用偏移地址
    genInst();
    //第二次开始修正所有的label偏移量
    ready      = true;
    text_size  = 0;
    genInst();
}
/**
 * 遍历所有的指令，计算偏移量
 */
void Parser::genInst() {
    /**
     * 1. 翻译机器指令写入elf文件
     * 2. 对外部符号进行重定位记录
     */
    //这里是计算指令段了，所以需要清空之前的计数
    Debug("instructs collection");
    for(auto func : funcs){
        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->labelname,false);
        sym->addr = text_size;
        //当前非外部符号
        //这里需要将函数名加入符号表
        symtable->addSym(sym);
        Debug("labelname:%s offset:%d",func->labelname,sym->addr);
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            //进行代码段指令翻译生成
            inst->gen();
        }
    }

}
/**
 * 解析
 * @param rt
 */
void Parser::parseLex()
{
    scanner->scan();
    if(scanner->token() == TK_EOF) {
        parse_err("[asmer] unrecognized file format :\'%s\'\n",filepath.c_str());
        return;
    }

    do{
        //能走到最外层 一般只有 .text .data  .global 已经标签声明
        switch(scanner->token()){
            //解析段声明
            case KW_DATA:
            case KW_TEXT:{
                //nothing todo
                //next
                scanner->scan();
                continue;
            }
            case KW_GLOBAL: parseGlobal(); continue;
            case KW_LABEL : parseLabel();  continue;
            case TK_EOF:                   break;
            default:
                parse_err("[Paser] unknow instruct:%s\n",scanner->value());
        }
    }while(scanner->token() != TK_EOF);
}

/**
 *
 * @return
 */
std::string Parser::printToken()
{
    auto  tk = scanner->scan();
    auto  str = scanner->value();
    while(tk != TK_EOF){
        std::cout << "" << tk << " => " << scanner->value() << "\n";
        tk = scanner->scan();
    }

}

};
