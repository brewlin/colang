/**
 *@Author brewlin
 *@Date 2021/03/04 0016 下午 8:32
 *@Version 1.0
 **/

#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Log.h"
#include "Asmer.h"

/**
 * 计算头部
 */
void ElfFile::buildEhdr() {
    //魔数计算
    int *p_id = (int *) ehdr.e_ident;
    //固定 四字节 DEL E L F 的ascii码值
    *p_id = 0x464c457f;
    p_id++;
    //02（64位） 01(小端) 01(版本号)
    *p_id = 0x010102;
    p_id++;
    //其他平台相关的都是0
    *p_id = 0;
    p_id++;
    *p_id = 0;
    //重定位目标文件类型，机器类型，版本号,平台相关属性
    ehdr.e_type      = ET_REL;
    ehdr.e_machine   = EM_X86_64;
    ehdr.e_version   = EV_CURRENT;
    ehdr.e_flags     = 0;

    //程序头表相关都是0
    ehdr.e_entry     = 0;
    ehdr.e_phoff     = 0;
    ehdr.e_phentsize = 0;
    ehdr.e_phnum     = 0;
    //当前结构体大小 支持的是64位大小
    ehdr.e_ehsize    = sizeof(Elf64_Ehdr);
    //段表项大小,段表个数
    ehdr.e_shentsize = sizeof(Elf64_Shdr);
    ehdr.e_shnum     = 8;
    //段字符串表在 段表中的索引默认写死为4
    ehdr.e_shstrndx  = 3;

    //我们规定段表就在头部后面
    ehdr.e_shoff = sizeof(Elf64_Ehdr);

    offset = sizeof(Elf64_Ehdr);
    Debug("header:[0,%d]",offset);
}
/**
 * 构建段表
 */
void ElfFile::buildSectab(){
    //默认八个段 + 1个空段
    Debug("section tab:[%d,%d]",offset,offset + sizeof(Elf64_Shdr) * 8);
    offset     += sizeof(Elf64_Shdr) * 8;
};
/**
 * 数据段
 */
void ElfFile::buildData(){
    //表示当前的数据段的大小
    addShdr(".data",asmer->data);
    Debug("data section:[%d,%d]",offset,offset + asmer->data);
    //数据段紧跟其后
    offset     += asmer->data;
}
/**
 * 代码段
 * 需要计算两次，因为第一次可能对应的符号引用偏移量未设置
 */
void ElfFile::buildText(){
    addShdr(".text",asmer->parser->text_size);
    Debug("text section:[%d,%d]",offset,offset + asmer->parser->text_size);
    offset += asmer->parser->text_size;
    asmer->text = asmer->parser->text_size;
    //添加默认的段
    addSectionSym();
    //到这里就源代码解析完了，需要导出所有符号表
    for(auto it : asmer->parser->symtable->symbolTable)
    {
        Sym* sym = it.second;
        addSym(sym);
    }
}
/**
 * 构建段字符串表
 */
void ElfFile::buildShstrtab() {

    /**
     * 当前所处位置
     * ehdr
     * section table * 8
     * text
     * data
     * now: 段字符串段表
     */
    std::string reltext  = ".rela.text";
    std::string reldata  = ".rela.data";
    std::string shstrtab = ".shstrtab";
    std::string symtab   = ".symtab";
    std::string strtab   = ".strtab";
    std::string pading   = "      ";

    //算出存储全部的段字符串需要多少空间
    //每个字符串末尾都要留一个空格
    shstrtab_size = reltext.length()     + 1 +
                    reldata.length() + 1 +
                    shstrtab.length()+ 1 +
                    symtab.length()  + 1 +
                    strtab.length()  + 1 +
                    pading.length();

    //开始构建存储所有的段字符串
    char *str = new char[shstrtab_size];
    this->shstrtab  = str;

    int index       = 0;
    strIndex[".rela.text"] = index;
    strcpy(str + index, ".rela.text");
    //text段名 和 .rela.text 有相同部分，可以共用
    strIndex[".text"] = index + 5;
    index += reltext.length() + 1;
    strIndex[""] = index - 1;
    strIndex[".rela.data"] = index;
    strcpy(str + index, ".rela.data");
    //data段同样可以共用
    strIndex[".data"] = index + 5;
    index += reldata.length() + 1;
    strIndex[".shstrtab"] = index;
    strcpy(str + index, ".shstrtab");
    index += shstrtab.length() + 1;
    strIndex[".symtab"] = index;
    strcpy(str + index, ".symtab");
    index += symtab.length() + 1;
    strIndex[".strtab"] = index;
    strcpy(str + index, ".strtab");
    index += strtab.length() + 1;
    //添加.shstrtab 段字符串表
    addShdr(".shstrtab", SHT_STRTAB, 0, 0, offset, shstrtab_size, SHN_UNDEF, 0, 1, 0);//.shstrtab
    Debug("shstrtable:[%d,%d]",offset,offset + shstrtab_size);
    //下一个表
    offset += shstrtab_size;
}
/**
 * 构建字符串表
 * @return
 */
void ElfFile::buildSymtab() {
    //进行global 和local 分类
    sortGlobal();
    //.symtab,sh_link 代表.strtab索引，默认在.symtab之后,sh_info不能确定
    //计算总共字符串表的大小
    strtab_size = symNames.size() * sizeof(Elf64_Sym);
    Debug("symtab: offset[%d,%d] size:%d", offset, offset + strtab_size, strtab_size);
    //偏移跟上
    //计算字符串表的大小
    addShdr(".symtab", SHT_SYMTAB, 0, 0, offset,strtab_size, 0, 0, 8, sizeof(Elf64_Sym));
    offset += strtab_size;
    //找到字符串段在段表中的索引，这里应该是4
    shdrTab[".symtab"]->sh_link = getSegIndex(".symtab") + 1;//.strtab默认在.symtab之后
    shdrTab[".symtab"]->sh_info = sh_info;
}
//构建字符串表
void ElfFile::buildStrtab() {
    //上面是串表数组的大小，下面这个是字符串存储区的大小
    strtab_size = 0;
    //遍历所有函数名，全局变量名,标签名
    for (int i = 0; i < symNames.size(); ++i) {
        strtab_size += symNames[i].length() + 1;
    }
    //添加字符串表
    addShdr(".strtab", SHT_STRTAB, 0, 0, offset, strtab_size, SHN_UNDEF, 0, 1, 0);//.strtab

    //填充strtab数据
    char *str = new char[strtab_size];
    this->strtab = str;
    int index = 0;
    //串表与符号表名字更新
    for(auto strs : symNames){
        //更新符号表中对应于字符串的索引
        symTab[strs]->st_name = index;
        strcpy(str + index, strs.c_str());
        index += strs.length() + 1;
    }
    //这里存储的是字符串区需要加上这个
    Debug("strtab:[%d,%d]",offset,offset + strtab_size);
    offset += strtab_size;
}
/**
 * 处理重定位表
 */
void ElfFile::buildRelTab(){
    //处理重定位表
    for(int i = 0 ;i < relTab.size() ; i++){
        Elf64_Rela *rela = new Elf64_Rela();
        rela->r_offset  = relTab[i]->offset;
        rela->r_info    = ELF64_R_INFO((Elf64_Word)getSymIndex(relTab[i]->name),relTab[i]->type);
        //修正数据偏移
        rela->r_addend  = -4;
        //数据是需要添加偏移的
        if(relTab[i]->type == R_X86_64_PC32){
            Sym* sym = asmer->parser->symtable->getSym(relTab[i]->name);
            //本地全局变量
            if(!sym->externed){
                rela->r_info    = ELF64_R_INFO((Elf64_Word)getSymIndex(".data"),relTab[i]->type);

                rela->r_addend  = -4 + sym->addr;
            }

        }
        //将重定项中的类型进行区分，代码区和数据区
        if(relTab[i]->tarSeg == ".text")
            relTextTab.push_back(rela);
        else if(relTab[i]->tarSeg == ".data")
            relDataTab.push_back(rela);
    }
    //如果存在函数的外部引用，以及全局变量的外部引用,需要进行重定位
    //加上代码区
    int text_size = relTextTab.size() * sizeof(Elf64_Rela);
    addShdr(".rela.text",SHT_RELA,SHF_INFO_LINK,0,offset,text_size,getSegIndex(".symtab"),getSegIndex(".text"),8, sizeof(Elf64_Rela));//.rela.text
    Debug("text realation table:[%d,%d]",offset,offset + text_size);
    offset += text_size;

    //加上代码区
    int data_size = relDataTab.size() * sizeof(Elf64_Rela);
    addShdr(".rela.data",SHT_RELA,SHF_INFO_LINK,0,offset,data_size,getSegIndex(".symtab"),getSegIndex(".data"),8, sizeof(Elf64_Rela));//.rel.data
    Debug("data realation table:[%d,%d]",offset,offset + data_size);
    offset += data_size;
    //更新段表name
    for(auto str : shdrNames ){
        int index = strIndex[str];
        shdrTab[str]->sh_name = index;
    }
}

