/**
 *@ClassName Asmer
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:34
 *@Version 1.0
 **/
#include "Asmer.h"
#include "src/asm_ast/Sym.h"
#include "ElfFile.h"
ElfFile* Asmer::elf = nullptr;
Asmer*   Asmer::obj = nullptr;

void Asmer::Asmer(std::string filename) {
    paser = new Parser(filename);
    //初始化 file.o文件
    out  = fopen(parser->outname.c_str(),"w");
    //初始化elf文件相关
    elf   = new ElfFile;
    obj   = this;
}
/**
 * start
 */
void Asmer::execute() {
    /**
     * 进行汇编代码翻译
     * 1. 解析数据段 加入符号表
     * 2. 解析代码段 备用
     */
    paser->parse();

    //更新代码段中的引用
    updateText();
    //处理所有的指令集 并更新重定位
    updateInstructs();

    //构建elf文件
    build();

}
void Asmer::buildElf() {
    //构建elf头
    elf->buildEhdr();
    //构建9个段的数组
    elf->buildSectab();
    //构建数据段
    elf->buildData();
    //构建代码段
    elf->buildText();
    //构建段名字符串表，并拷贝所有字符串
    elf->buildShstrtab();
    //构建段符号表
    elf->buildSymtab()
    //构建字符串表，包括了上面所有的符号
    elf->buildStrtab()
    //构建重定位代码段和数据段
    elf->buildRelTab();
}
void Asmer::writeElf() {
    //写入elf header
    fwrite(&elf->ehdr, ehdr.e_ehsize, 1, out);

    //写入段表
    for (auto name : elf->shdrNames) {
        //遍历每一个段名
        Elf32_Shdr *sh = elf->shdrTab[name];
        fwrite(sh, elf->ehdr.e_shentsize, 1, out);
    }
    //写入数据区 每个全局数据类型当前语言实现默认为指针
    for (auto *sym : paser->symtable->data_symbol) {
        //现在假定所有的 数据区变量都占8字节，用于存储指针类型
        for(int i = 0 ; i < 8 ; i ++)
            fwrite(0,len,1,fout)
    }
    //TODO: 写入代码区
    Asmer::obj.InstGen();

    //.shstrtab 将所有的段名字符串写入到文件里
    fwrite(elf->shstrtab,elf->shstrtab_size,1,out);
    //.symtab   写入所有的字符串表
    for(auto symname : elf->symNames){
        Elf64_Sym* sym = elf->symTab[symname];
        fwrite(sym,sizeof(Elf64_Sym),1,out);
    }
    //.strtab 写入所有的字符串
    fwrite(elf->strtab,elf->strtab_size,1,out);

    //.rel_text 写入重定向代码表
    for(auto* rel : elf->relTextTab){
        fwrite(rel,sizeof(Elf64_Rel),1,out);
        delete rel;
    }
    //.rel_data 写入重定向数据表
    for(auto* rel : elf->relDataTab){
        fwrite(rel,sizeof(Elf64_Rel),1,out);
        delete rel;
    }
}

/**
 * 	按照小端顺序（little endian）输出指定长度数据
	len=1：输出第4字节
	len=2:输出第3,4字节
	len=4:输出第1,2,3,4字节
 * @param value
 * @param len
 */
void Asmer::write(int value, int len)
{
    //计算地址
    asmer::Sym::curAddr += len;
    if(scanLop==2)
    {
        fwrite(&value,len,1,out);
        inLen+=len;
    }
    //cout<<lb_record::curAddr<<"\t"<<inLen<<endl;
}