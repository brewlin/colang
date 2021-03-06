#ifndef _ELF_FILE_H
#define	_ELF_FILE_H

//elf文件所有数据结构和宏定义
#include "elf.h"
#include "asmer/ast/Sym.h"
//STL模板库
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;
using namespace asmer;
using namespace __gnu_cxx;

class Asmer;

//重定位信息
struct RelInfo
{
	string tarSeg;//重定位目标段
	int offset;//重定位位置的偏移
	string name;//重定位符号的名称
	int type;//重定位类型0-R_386_32；1-R_386_PC32
	RelInfo(string seg,int addr,string name,int t):
	tarSeg(seg),
	offset(addr),
	name(name),
	type(t){}
};


//elf文件类，包含elf文件的重要内容，处理elf文件
class ElfFile
{
public:
	int  offset;
	//elf文件重要数据结构
	Elf64_Ehdr ehdr;//文件头
	map<string, Elf64_Shdr*> shdrTab;//段表
	map<string,int>          strIndex; //段字符串表
	vector<string>			 shdrNames;//段表名和索引的映射关系，方便符号查询自己的段信息
	map<string,Elf64_Sym*>   symTab; //符号表
	vector<string>			 symNames;//符号名与符号表项索引的映射关系，对于重定位表生成重要
	vector<RelInfo*>		 relTab;//重定位表
	vector<Elf64_Rela*>       relTextTab,relDataTab;
	//辅助数据
	char	*shstrtab;//段表字符串表数据
	int 	shstrtab_size;//段表字符串表长
	char	*strtab;//字符串表数据
	int 	strtab_size;//字符串表长
	int		sh_info;

	Asmer* asmer;
public:
	ElfFile(Asmer* asmer);
	int getSegIndex(string segName);//获取指定段名在段表下标
	int getSymIndex(string symName);//获取指定符号名在符号表下标
	void addShdr(string sh_name,int size);
	void addShdr(string sh_name,Elf64_Word sh_type,Elf64_Word sh_flags,Elf64_Addr sh_addr,Elf64_Off sh_offset,
			Elf64_Word sh_size,Elf64_Word sh_link,Elf64_Word sh_info,Elf64_Word sh_addralign,
			Elf64_Word sh_entsize);//添加一个段表项
	void addSym(asmer::Sym* sym);
	void addSym(string st_name,Elf64_Sym*);//添加一个符号表项
	void sortGlobal();
	void addSectionSym();
	RelInfo* addRel(string seg,int addr,string name,int type);//添加一个重定位项，相同段的重定位项连续（一般是先是.rel.text后.rel.data）

	//构建头部和段表
	void buildEhdr();
	void buildSectab();
	void buildData();
	void buildText();
	void buildShstrtab();
	void buildSymtab();
	void buildStrtab();
	void buildRelTab();
	~ElfFile(){}
};

#endif //elf_file.h
