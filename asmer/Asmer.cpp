/**
 *@ClassName Asmer
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:34
 *@Version 1.0
 **/
#include "Asmer.h"
#include "Sym.h"
#include "ElfFile.h"
#include "Log.h"


ElfFile* Asmer::elf   = nullptr;
Asmer*   Asmer::obj   = nullptr;
int      Asmer::bytes = 0;
int      Asmer::data  = 0;
int      Asmer::text  = 0;

Asmer::Asmer(std::string filename) {
    parser = new Parser(filename);
    //初始化 file.o文件
    out  = fopen(parser->outname.c_str(),"w");
    //初始化elf文件相关
    elf   = new ElfFile;
    Asmer::obj   = this;
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
    parser->parse();
    //构建elf结构
    buildElf();
    //写入elf文件
    writeElf();

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
    elf->buildSymtab();
    //构建字符串表，包括了上面所有的符号
    elf->buildStrtab();
    //构建重定位代码段和数据段
    elf->buildRelTab();
}
void Asmer::writeElf() {
    int offset = 0;
    //写入elf header
    writeBytes(&elf->ehdr,elf->ehdr.e_ehsize);
//    std::cout << "[writeElf] header size:" << elf->ehdr.e_ehsize << std::endl;
    offset += elf->ehdr.e_ehsize;
    assert(Asmer::bytes == offset);

    //写入段表
    for (auto name : elf->shdrNames) {
        //遍历每一个段名
        Elf64_Shdr *sh = elf->shdrTab[name];
        writeBytes(sh,elf->ehdr.e_shentsize);
    }
    offset += elf->ehdr.e_shentsize * 8;
    assert(Asmer::bytes == offset);

    int data_size  = parser->symtable->data_symbol.size() ;
    //写入数据区 每个全局数据类型当前语言实现默认为指针
    int ds = 0;
    for (auto *sym : parser->symtable->data_symbol) {
        //现在假定所有的 数据区变量都占8字节，用于存储指针类型
        //当前全局区域都是存储的8字节指针
        int b[20] = {0};
        if(sym->str != ""){
            writeBytes(sym->str.c_str(),sym->len);
        }else{
            writeBytes(b,sym->len);
        }
    }
    offset += Asmer::data;
    // std::cout << ":bytes:" << Asmer::bytes << " offset:" << offset <<std::endl;
    assert(Asmer::bytes == offset);

    //写入代码区
    Asmer::obj->InstWrite();
    offset += Asmer::text;
    assert(Asmer::bytes == offset);

//    std::cout << "[writeElf] .shstrtab: size:" << elf->shstrtab_size << std::endl;
    //.shstrtab 将所有的段名字符串写入到文件里
    writeBytes(elf->shstrtab,elf->shstrtab_size);
    offset += elf->shstrtab_size;
    assert(Asmer::bytes == offset);

    //.symtab   写入所有的字符串表
    // cout << "writeelf:" <<  offset << endl;
    for(auto symname : elf->symNames){
//        std::cout << "[writeElf] .strtab:" << symname << std::endl;
        Elf64_Sym* sym = elf->symTab[symname];
        writeBytes(sym,sizeof(Elf64_Sym));
    }
    offset += elf->symNames.size() * sizeof(Elf64_Sym);
    assert(Asmer::bytes == offset);
//    std::cout << "[writeElf] str: size" << elf->strtab_size << std::endl;
    //.strtab 写入所有的字符串
    writeBytes(elf->strtab,elf->strtab_size);
    offset += elf->strtab_size;
    assert(Asmer::bytes == offset);

    //.rel_text 写入重定向代码表
    for(auto* rel : elf->relTextTab){
//        std::cout << "[writeElf] .rela.text: "  <<  std::endl;
        writeBytes(rel,sizeof(Elf64_Rela));
        delete rel;
    }
    offset += elf->relTextTab.size() * sizeof(Elf64_Rela);
    assert(Asmer::bytes == offset);
    //.rel_data 写入重定向数据表
    for(auto* rel : elf->relDataTab){
        writeBytes(rel,sizeof(Elf64_Rela));
        delete rel;
    }
    offset += elf->relDataTab.size() * sizeof(Elf64_Rela);
    assert(Asmer::bytes == offset);

}
// void b, int len
void Asmer::writeBytes(const void* b, int len)
{
    bytes += len;
    fwrite(b,len,1,obj->out);
}

