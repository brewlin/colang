#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Log.h"
#include "Asmer.h"

/**
 * @param asmer
 */
ElfFile::ElfFile(Asmer* asmer)
{
    offset = 0;
    this->asmer = asmer;
	shstrtab = NULL;
	strtab   = NULL;
	//空段表项
	addShdr("",0,0,0,0,0,0,0,0,0);
	//空符号表项
	addSym("",NULL);
}

/**
 *
 * @param segName
 * @return
 */
int ElfFile::getSegIndex(string segName)
{
	int index = 0;
	for(int i = 0; i < shdrNames.size();++i){
		//找到段
		if(shdrNames[i] == segName)
			break;
		++index;
	}
	return index;
}
/**
 *
 * @param symName
 * @return
 */
int ElfFile::getSymIndex(string symName)
{
	int index = 0;
	for(int i = 0;i < symNames.size(); ++i)
	{
		//找到符号
		if(symNames[i] == symName)
			break;
		++index;
	}
	return index;
}

/**
 *
 * @param sh_name
 * @param size
 */
void ElfFile::addShdr(string sh_name,int size)
{
	if( sh_name == ".text")
	{
		addShdr(sh_name,SHT_PROGBITS,SHF_ALLOC|SHF_EXECINSTR,0,offset,size,0,0,1,0);
	}
	else if(sh_name == ".data")
	{
		addShdr(sh_name,SHT_PROGBITS,SHF_ALLOC|SHF_WRITE,0,offset,size,0,0,1,0);
	}
	//没有bss段
}
/**
 *
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
void ElfFile::addShdr(
	string sh_name,
	Elf64_Word sh_type,
	Elf64_Word sh_flags,
	Elf64_Addr sh_addr,
	Elf64_Off sh_offset,
	Elf64_Word sh_size,
	Elf64_Word sh_link,
	Elf64_Word sh_info,
	Elf64_Word sh_addralign,
	Elf64_Word sh_entsize)
{
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
 * 添加默认的符号
 */
void ElfFile::addSectionSym()
{

	Elf64_Sym* elfsym = new Elf64_Sym();
	elfsym->st_name   = 0;
	elfsym->st_value  = 0;
	elfsym->st_size   = 0;
	elfsym->st_info   = ELF64_ST_INFO(STB_LOCAL,STT_SECTION);

	elfsym->st_other = 0;
	elfsym->st_shndx = getSegIndex(".text");
	addSym(".text",elfsym);
	elfsym->st_shndx = getSegIndex(".data");
	addSym(".data",elfsym);

}
/**
 * 添加符号，一般由parser那边导入过来
 * @param sym
 */
void ElfFile::addSym(asmer::Sym* sym)
{
	//解析符号的全局性局部性，避免符号冲突
	std::string name 	 = sym->name;
	Elf64_Sym *elfsym 	 = new Elf64_Sym();
	elfsym->st_name   	 = 0;
	elfsym->st_value  	 = sym->addr;//符号段偏移,外部符号地址为0
	elfsym->st_size   	 = 0;        //目前只支持8位支持的全局变量定义，其他的函数标签不需要管
	//外部符号也是全局
	if(sym->global || sym->externed)
		elfsym->st_info  = ELF64_ST_INFO(STB_GLOBAL,STT_NOTYPE);//全局符号
	else
		elfsym->st_info  = ELF64_ST_INFO(STB_LOCAL,STT_NOTYPE);//局部符号，避免名字冲突

	elfsym->st_other     = 0;
	if(sym->externed){
		elfsym->st_shndx = STN_UNDEF;
	}else{
		elfsym->st_shndx = getSegIndex(sym->segName);
	}
	Debug("symbol:%s section:%d ",sym->name.c_str(),sym->segName.c_str());
	addSym(name,elfsym);
}
/**
 *
 * @param st_name
 * @param s
 */
void ElfFile::addSym(string st_name,Elf64_Sym*s)
{
	Elf64_Sym *sym = symTab[st_name] = new Elf64_Sym();
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
 * 为了兼容gnu 链接器
 * 需要将符号表进行排序
 * 将GLOBAL类型放到最下面,并记录第一个GLOBAL索引位置
 */
void ElfFile::sortGlobal()
{
	vector<string> global;
	vector<string> local;
	for(auto str : symNames){
		auto sym = symTab[str];
		if(sym->st_info == ELF64_ST_INFO(STB_GLOBAL,STT_NOTYPE)){
			global.push_back(str);
		}else{
			local.push_back(str);
		}
	}
	symNames.clear();
	for(auto str : local)
		symNames.push_back(str);
	//第一个GLOBAL索引位置
	sh_info = local.size();
	for(auto str : global)
		symNames.push_back(str);
}
/**
 *
 * @param seg
 * @param addr
 * @param name
 * @param type
 * @return
 */
RelInfo* ElfFile::addRel(string seg,int addr,string name,int type)
{
	RelInfo *rel = new RelInfo(seg,addr,name,type);
	relTab.push_back(rel);
	return rel;
}
