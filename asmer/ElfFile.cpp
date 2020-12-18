#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Log.h"
#include "Asmer.h"



RelInfo::RelInfo(string seg,int addr,string lb,int t)
{
	offset=addr;
	tarSeg=seg;
	lbName=lb;
	type=t;
}


ElfFile::ElfFile()
{
	shstrtab=NULL;
	strtab=NULL;
	addShdr("",0,0,0,0,0,0,0,0,0);//空段表项
	addSym("",NULL);//空符号表项
}



int ElfFile::getSegIndex(string segName)
{
	int index = 0;
	for(int i = 0; i < shdrNames.size();++i){
		if(shdrNames[i]==segName)//找到段
			break;
		++index;
	}
	return index;
}

int ElfFile::getSymIndex(string symName)
{
	int index=0;
	for(int i=0;i<symNames.size();++i)
	{
		if(symNames[i]==symName)//找到符号
			break;
		++index;
	}
	return index;
}

//sh_name和sh_offset都需要重新计算
void ElfFile::addShdr(string sh_name,int size)
{
	if( sh_name == ".text")
	{
		addShdr(sh_name,SHT_PROGBITS,SHF_ALLOC|SHF_EXECINSTR,0,offset,size,0,0,4,0);
	}
	else if(sh_name==".data")
	{
		addShdr(sh_name,SHT_PROGBITS,SHF_ALLOC|SHF_WRITE,0,offset,size,0,0,4,0);
	}
	//没有bss段
}

void ElfFile::addShdr(string sh_name,Elf64_Word sh_type,Elf64_Word sh_flags,Elf64_Addr sh_addr,Elf64_Off sh_offset,
			Elf64_Word sh_size,Elf64_Word sh_link,Elf64_Word sh_info,Elf64_Word sh_addralign,
			Elf64_Word sh_entsize)//添加一个段表项
{
	Elf64_Shdr*sh=new Elf64_Shdr();
	sh->sh_name=0;
	sh->sh_type=sh_type;
	sh->sh_flags=sh_flags;
	sh->sh_addr=sh_addr;
	sh->sh_offset=sh_offset;
	sh->sh_size=sh_size;
	sh->sh_link=sh_link;
	sh->sh_info=sh_info;
	sh->sh_addralign=sh_addralign;
	sh->sh_entsize=sh_entsize;
	shdrTab[sh_name]=sh;
	shdrNames.push_back(sh_name);
}

void ElfFile::addSym(asmer::Sym* sym)
{
	//解析符号的全局性局部性，避免符号冲突
	std::string name 	 = sym->name;

	Elf64_Sym *elfsym 	 = new Elf64_Sym();
	elfsym->st_name   	 = 0;
	elfsym->st_value  	 = sym->addr;//符号段偏移,外部符号地址为0
	elfsym->st_size   	 = 8;        //目前只支持8位支持的全局变量定义，其他的函数标签不需要管
	//是否为全局
	if(sym->global)
		elfsym->st_info  = ELF64_ST_INFO(STB_GLOBAL,STT_NOTYPE);//全局符号
	else
		elfsym->st_info  = ELF64_ST_INFO(STB_LOCAL,STT_NOTYPE);//局部符号，避免名字冲突

	elfsym->st_other     = 0;
	if(sym->externed)
		elfsym->st_shndx = STN_UNDEF;
	else
		elfsym->st_shndx = getSegIndex(sym->segName);

	addSym(name,elfsym);
}

void ElfFile::addSym(string st_name,Elf64_Sym*s)
{
	Elf64_Sym*sym = symTab[st_name] = new Elf64_Sym();
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


RelInfo* ElfFile::addRel(string seg,int addr,string lb,int type)
{
	RelInfo *rel = new RelInfo(seg,addr,lb,type);
	relTab.push_back(rel);
	return rel;
}

void ElfFile::padSeg(string first,string second)//填充段间的空隙
{
//	char pad[1] = {0};
//	int padNum  = shdrTab[second]->sh_offset-(shdrTab[first]->sh_offset+shdrTab[first]->sh_size);
//	while(padNum--)
//	{
//		fwrite(pad,1,1,out);//填充
//	}
}

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
	ehdr.e_shnum     = 9;
	//段字符串表在 段表中的索引默认写死为4
	ehdr.e_shstrndx  = 4;

	//我们规定段表就在头部后面
	ehdr.e_shoff = sizeof(Elf64_Ehdr);

	offset = sizeof(Elf64_Ehdr);
}
/**
 * 构建段表
 */
void ElfFile::buildSectab(){
	//默认八个段 + 1个空段
	offset += sizeof(Elf64_Shdr) * 9;
};
void ElfFile::buildData(){
   	//表示当前的数据段的大小
	addShdr(".data",asmer::curAddr);
	//数据段紧跟其后
	offset += curAddr;
	//TODO: 后面要加上pad 对齐
}
void ElfFile::buildText(){
    //代码段还没有开始计算偏移量
    Asmer::obj->InstUpdate();
	addShdr(".text",asmer::curAddr);
	offset += asmer::curAddr;
	//TODO: 后面要加上pad对齐

	//到这里就源代码解析完了，需要导出所有符号表
	Asmer::obj->parser->symtable->exportSyms();

}
/**
 * 构建段字符串表
 */
void ElfFile::buildShstrtab() {

	/**
	 * 当前所处位置
	 * ehdr
	 * section table * 9
	 * text
	 * data
	 * now: 段字符串段表
	 */
	std::string reltext = ".rel.text";
	std::string reldata = ".rel.data";
	std::string bss = ".bss";
	std::string shstrtab = ".shstrtab";
	std::string symtab = ".symtab";
	std::string strtab = ".strtab";
	std::string pading = "      ";

	//算出存储全部的段字符串需要多少空间
	//每个字符串末尾都要留一个空格
	shstrtab_size = reltext.length() + 1 +
						reldata.length() + 1 +
						bss.length() + 1 +
						shstrtab.length() + 1 +
						symtab.length() + 1 +
						strtab.length() + 1 +
						pading.length();

	//开始构建存储所有的段字符串
	char *str = new char[shstrtab_size];
	this->shstrtab  = str;

	int index = 0;
	strIndex[".rel.text"] = index;
	strcpy(str + index, ".rel.text");
	//text段名 和 .rel.text 有相同部分，可以共用
	strIndex[".text"] = index + 4;
	index += reltext.length() + 1;
	strIndex[""] = index - 1;
	strIndex[".rel.data"] = index;
	strcpy(str + index, ".rel.data");
	//data段同样可以共用
	strIndex[".data"] = index + 4;
	index += reldata.length() + 1;
	strIndex[".bss"] = index;
	strcpy(str + index, ".bss");
	index += bss.length() + 1;
	strIndex[".shstrtab"] = index;
	strcpy(str + index, ".shstrtab");
	index += shstrtab.length() + 1;
	strIndex[".symtab"] = index;
	strcpy(str + index, ".symtab");
	index += symtab.length() + 1;
	strIndex[".strtab"] = index;
	strcpy(str + index, ".strtab");
	index += strtab.length() + 1;
	//for(int i=0;i<shstrtabSize;++i)printf("%c",str[i]);printf("\n");
	//for(int i=0;i<shstrtabSize;++i)printf("%d|",str[i]);printf("\n");
	//string segNames[]={"",".rel.text",".rel.data",".bss",".shstrtab",".symtab",".strtab"};
	//添加.shstrtab 段字符串表
	addShdr(".shstrtab", SHT_STRTAB, 0, 0, offset, shstrtab_size, SHN_UNDEF, 0, 1, 0);//.shstrtab
	//下一个表
	offset += shstrtab_size;
}
//构建字符串表
void ElfFile::buildSymtab() {

	//.symtab,sh_link 代表.strtab索引，默认在.symtab之后,sh_info不能确定
	//计算总共字符串表的大小
	strtab_size = symNames.size() * sizeof(Elf64_Sym);
	Debug("str_tab: offset[%d,%d] size:%d", offset, offset + strtab_size, strtab_size);
	//偏移跟上
	offset += strtab_size;
	//计算字符串表的大小
	addShdr(".symtab", SHT_SYMTAB, 0, 0, offset,strtab_size, 0, 0, 1, 16);
	//找到字符串段在段表中的索引，这里应该是4
	shdrTab[".symtab"]->sh_link = getSegIndex(".symtab") + 1;//.strtab默认在.symtab之后
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
	for (int i = 0; i < symNames.size(); ++i) {
		//更新符号表中对应于字符串的索引
		symTab[symNames[i]]->st_name = index;
		strcpy(str + index, symNames[i].c_str());
		index += symNames[i].length() + 1;
	}
	//这里存储的是字符串区需要加上这个
	offset += strtab_size;
	//for(int i=0;i<strtab_size;++i)printf("%c",str[i]);printf("\n");
	//for(int i=0;i<strtab_size;++i)printf("%d|",str[i]);printf("\n");
}
/**
 * 处理重定位表
 */
void ElfFile::buildRelTab(){
	//处理重定位表
	for(int i = 0 ;i < relTab.size() ; i++){
		Elf64_Rel *rel = new Elf64_Rel();
		rel->r_offset  = relTab[i]->offset;
		rel->r_info    = ELF64_R_INFO((Elf64_Word)getSymIndex(relTab[i]->lbName),relTab[i]->type);
		//将重定项中的类型进行区分，代码区和数据区
		if(relTab[i]->tarSeg == ".text")
			relTextTab.push_back(rel);
		else if(relTab[i]->tarSeg == ".data")
			relDataTab.push_back(rel);
	}
	//如果存在函数的外部引用，以及全局变量的外部引用,需要进行重定位
	//加上代码区
	int text_size = relDataTab.size() * sizeof(Elf64_Rel);
	addShdr(".rel.text",SHT_REL,0,0,offset,text_size,getSegIndex(".symtab"),getSegIndex(".text"),1,8);//.rel.text
	offset += text_size;

	//加上代码区
	addShdr(".rel.data",SHT_REL,0,0,offset,relDataTab.size()*8,getSegIndex(".symtab"),getSegIndex(".data"),1,8);//.rel.data
	//更新段表name
	for(int i = 0; i < shdrNames.size();++i){
		int index = strIndex[shdrNames[i]];
		shdrTab[shdrNames[i]]->sh_name=index;
	}
}


ElfFile::~ElfFile(){}


void ElfFile:: printAll()
{
	cout << "------------段信息------------" << endl;
	for(auto it : shdrTab){
		if(it.first == "")
			continue;
		cout << it.first << ":" << it.second->sh_size << endl;
	}
	cout << "------------符号信息------------" << endl;
	for(auto it : symTab){
		if(it.first=="")
			continue;
		cout << it.first << ":";
		if(it.second->st_shndx==0)
			cout << "外部";
		if(ELF64_ST_BIND(it.second->st_info) == STB_GLOBAL)
			cout << "全局";
		else if(ELF64_ST_BIND(it.second->st_info) == STB_LOCAL)
			cout << "局部";
		cout << endl;
	}
	cout << "------------重定位信息------------" << endl;
	for(auto it : relTab){
		cout << it->tarSeg << ":" << it->offset << "<-" << it->lbName << endl;
	}
}
