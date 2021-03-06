/**
 *@ClassName Sym
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:26
 *@Version 1.0
 **/
#include "Sym.h"
#include "Asmer.h"
#include "asmer/parser/Parser.h"
#include "ElfFile.h"

//对于重定位文件是0，链接后开始于0x08048100
namespace asmer
{
    /**
     * 创建一个符号
     * @param name
     * @param externed
     */
    Sym::Sym(std::string name, bool externed):name(name),global(false),externed(externed)
    {
        //初始化当前符号偏移量
        //TODO: 初始化当前符号所在的段名
        segName = ".text";
        //当前符号默认长度为0
        len = 0;
        //如果是外部链接 不存在当前符号偏移量,段名也是未知
        if(externed){
            addr = 0;
            segName = "";
        }

    }
    /**
     * 静态字符串定义
     * @param name
     * @param str
     */
    Sym::Sym(std::string name, std::string str,int pos):name(name),global(false),str(str),addr(pos)
    {
        segName  = ".data";
        len      = str.size() + 1;
        externed = false;
    }
    /**
     * 静态数据定义
     * @param name
     * @param len
     * @param pos
     */
    Sym::Sym(std::string name, int len,int pos):name(name),global(false),addr(pos)
    {
        segName   = ".data";
        this->len = len;
        externed  = false;
        global    = false;
    }
};