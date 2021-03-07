//
// Created by root on 2021/3/7.
//
#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;


/**
 * 添加一个程序表项
 * @param type
 * @param off
 * @param vaddr
 * @param filesz
 * @param memsz
 * @param flags
 * @param align
 */
void ElfFile::addPhdr(Elf64_Word type,Elf64_Off off,Elf64_Addr vaddr,Elf64_Word filesz,
                      Elf64_Word memsz,Elf64_Word flags,Elf64_Word align){

    Elf64_Phdr*ph = new Elf64_Phdr();
    ph->p_type    = type;
    ph->p_offset  = off;
    ph->p_vaddr   = ph->p_paddr = vaddr;
    ph->p_filesz  = filesz;
    ph->p_memsz   = memsz;
    ph->p_flags   = flags;
    ph->p_align   = align;
    phdrTab.push_back(ph);
}
/**
 * 添加一个段表项
 * @param sh_name
 * @param sh_type
 * @param sh_flags
 * @param sh_addr
 * @param sh_offset
 * @param sh_size
 * @param sh_link
 * @param sh_info
 * @param sh_addralign
 * @param sh_entsize
 */
void ElfFile::addShdr(string sh_name,Elf64_Word sh_type,Elf64_Word sh_flags,Elf64_Addr sh_addr,Elf64_Off sh_offset,
                      Elf64_Word sh_size,Elf64_Word sh_link,Elf64_Word sh_info,Elf64_Word sh_addralign,
                      Elf64_Word sh_entsize){
    Elf64_Shdr*sh    = new Elf64_Shdr();
    sh->sh_name      = 0;
    sh->sh_type      = sh_type;
    sh->sh_flags     = sh_flags;
    sh->sh_addr      = sh_addr;
    sh->sh_offset    = sh_offset;
    sh->sh_size      = sh_size;
    sh->sh_link      = sh_link;
    sh->sh_info      = sh_info;
    sh->sh_addralign = sh_addralign;
    sh->sh_entsize   = sh_entsize;
    shdrTab[sh_name] = sh;
    shdrNames.push_back(sh_name);
}

/**
 *
 * @param st_name
 * @param s
 */
void ElfFile::addSym(string st_name,Elf64_Sym *s)
{
    Elf64_Sym* sym    = new Elf64_Sym();
    symTab[st_name]   = sym;
    if(st_name == "")
    {
        sym->st_name  = 0;
        sym->st_value = 0;
        sym->st_size  = 0;
        sym->st_info  = 0;
        sym->st_other = 0;
        sym->st_shndx = 0;
    }
    else
    {
        sym->st_name  = 0;
        sym->st_value = s->st_value;
        sym->st_size  = s->st_size;
        sym->st_info  = s->st_info;
        sym->st_other = s->st_other;
        sym->st_shndx = s->st_shndx;
    }
    symNames.push_back(st_name);
}

/**
 * 1. 写入header头
 * 2. 写入程序表头
 * @param out
 * @return
 */
int ElfFile::writeHeader(string out) {
    int bytes = 0;

    FILE *fp = fopen(out.c_str(), "w+");
    bytes += ehdr.e_ehsize;
    fwrite(&ehdr, ehdr.e_ehsize, 1, fp);//elf文件头
    if (!phdrTab.empty())//程序头表
    {
        for (auto phd : phdrTab) {
            bytes += ehdr.e_phentsize;
            fwrite(phd, ehdr.e_phentsize, 1, fp);
        }
    }
    fclose(fp);
    return bytes;
}
/**
 * 1. 写入段表 + 段字符串表
 * 2. 写入符号表 + 符号字符串表
 * @param out
 * @return
 */
int ElfFile::writeSecSym(string out) {
    int bytes = 0;

    FILE*fp = fopen(out.c_str(),"a+");
    bytes += shstrtabSize;
    //字符串段表: 写入所有关于段名的字符串 .shstrtab
    fwrite(shstrtab,shstrtabSize,1,fp);
    //段表: 写入所有段
    for(int i = 0;i<shdrNames.size();++i)
    {
        Elf64_Shdr *sh = shdrTab[shdrNames[i]];
        bytes += ehdr.e_shentsize;
        fwrite(sh,ehdr.e_shentsize,1,fp);
    }
    //符号表: 写入所有符号
    for(int i = 0;i<symNames.size();++i)
    {
        Elf64_Sym*sym = symTab[symNames[i]];
        bytes += sizeof(Elf64_Sym);
        fwrite(sym,sizeof(Elf64_Sym),1,fp);
    }
    //字符串表: 写入所有字符串
    bytes += strtabSize;
    fwrite(strtab,strtabSize,1,fp);
    fclose(fp);

    return bytes;
}

