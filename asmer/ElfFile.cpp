#include "ElfFile.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Log.h"
#include "Asmer.h"

int ElfFile::offset = 0;


RelInfo::RelInfo(string seg,int addr,string lb,int t)
{
	offset=addr;
	tarSeg=seg;
	name=lb;
	type=t;
}


ElfFile::ElfFile()
{
	shstrtab=NULL;
	strtab=NULL;
	addShdr("",0,0,0,0,0,0,0,0,0);//空段表项
	addSym("",NULL);//空符号表项
}

int ElfFile::pad(string first,string second)
{
	//填充段间的空隙
	char pad[1] = {0};
	int  num    = shdrTab[second]->sh_offset - (shdrTab[first]->sh_offset + shdrTab[first]->sh_size);
	cout << second << ":" << shdrTab[second]->sh_offset << ":" << first << ":" << shdrTab[first]->sh_offset + shdrTab[first]->sh_size << endl;
	int  ret = num;
	while(num--){
		Asmer::writeBytes(pad,1);
	}
	return ret;
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
void ElfFile::addSectionSym(){

	Elf64_Sym* elfsym = new Elf64_Sym();
	elfsym->st_name = 0;
	elfsym->st_value = 0;
	elfsym->st_size = 0;
	elfsym->st_info = ELF64_ST_INFO(STB_LOCAL,STT_SECTION);

	elfsym->st_other = 0;
	elfsym->st_shndx = getSegIndex(".text");
	addSym(".text",elfsym);
	elfsym->st_shndx = getSegIndex(".data");
	addSym(".data",elfsym);
	elfsym->st_info = ELF64_ST_INFO(STB_GLOBAL,STT_NOTYPE);
	elfsym->st_shndx = 0;
	addSym("_GLOBAL_OFFSET_TABLE_",elfsym);



}
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
//	cout << "符号:" << sym->name << " 所在段:" << sym->segName << " " <<elfsym->st_shndx <<endl;

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

void ElfFile::sortGlobal(){
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
	sh_info = local.size();
	for(auto str : global)
		symNames.push_back(str);
}



RelInfo* ElfFile::addRel(string seg,int addr,string name,int type)
{
	RelInfo *rel = new RelInfo(seg,addr,name,type);
	relTab.push_back(rel);
	return rel;
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
	ehdr.e_shnum     = 8;
	//段字符串表在 段表中的索引默认写死为4
	ehdr.e_shstrndx  = 3;

	//我们规定段表就在头部后面
	ehdr.e_shoff = sizeof(Elf64_Ehdr);

	offset = sizeof(Elf64_Ehdr);
//	std::cout << "[buildElf] header:[0," << offset <<"]" << std::endl;
}
/**
 * 构建段表
 */
void ElfFile::buildSectab(){
	//默认八个段 + 1个空段
//	std::cout << "[buildElf] .section table:[" << offset << "," << sizeof(Elf64_Shdr) * 9 <<"]" << std::endl;
	offset += sizeof(Elf64_Shdr) * 8;
};
void ElfFile::buildData(){
   	//表示当前的数据段的大小
	addShdr(".data",asmer::curAddr);
//	std::cout << "[buildElf] .data:[" << offset << "," << curAddr <<"]" << std::endl;
	//数据段紧跟其后
	offset += curAddr;
	Asmer::data = asmer::curAddr;
}
void ElfFile::buildText(){
    asmer::curAddr = 0;
    Asmer::obj->InstCollect();
    Instruct::ready = true;
	asmer::curAddr = 0;
    Asmer::obj->InstCollect();

	addShdr(".text",asmer::curAddr);
//	std::cout << "[buildElf] .text:[" << offset << "," << asmer::curAddr <<"]" << std::endl;
	offset += asmer::curAddr;
	Asmer::text = asmer::curAddr;
//	cout << asmer::curAddr <<endl;
	//到这里就源代码解析完了，需要导出所有符号表
	// addSectionSym();
	Asmer::obj->parser->symtable->exportSyms();

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
	std::string reltext = ".rela.text";
	std::string reldata = ".rela.data";
	std::string bss = ".bss";
	std::string shstrtab = ".shstrtab";
	std::string symtab = ".symtab";
	std::string strtab = ".strtab";
	std::string pading = "      ";

	//算出存储全部的段字符串需要多少空间
	//每个字符串末尾都要留一个空格
	shstrtab_size = reltext.length() + 1 +
						reldata.length() + 1 +
						// bss.length() + 1 +
						shstrtab.length() + 1 +
						symtab.length() + 1 +
						strtab.length() + 1 +
						pading.length();

	//开始构建存储所有的段字符串
	char *str = new char[shstrtab_size];
	this->shstrtab  = str;

	int index = 0;
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
	// strIndex[".bss"] = index;
	// strcpy(str + index, ".bss");
	// index += bss.length() + 1;
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
	//string segNames[]={"",".rela.text",".rel.data",".bss",".shstrtab",".symtab",".strtab"};
	//添加.shstrtab 段字符串表
	addShdr(".shstrtab", SHT_STRTAB, 0, 0, offset, shstrtab_size, SHN_UNDEF, 0, 1, 0);//.shstrtab
//	std::cout << "[buildElf] .shstrtab:[" << offset << "," << shstrtab_size <<"]" << std::endl;
	//下一个表
	offset += shstrtab_size;
}
//构建字符串表
void ElfFile::buildSymtab() {
	//进行global 和local 分类
	sortGlobal();
	//.symtab,sh_link 代表.strtab索引，默认在.symtab之后,sh_info不能确定
	//计算总共字符串表的大小
	strtab_size = symNames.size() * sizeof(Elf64_Sym);
	Debug("str_tab: offset[%d,%d] size:%d", offset, offset + strtab_size, strtab_size);
	//偏移跟上
	//计算字符串表的大小
	addShdr(".symtab", SHT_SYMTAB, 0, 0, offset,strtab_size, 0, 0, 1, sizeof(Elf64_Sym));
//	std::cout << "[buildElf] .symtab:[" << offset << "," << strtab_size <<"]" << std::endl;
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
//		cout << "[" << strs << "," << strs.length() + 1 << "]" << "index:" << index <<endl;
	}
	for(int i = 0; i < this->strtab_size ; i ++){
//		cout << strtab[i];
	}
//	cout << endl;
	//这里存储的是字符串区需要加上这个
//	std::cout << "[buildElf] .strtab:[" << offset << "," << strtab_size <<"]" << std::endl;
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
		Elf64_Rela *rela = new Elf64_Rela();
		rela->r_offset  = relTab[i]->offset;
		rela->r_info    = ELF64_R_INFO((Elf64_Word)getSymIndex(relTab[i]->name),relTab[i]->type);
		rela->r_addend  = -4;
		//将重定项中的类型进行区分，代码区和数据区
		if(relTab[i]->tarSeg == ".text")
			relTextTab.push_back(rela);
		else if(relTab[i]->tarSeg == ".data")
			relDataTab.push_back(rela);
	}
	//如果存在函数的外部引用，以及全局变量的外部引用,需要进行重定位
	//加上代码区
	int text_size = relTextTab.size() * sizeof(Elf64_Rela);
	addShdr(".rela.text",SHT_RELA,SHF_INFO_LINK,0,offset,text_size,getSegIndex(".symtab"),getSegIndex(".text"),1, sizeof(Elf64_Rela));//.rela.text
//	std::cout << "[buildElf] .rela.text:[" << offset << "," << text_size <<"]" << std::endl;
	offset += text_size;

	//加上代码区
	int data_size = relDataTab.size() * sizeof(Elf64_Rela);
	addShdr(".rela.data",SHT_RELA,SHF_INFO_LINK,0,offset,data_size,getSegIndex(".symtab"),getSegIndex(".data"),1, sizeof(Elf64_Rela));//.rel.data
//	std::cout << "[buildElf] .rela.data:[" << offset << "," << data_size <<"]" << std::endl;
	offset += data_size;
	for(int i = 0; i < shstrtab_size; i ++){
//		std::cout << shstrtab[i];
	}
//	std::cout <<std::endl;
	//更新段表name
	for(auto str : shdrNames ){
		int index = strIndex[str];
		shdrTab[str]->sh_name = index;
//		std::cout << "[buildElf] section_name_index:[" << str << "," << shdrTab[str]->sh_name <<"]" << std::endl;
	}
}


ElfFile::~ElfFile(){}


void ElfFile:: printAll()
{
	cout << "------------段信息------------" << endl;
	for(auto it : shdrTab){
		if(it.first == "")
			continue;
		cout << it.first << ":" << it.second->sh_offset<< endl;
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
		cout << it->tarSeg << ":" << it->offset << "<-" << it->name << endl;
	}
}
