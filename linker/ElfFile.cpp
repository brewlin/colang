#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

/**
 * 
 * @param buf 
 * @param offset 
 * @param size 
 */
void ElfFile::getData(char*buf,Elf64_Off offset,Elf64_Word size)
{
	FILE *fp = fopen(elf_dir,"rb");
	rewind(fp);
	//设置读取偏移量
	fseek(fp,offset,0);
	//读取数据
	fread(buf,size,1,fp);
	fclose(fp);
}
ElfFile::ElfFile():shstrtab(nullptr),strtab(nullptr),elf_dir(nullptr){}

/**
 * 解析elf文件
 * @param file
 */
void ElfFile::readElf(string file)
{
	elf_dir  = new char[file.length() + 1];
	strcpy(elf_dir,file.c_str());
	FILE*fp  = fopen(file.c_str(),"rb");
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
		Elf64_Sym*sym = new Elf64_Sym();
		fread(sym, sizeof(Elf64_Sym),1,fp);
		symList.push_back(sym);//添加到符号序列
		string name(strTabData + sym->st_name);
		if(name.empty() || name == "_GLOBAL_OFFSET_TABLE_")//无名符号，对于链接没有意义,按照链接器设计需要记录全局和局部符号，避免名字冲突
			delete sym;//删除空符号项
		else
		{
			//if(ELF64_ST_BIND(sym->st_info)==STB_GLOBAL)
				//printf("%s\t\t%d\n",strTabData+sym->st_name,sym->st_shndx);
			symTab[name]=sym;//加入符号表
		}
	}
	cout << elf_dir << "重定位数据" <<endl;
	for(auto i : shdrTab){
	    //目前数据和代码为了兼容 gnu 都是放在 rela.text中的
		if(i.first.find(".rela.text") == 0)//是重定位段
		{
			Elf64_Shdr *sh_relTab = shdrTab[i.first];//重定位表信息
			fseek(fp,sh_relTab->sh_offset,0);//转移到重定位表内容
			int relNum            = sh_relTab->sh_size / sizeof(Elf64_Rela);//重定位项数
			for(int j = 0 ; j < relNum ; ++j)
			{
				Elf64_Rela *rela = new Elf64_Rela();
				//获取重定位符号引用
				fread(rela, sizeof(Elf64_Rela),1,fp);
				int index = symList[ELF64_R_SYM(rela->r_info)]->st_name;
//				cout <<"relNum:" << relNum << " index:" << index  << " j:" << j << endl;
				string name(strTabData + index);//获得重定位符号名字
//				cout << "name:" << name <<endl;
				//使用shdrNames[sh_relTab->sh_info]访问目标段更标准
				relTab.push_back(new RelItem(i.first.substr(5),rela,name));//添加重定位项
//				printf("%s\t%08x\t%s\n",i.first.substr(4).c_str(),rela->r_offset,name.c_str());
			}
		}
	}
	delete []strTabData;//清空字符串表

	fclose(fp);
}
/**
 * 找段对应的索引
 * @param segName
 * @return
 */
int ElfFile::getSegIndex(string segName)
{
	int index = 0;
	for(auto name : shdrNames){
		//找到段
		if(name == segName)
			break;
		++index;
	}
	return index;
}
/**
 * 找到符号对应的索引
 * @param symName
 * @return
 */
int ElfFile::getSymIndex(string symName)
{
	int index = 0;
	for(auto name : symNames){
		//找到符号
		if(name == symName)
			break;
		++index;
	}
	return index;
}
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

ElfFile::~ElfFile()
{
	//清空程序头表
	for(auto i : phdrTab)
		delete i;
	phdrTab.clear();
	//清空段表
	for(auto i : shdrTab)
		delete i.second;
	shdrTab.clear();
	shdrNames.clear();
	//清空符号表
	for(auto i : symTab)
		delete  i.second;
	symTab.clear();
	//清空重定位表
	for(auto i : relTab)
		delete  i;
	relTab.clear();
	//清空临时存储数据
	if(shstrtab!=NULL)delete[] shstrtab;
	if(strtab!=NULL)delete[] strtab;
	if(elf_dir)
		delete elf_dir;
}
