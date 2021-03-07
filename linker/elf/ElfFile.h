
#ifndef COLANG_LINKER_ELF_FILE_H
#define	COLANG_LINKER_ELF_FILE_H

#include "elf.h"
#include <map>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
using namespace __gnu_cxx;

//构造重定位项信息
struct RelItem
{
	string     segname;//重定位的目标段名
	Elf64_Rela *rel;//重定位信息
	string     relname;//重定位符号名
	RelItem(string sname,Elf64_Rela *rel,string rname):
	segname(sname),
	rel(rel),
	relname(rname){}
	~RelItem(){delete  rel;}
};


//elf文件类，包含elf文件的重要内容，处理elf文件
class ElfFile
{
public:
    Elf64_Ehdr 				 ehdr;
	//程序头表
	vector<Elf64_Phdr*>  	 phdrTab;
	map<string, Elf64_Shdr*> shdrTab;//段表
	//段表名和索引的映射关系，方便符号查询自己的段信息
	vector<string>			 shdrNames;
	map<string,Elf64_Sym*>   symTab;//符号表
	vector<string>			 symNames;//符号名与符号表项索引的映射关系，对于重定位表生成重要
	vector<string>			 symbols;//符号名与符号表项索引的映射关系，对于重定位表生成重要
	vector<RelItem*>		 relTab;//重定位表
	//辅助数据
	char 					 *elf_dir;//处理elf文件的目录
	char					 *shstrtab;//段表字符串表数据
	unsigned int 			 shstrtabSize;//段表字符串表长
	char					 *strtab;//字符串表数据
	unsigned int 		     strtabSize;//字符串表长
public:
	ElfFile();
	~ElfFile();
	void readElf(string file);//读入elf
	void getData(char*buf,Elf64_Off offset,Elf64_Word size);//读取数据
	int  getSegIndex(string segName);//获取指定段名在段表下标
	int  getSymIndex(string symName);//获取指定符号名在符号表下标
	void addPhdr(Elf64_Word type,Elf64_Off off,Elf64_Addr vaddr,Elf64_Word filesz,
		Elf64_Word memsz,Elf64_Word flags,Elf64_Word align);//添加程序头表项
	void addShdr(string sh_name,Elf64_Word sh_type,Elf64_Word sh_flags,Elf64_Addr sh_addr,Elf64_Off sh_offset,
			Elf64_Word sh_size,Elf64_Word sh_link,Elf64_Word sh_info,Elf64_Word sh_addralign,
			Elf64_Word sh_entsize);//添加一个段表项
	void addSym(string st_name,Elf64_Sym*);//添加一个符号表项
	//写入elf头 + 程序头表
	int writeHeader(string out);
	//写入段 + 段那么字符串 + 符号表 + 符号名字符串
	int writeSecSym(string out);
};

#endif //elf_file.h
