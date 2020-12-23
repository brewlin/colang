/**
 *@ClassName Instruct
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 4:35
 *@Version 1.0
 **/
#ifndef COLANG_ASMER_INSTRUCT_H
#define COLANG_ASMER_INSTRUCT_H

#include <string>
#include <iostream>
#include <vector>
#include "Token.h"
using  namespace std;

namespace asmer{

    //modrm字段
    struct ModRM
    {
        int mod;//0-1
        int reg;//2-4
        int rm;//5-7
        ModRM();
        void init();
    };
    //sib字段
    struct SIB
    {
        int scale;//0-1
        int index;//2-4
        int base;//5-7
        SIB();
        void init();
    };
    //指令的其他部分
    struct Inst
    {
        unsigned char opcode;
        int disp;
        //对于mov 支持64位立即数
        long int imm;
        int dispLen;//偏移的长度
        Inst();
        void init();
        //设置disp，自动检测disp长度（符号），即使是无符号地址值也无妨
        void setDisp(int d,int len);
    };

    class Instruct{
    public:
        Instruct(Token type);
        //表示有引用
        bool        is_rel;
        //表示当前组合中，有一个指令包含了引用符号，两个指令中 可能有一个是重定向符号
        std::string name;
        //表明当前的指令组合中有 对外的函数引用，那么上面的name就是那个函数的标签
        bool        is_func;
        Token       type;
        //寄存器个数
        int         regnum;
        InstType    left;
        InstType    right;
        vector<Token> tks;
        Inst*       inst;
        SIB*        sib;
        ModRM*      modrm;

        std::string str;
        char        bytes[20];
        int         size;

    public:
        void append(unsigned char b);
        void append(unsigned short int b);
        void append(long int b,int len);
        bool updateRel();//处理可能的重定位信息
        void gen();
        void gen2Op();
        void gen1Op();
        void gen0Op();
        void writeModRM();
        void writeSIB();
    };

};

#endif //COLANG_INSTRUCT_H
