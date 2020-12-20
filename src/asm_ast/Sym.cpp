/**
 *@ClassName Sym
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:26
 *@Version 1.0
 **/
#include "Sym.h"
#include "Asmer.h"
#include "src/asm_parser/Parser.h"
#include "ElfFile.h"

//对于重定位文件是0，链接后开始于0x08048100
namespace asmer
{
    int curAddr = 0;
    int dataLen = 0;
    /**
     * 创建一个符号
     * @param name
     * @param externed
     */
    Sym::Sym(std::string name, bool externed):
    name(name),
    global(false),
    externed(externed)
    {
        //初始化当前符号偏移量
        addr = curAddr;
        //TODO: 初始化当前符号所在的段名
        segName = ".text";
        //当前符号默认长度为0
        len = 0;
        if(externed){
            //如果是外部链接 不存在当前符号偏移量,段名也是未知
            addr = 0;
            segName = "";
        }

    }
    /**
     * 静态字符串定义
     * @param name
     * @param str
     */
    Sym::Sym(std::string name, std::string str):
        name(name),
        global(false),
        str(str)
    {
        cout << name <<endl;
        cout << "cur:" << curAddr << " size:" << str.size() <<endl;
        addr     = curAddr;
        segName  = ".data";
        len      = str.size();
        externed = false;
        curAddr  += str.size();
    }
    Sym::Sym(std::string name, int len):
    name(name),
   global(false) {
        cout << name <<endl;
        cout << "cur:" << curAddr << " size:" << len <<endl;
        addr     = curAddr;
        segName  = ".data";
        this->len      = len;
        externed = false;
        global   = false;
        curAddr  += len;
    }
    Sym::~Sym() {}


};