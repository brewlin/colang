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
	if(!fp){
		cout << "file invalid:" << elf_dir <<endl;
		exit(1);
	}
	rewind(fp);
	//设置读取偏移量
	fseek(fp,offset,0);
	//读取数据
	fread(buf,size,1,fp);
	fclose(fp);
}
ElfFile::ElfFile():shstrtab(nullptr),strtab(nullptr),elf_dir(nullptr){}

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
