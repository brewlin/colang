//
// Created by root on 2021/3/7.
//
#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;
/**
 * 解析elf文件
 * @param file
 */
void ElfFile::readElf(string file)
{
    elf_dir  = new char[file.length() + 1];
    strcpy(elf_dir,file.c_str());
    FILE*fp  = fopen(file.c_str(),"rb");
    if(!fp){
        cout << "file invalid:" << elf_dir <<endl;
        exit(1);
    }
    rewind(fp);
    fread(&ehdr,sizeof(Elf64_Ehdr),1,fp);//读取文件头

    //可执行文件拥有程序头表
    //可重定向elf没有程序头表
    if(ehdr.e_type == ET_EXEC)
    {
        fseek(fp,ehdr.e_phoff,0);//程序头表位置
        for(int i = 0;i < ehdr.e_phnum; ++i)//读取程序头表
        {
            Elf64_Phdr *phdr = new Elf64_Phdr();
            fread(phdr, sizeof(Elf64_Phdr),1,fp);//读取程序头
            phdrTab.push_back(phdr);//加入程序头表
        }
    }

    fseek(fp,ehdr.e_shoff + ehdr.e_shentsize * ehdr.e_shstrndx,0);//段表字符串表位置
    Elf64_Shdr shstrTab;
    //读取段表字符串表项
    fread(&shstrTab, sizeof(Elf64_Shdr),1,fp);
    char* shstrTabData = new char[shstrTab.sh_size];
    fseek(fp,shstrTab.sh_offset,0);//转移到段表字符串表内容
    //读取段表字符串表
    fread(shstrTabData, shstrTab.sh_size,1,fp);
    //for(int i=0;i<shstrTab.sh_size;i++)printf("%c",shstrTabData[i]);printf("\t--shstrTab\n");

    //段表位置
    fseek(fp,ehdr.e_shoff,0);
    for(int i = 0;i < ehdr.e_shnum; ++i)//读取段表
    {
        Elf64_Shdr *shdr = new Elf64_Shdr();
        //读取段表项[非空]
        fread(shdr, sizeof(Elf64_Shdr),1,fp);
        string name(shstrTabData + shdr->sh_name);
        shdrNames.push_back(name);//记录段表名位置
        if(name.empty())
            delete shdr;//删除空段表项
        else
        {
            //printf("%s\t\t%08x\n",shstrTabData+shdr->sh_name,shdr->sh_addralign);
            shdrTab[name] = shdr;//加入段表
        }
    }
    delete []shstrTabData;//清空段表字符串表

    Elf64_Shdr *strTab = shdrTab[".strtab"];//字符串表信息
    char   *strTabData = new char[strTab->sh_size];
    fseek(fp,strTab->sh_offset,0);//转移到字符串表内容
    fread(strTabData,strTab->sh_size,1,fp);//读取字符串表
    //for(int i = 0;i<strTab->sh_size;i++)printf("%c",strTabData[i]);printf("\t--strTab\n");

    Elf64_Shdr *sh_symTab = shdrTab[".symtab"];//符号表信息
    fseek(fp,sh_symTab->sh_offset,0);//转移到符号表内容
    //计算符号个数
    int symNum = sh_symTab->sh_size / sh_symTab->sh_entsize;
    vector<Elf64_Sym*>   symList;//按照序列记录符号表所有信息，方便重定位符号查询
    for(int i = 0;i < symNum;++i)//读取符号
    {
        Elf64_Sym *sym = new Elf64_Sym();
        fread(sym, sizeof(Elf64_Sym),1,fp);
        symList.push_back(sym);//添加到符号序列
        string name(strTabData + sym->st_name);
        symbols.push_back(name);

        if(name == "_GLOBAL_OFFSET_TABLE_"){
            delete sym;
        }else if(!name.empty())
        {
            //if(ELF64_ST_BIND(sym->st_info)==STB_GLOBAL)
            //printf("%s\t\t%d\n",strTabData+sym->st_name,sym->st_shndx);
            symTab[name] = sym;//加入符号表
        }
        else if(sym->st_shndx != SHN_UNDEF && sym->st_name == 0){
            //可能是段名
            name = shdrNames[sym->st_shndx];
            if(!name.empty()){
                symTab[name] = sym;
            }


        }
    }
//	cout << elf_dir << "重定位数据" <<endl;
    for(auto i : shdrTab){
        //目前数据和代码为了兼容 gnu 都是放在 rela.text中的
        if(i.first.find(".rela.text") == 0 || i.first.find(".rela.data") == 0)//是重定位段
        {
            Elf64_Shdr *sh_relTab = shdrTab[i.first];//重定位表信息
            fseek(fp,sh_relTab->sh_offset,0);//转移到重定位表内容
            int relNum            = sh_relTab->sh_size / sizeof(Elf64_Rela);//重定位项数
            for(int j = 0 ; j < relNum ; ++j)
            {
                Elf64_Rela *rela = new Elf64_Rela();
                //获取重定位符号引用
                fread(rela, sizeof(Elf64_Rela),1,fp);
//				cout << "rela->r_info:"<< ELF64_R_SYM(rela->r_info) << endl;
                Elf64_Sym* sym = symList[ELF64_R_SYM(rela->r_info)];
                int index      = sym->st_name;
//				cout <<"relNum:" << relNum << " index:" << index  << " j:" << j << endl;
                string name(strTabData + index);//获得重定位符号名字
//				cout << "name:" << name <<endl;
                //使用shdrNames[sh_relTab->sh_info]访问目标段更标准
                //有些重定位符号是 基于段偏移  比如 .rodata 就是存在与段表里面的
                if(name == "" && sym->st_shndx != SHN_UNDEF){
                    name = shdrNames[sym->st_shndx];
                }
//				cout << "name:" << name << " inde:" << index << endl;
                relTab.push_back(new RelItem(i.first.substr(5),rela,name));//添加重定位项
//				printf("%s\t%08x\t%s\n",i.first.substr(4).c_str(),rela->r_offset,name.c_str());
            }
        }
    }
    delete []strTabData;//清空字符串表

    fclose(fp);
}

