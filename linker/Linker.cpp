#include "Linker.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

using  namespace std;

int Linker::bytes = 0;

Block::Block(char*d,unsigned int off,unsigned int s)
{

	data=d;
	offset=off;
	size=s;
}

Block::~Block()
{

	delete [] data;
}

SegList::~SegList()
{
	ownerList.clear();
	for(int i=0;i<blocks.size();++i)
	{
		delete blocks[i];
	}
	blocks.clear();
}

/*
	name:段名
	off:文件偏移地址
	base:加载基址，修改后提供给其他段
*/
void SegList::allocAddr(string name,unsigned int& base,unsigned int& off)
{

	begin = off;//记录对齐前偏移
	//虚拟地址对齐，让所有的段按照4k字节对齐
	if(name!=".bss")//.bss段直接紧跟上一个段，一般是.data,因此定义处理段时需要将.data和.bss放在最后
		base += (MEM_ALIGN-base%MEM_ALIGN)%MEM_ALIGN;
	//偏移地址对齐，让一般段按照4字节对齐，文本段按照16字节对齐
	int align = DISC_ALIGN;
	if(name ==".text")
		align=16;
	off    += (align-off%align)%align;
	//使虚址和偏移按照4k模同余
	base    = base-base%MEM_ALIGN+off%MEM_ALIGN;
	//累加地址和偏移
	baseAddr= base;
	offset  = off;
	size     = 0;
	for(int i = 0;i < ownerList.size(); ++i)
	{
		size += (DISC_ALIGN - size % DISC_ALIGN) % DISC_ALIGN;//对齐每个小段，按照4字节
		Elf64_Shdr*seg=ownerList[i]->shdrTab[name];
		//读取需要合并段的数据
		if(name!=".bss")
		{
			char* buf=new char[seg->sh_size];//申请数据缓存
			ownerList[i]->getData(buf,seg->sh_offset,seg->sh_size);//读取数据
			blocks.push_back(new Block(buf,size,seg->sh_size));//记录数据，对于.bss段数据是空的，不能重定位！没有common段！！！
		}
		//修改每个文件中对应段的addr
		seg->sh_addr=base+size;//修改每个文件的段虚拟，为了方便计算符号或者重定位的虚址，不需要保存合并后文件偏移
		size+=seg->sh_size;//累加段大小
	}
	base+=size;//累加基址
	if(name!=".bss")//.bss段不修改偏移
		off+=size;
	
}

/*
	relAddr:重定位虚拟地址
	type:重定位类型
	symAddr:重定位符号的虚拟地址
*/
void SegList::relocAddr(unsigned int relAddr,unsigned char type,unsigned int symAddr,int addend)
{

	unsigned int relOffset = relAddr-baseAddr;//同类合并段的数据偏移
	//查找修正地址所在位置
	Block*b = NULL;
	for(int i = 0;i < blocks.size(); ++i)
	{
		if(blocks[i]->offset <= relOffset && blocks[i]->offset + blocks[i]->size > relOffset)
		{
			b=blocks[i];
			break;//找到了
		}
	}
	//处理字节为b->data[relOffset-b->offset]
//	int *pAddr = (int*)(b->data + relOffset + addend - b->offset);
	int *pAddr = (int*)(b->data + relOffset  - b->offset);

	//对于 mov 0x(rip),%rax 这种需要在修正偏移量的时候改写指令
	//TODO:只针对 mov gplt引用进行了重写指令，其他的重写指令后续在补充
	if(type == 42)//绝对地址修正
	{
//		printf("绝对地址修正：原地址=%08x\t",*pAddr);
//		*pAddr = symAddr - relAddr +*pAddr;
		unsigned  char * inst = (unsigned char *)pAddr;
		inst --;
		unsigned char * modr = inst;
		inst  --;
		unsigned char * opcode = inst;

		if(*opcode == 0x8b){
			unsigned  char reg = (*modr - 0x05)/8;
			*opcode = 0xc7;
			*modr   = 0xc0 + reg;
		}
		*pAddr = symAddr - addend;
//		printf("修正后地址=%08x\n",*pAddr);
	}
	else if(type == R_X86_64_PC32)//相对地之修正
	{
//		printf("相对地址修正：原地址=%08x\t",*pAddr);
		*pAddr = symAddr - relAddr + *pAddr;
//		printf("修正后地址=%08x\n",*pAddr);
	}else if(type == R_X86_64_PLT32)
	{
		*pAddr = symAddr - relAddr + *pAddr;
	}
}

Linker::Linker()
{
	segNames.push_back(".text");
	segNames.push_back(".data");
	segNames.push_back(".bss");//.bss段有尾端对齐功能，不能删除
	for(int i=0;i<segNames.size();++i)
		segLists[segNames[i]]=new SegList();
}

/**
 * 1. 解析elf文件
 * 2. 加入vector中管理
 * @param dir
 */
void Linker::addElf(string obj)
{
	ElfFile *elf = new ElfFile();
	//解析elf文件
	elf->readElf(obj);
	elfs.push_back(elf);
}


void Linker::collectInfo() {

    //扫描文件
    for (auto elf : elfs) {
        //记录段表信息
        for (auto seg : segNames)
            if (elf->shdrTab.find(seg) != elf->shdrTab.end())
                segLists[seg]->ownerList.push_back(elf);
		//记录符号引用信息
		for (auto sym : elf->symTab) {
			SymLink *symLink = new SymLink();
			symLink->name = sym.first;//记录名字
			if (sym.second->st_shndx == STN_UNDEF)//引用符号
			{
				symLink->recv = elf;//记录引用文件
				symLink->prov = NULL;//标记未定义
				symLinks.push_back(symLink);
				//printf("%s---未定义\n",symLink->name.c_str());
			} else if(sym.second->st_shndx != SHN_ABS) {
				symLink->prov = elf;//记录定义文件
				symLink->recv = NULL;//标示该定义符号未被任何文件引用
				cout << sym.first <<endl;
				symDef.push_back(symLink);
				//printf("%s---定义\n",symLink->name.c_str());
			}
		}
    }
}
/**
 * 符号引用认证
 */
bool Linker::symValid()
{
	bool flag  = true;
	startOwner = NULL;
	for(int i = 0;i < symDef.size();++i)//遍历定义的符号,寻找重定义信息，和入口信息
	{
		if(ELF64_ST_BIND(symDef[i]->prov->symTab[symDef[i]->name]->st_info) != STB_GLOBAL)//只考虑全局符号
			continue;
		if(symDef[i]->name == "_start")//记录程序入口文件
			startOwner = symDef[i]->prov;

		for(int j = i + 1;j < symDef.size(); ++j)//遍历后边定义的符号
		{
			if(ELF64_ST_BIND(symDef[j]->prov->symTab[symDef[j]->name]->st_info) != STB_GLOBAL)//只考虑全局符号
				continue;
			//printf("%s---VS---%s\n",symDef[i]->name.c_str(),symDef[j]->name.c_str());
			if(symDef[i]->name==symDef[j]->name//同名符号
				//&&symDef[i]->prov->symTab[symDef[i]->name]->st_info
				//==symDef[j]->prov->symTab[symDef[j]->name]->st_info
			)//类型相同[!!!不允许函数名符号和变量名符号相同,在汇编时无法区分这种差别!!!]
			{
				//unsigned char info=symDef[i]->prov->symTab[symDef[i]->name]->st_info;
				//string type;
				//if(ELF64_ST_TYPE(info)==STT_OBJECT)type="变量";
				//else if(ELF64_ST_TYPE(info)==STT_FUNC)type="函数";
				//else type="符号";
				printf("符号名%s在文件%s和文件%s中发生链接冲突。\n",symDef[i]->name.c_str()
				,symDef[i]->prov->elf_dir,symDef[j]->prov->elf_dir);
				flag=false;
			}
		}
	}
	if(startOwner == NULL)
	{
		cout << "链接器找不到程序入口:_start" <<endl;
		flag = false;
	}
	for(int i = 0;i < symLinks.size();++i)//遍历未定义符号
	{
		for(int j = 0;j < symDef.size();++j)//遍历定义的符号
		{
			if(ELF64_ST_BIND(symDef[j]->prov->symTab[symDef[j]->name]->st_info) != STB_GLOBAL)//只考虑全局符号
				continue;
			//printf("%s---VS---%s,%d<->%d\n",symLinks[i]->name.c_str(),symDef[j]->name.c_str()
				//,symLinks[i]->recv->symTab[symLinks[i]->name]->st_info
				//,symDef[j]->prov->symTab[symDef[j]->name]->st_info);
			if(symLinks[i]->name == symDef[j]->name//同名符号
				//&&symLinks[i]->recv->symTab[symLinks[i]->name]->st_info
				//==symDef[j]->prov->symTab[symDef[j]->name]->st_info
			)//类型相同[!!!不允许函数名符号和变量名符号相同,在汇编时无法区分这种差别!!!]
			{
				symLinks[i]->prov=symDef[j]->prov;//记录符号定义的文件信息
				symDef[j]->recv=symDef[j]->prov;//该赋值没有意义，只是保证recv不为NULL
				//printf("解析%s\n",symLinks[i]->name.c_str());
			}
		}
		//未定义
		if(symLinks[i]->prov == NULL)
		{
			unsigned char info = symLinks[i]->recv->symTab[symLinks[i]->name]->st_info;
			string type;
			if(ELF64_ST_TYPE(info) == STT_OBJECT){
				type = "变量";
			}else if(ELF64_ST_TYPE(info) == STT_FUNC){
				type = "函数";
			}else{
				type = "符号";
			}
			printf("文件%s的%s名%s未定义。\n",symLinks[i]->recv->elf_dir
				,type.c_str(),symLinks[i]->name.c_str());
			if(flag)
				flag=false;
		}
	}
	return flag;
}
/**
 * 分配地址空间
 */
void Linker::allocAddr()
{
	//当前加载基址
	unsigned int curAddr = BASE_ADDR;
	//默认文件偏移,PHT保留.bss段
	unsigned int curOff  = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * segNames.size();
	cout << "地址分配" << endl;
	//按照类型分配地址，不紧邻.data与.bss段
	for(auto seg : segNames){
		//unsigned int oldOff=curOff;//记录分配前的文件偏移
		segLists[seg]->allocAddr(seg,curAddr,curOff);//自动分配
		//if(segNames[i]==".bss")//不做处理，在函数内部对off不累加
		//	segLists[segNames[i]]->offset=segLists[segNames[i]]->end=curOff=oldOff;//撤销.bss对curOff的修改
		printf("%s\taddr=%08x\toff=%08x\tsize=%08x(%d)\n",seg.c_str(),
			segLists[seg]->baseAddr,segLists[seg]->offset
			,segLists[seg]->size,segLists[seg]->size);
	}
}

void Linker::symParser()
{
	//扫描所有定义符号，原地计算虚拟地址
	cout << "----------定义符号解析----------" << endl;
	for(auto def : symDef){
		Elf64_Sym *sym = def->prov->symTab[def->name];//定义的符号信息
		string segName = def->prov->shdrNames[sym->st_shndx];//段名
		//if(sym->st_shndx==SHN_COMMON)//bss,该链接器定义不允许出现COMMON
			//segName=".bss";
		sym->st_value = sym->st_value + def->prov->shdrTab[segName]->sh_addr;//段基址
		printf("%s\t%08x\t%s\n",def->name.c_str(),sym->st_value,def->prov->elf_dir);
	}
	//扫描所有符号引用，绑定虚拟地址
	cout << "----------未定义符号解析----------" << endl;

	for(auto sym : symLinks){
		cout << sym->name <<endl;
		Elf64_Sym* provsym = sym->prov->symTab[sym->name];//被引用的符号信息
		Elf64_Sym* recvsym = sym->recv->symTab[sym->name];//被引用的符号信息
		recvsym->st_value = provsym->st_value;//被引用符号已经解析了
		printf("%s\t%08x\t%s\n",sym->name.c_str(),recvsym->st_value,sym->recv->elf_dir);
	}
}
/**
 * 重定位
 */
void Linker::relocate()
{
	//重定位项符号必然在符号表中，且地址已经解析完毕
	printf("--------------重定位----------------\n");
	for(auto elf : elfs){
		vector<RelItem*> tab = elf->relTab;//得到重定位表

		for(auto t : tab){
			if(t->relname == "")continue;
			Elf64_Sym* sym = elf->symTab[t->relname];//重定位符号信息
			unsigned int symAddr = sym->st_value + t->rel->r_addend;//解析后的符号段偏移为虚拟地址
			unsigned int relAddr = elf->shdrTab[t->segname]->sh_addr + t->rel->r_offset;//重定位地址
			//重定位操作
			printf("%s\trelAddr=%08x\tsymAddr=%08x\n",t->relname.c_str(),relAddr,symAddr);
			segLists[t->segname]->relocAddr(relAddr,ELF64_R_TYPE(t->rel->r_info),symAddr,t->rel->r_addend);
		}
	}
}

void Linker::buildExe()
{
	//封装头部
	int *p_id = (int*)exe.ehdr.e_ident;
	*p_id     = 0x464c457f;p_id++;
	*p_id     = 0x010102;  p_id++;
	*p_id     = 0;         p_id++;
	*p_id     = 0;
	exe.ehdr.e_type    = ET_EXEC;
	exe.ehdr.e_machine = EM_X86_64;
	exe.ehdr.e_version = EV_CURRENT;
	exe.ehdr.e_flags   = 0;
	exe.ehdr.e_ehsize  = sizeof(Elf64_Ehdr);
	//数据位置指针
	unsigned int curOff= sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * segNames.size();
	//空段表项
	exe.addShdr("",0,0,0,0,0,0,0,0,0);
	//".shstrtab".length()+".symtab".length()+".strtab".length()+3;//段表字符串表大小
	int shstrtabSize = 26;
	for(auto seg : segNames)
	{
		shstrtabSize += seg.length() + 1;//考虑结束符'\0'
		//生成程序头表
		Elf64_Word flags  = PF_W|PF_R;//读写
		Elf64_Word filesz = segLists[seg]->size;//占用磁盘大小
		if(seg == ".text") flags  = PF_X|PF_R;//.text段可读可执行
		if(seg == ".bss")  filesz = 0;//.bss段不占磁盘空间

		//添加程序头表项
		exe.addPhdr(PT_LOAD,
			segLists[seg]->offset,
			segLists[seg]->baseAddr,
			filesz,
			segLists[seg]->size,
			flags,
			MEM_ALIGN
		);
		//计算有效数据段的大小和偏移,最后一个决定
		//修正当前偏移，循环结束后保留的是.bss的基址
		curOff = segLists[seg]->offset;

		//生成段表项
		Elf64_Word sh_type  = SHT_PROGBITS;
		Elf64_Word sh_flags = SHF_ALLOC|SHF_WRITE;
		Elf64_Word sh_align = 4;//4B
		if(seg == ".bss")    sh_type = SHT_NOBITS;
		if(seg == ".text"){
			sh_flags = SHF_ALLOC|SHF_EXECINSTR;
			sh_align = 16;//16B
		}
		//添加一个段表项，暂时按照4字节对齐
		exe.addShdr(seg,sh_type,sh_flags,segLists[seg]->baseAddr,segLists[seg]->offset,
			segLists[seg]->size,SHN_UNDEF,0,sh_align,0);
	}
	exe.ehdr.e_phoff     = sizeof(Elf64_Ehdr);
	exe.ehdr.e_phentsize = sizeof(Elf64_Phdr);
	exe.ehdr.e_phnum     = segNames.size();
	//填充shstrtab数据
	exe.shstrtab         = new char[shstrtabSize];
	char*str             = exe.shstrtab;
	exe.shstrtabSize     = shstrtabSize;

	int index            = 0;
	//段表串名与索引映射
	map<string,int> shstrIndex;
	shstrIndex[".shstrtab"] = index;strcpy(str + index,".shstrtab");index += 10;
	shstrIndex[".symtab"]   = index;strcpy(str + index,".symtab");index += 8;
	shstrIndex[".strtab"]   = index;strcpy(str + index,".strtab");index += 8;
	shstrIndex[""]			= index-1;

	for(auto i : segNames){
		shstrIndex[i] = index;
		strcpy(str + index,i.c_str());
		index += i.length() + 1;
	}
	for(int i=0;i<shstrtabSize;++i)printf("%c",str[i]);printf("\n");
	for(int i=0;i<shstrtabSize;++i)printf("%d|",str[i]);printf("\n");
	//生成.shstrtab
	printf(".shstrtab:\tbase=%08x\tsize=%08x\n",curOff,shstrtabSize);
	exe.addShdr(".shstrtab",SHT_STRTAB,0,0,curOff,shstrtabSize,SHN_UNDEF,0,1,0);//.shstrtab
	exe.ehdr.e_shstrndx  = exe.getSegIndex(".shstrtab");//1+segNames.size();//空表项+所有段数
	//段表偏移
	curOff  += shstrtabSize;
	exe.ehdr.e_shoff     = curOff;
	exe.ehdr.e_shentsize = sizeof(Elf64_Shdr);
	exe.ehdr.e_shnum     = 4 + segNames.size();//段表数
	//printf("Sht(40N):\tbase=%08x\tsize=%08x\n",curOff,40*exe.ehdr.e_shnum);
	//生成符号表项
	curOff  += sizeof(Elf64_Shdr) * (4 + segNames.size());//符号表偏移
	//printf(".symtab:\tbase=%08x\tsize=%08x\n",curOff,(1+symDef.size())*16);
	//符号表位置=（空表项+所有段数+段表字符串表项+符号表项+字符串表项）*40
	//.symtab,sh_link 代表.strtab索引，默认在.symtab之后,sh_info不能确定
	exe.addShdr(".symtab",SHT_SYMTAB,0,0,curOff,(1 + symDef.size()) * sizeof(Elf64_Sym),0,0,1, sizeof(Elf64_Sym));
	exe.shdrTab[".symtab"]->sh_link = exe.getSegIndex(".symtab") + 1;//。strtab默认在.symtab之后
	int strtabSize = 0;//字符串表大小
	exe.addSym("",NULL);//空符号表项

	//遍历所有符号
	for(auto def : symDef){
		string name    = def->name;
		strtabSize    += name.length() + 1;
		Elf64_Sym *sym = def->prov->symTab[name];
		sym->st_shndx  = exe.getSegIndex(def->prov->shdrNames[sym->st_shndx]);//重定位后可以修改了
		exe.addSym(name,sym);
	}
	//记录程序入口
	exe.ehdr.e_entry   = exe.symTab[START]->st_value;//程序入口地址
	curOff  += (1 + symDef.size())* sizeof(Elf64_Sym);//.strtab偏移
	exe.addShdr(".strtab",SHT_STRTAB,0,0,curOff,strtabSize,SHN_UNDEF,0,1,0);//.strtab
	//printf(".strtab:\tbase=%08x\tsize=%08x\n",curOff,strtabSize);
	//填充strtab数据
	exe.strtab         = new char[strtabSize];
	str 			   = exe.strtab;
	exe.strtabSize     = strtabSize;
	index 			   = 0;
	//串表与索引映射
	map<string,int> strIndex;
	strIndex[""]=strtabSize-1;
	for(auto sym : symDef){

		strIndex[sym->name] = index;
		strcpy(str+index,sym->name.c_str());
		index  += sym->name.length()+1;
	}
	//for(int i=0;i<strtabSize;++i)printf("%c",str[i]);printf("\n");
	//for(int i=0;i<strtabSize;++i)printf("%d|",str[i]);printf("\n");
	//更新符号表name
	for(auto sym : exe.symTab){
		sym.second->st_name = strIndex[sym.first];
		//printf("%s\t%08x\t%s\n",i->first.c_str(),strIndex[i->first],str+strIndex[i->first]);
	}
	//更新段表name
	for(auto sh : exe.shdrTab){
		sh.second->sh_name = shstrIndex[sh.first];
	}
}

/**
 *
 * @param dir
 */
void Linker::writeExe(string out)
{
    cout << "start generation..." << endl;
    int offset = 0;
    //写入header + 程序头表
    offset = exe.writeHeader(out);
    assert(offset == (sizeof(Elf64_Ehdr) + exe.phdrTab.size() * sizeof(Elf64_Phdr)));
	//输出重要段数据
	FILE*fp = fopen(out.c_str(),"a+");
	char pad[1] = {0};

	//.text .data .bss
	for(auto seg : segNames)
	{
		SegList *sl = segLists[seg];
		int padnum  = sl->offset-sl->begin;
		offset += padnum;
		cout << "segment:" << seg << " offset:" << offset << " pad:" << padnum << endl;
		while(padnum--)
			fwrite(pad,1,1,fp);//填充
		//输出数据
		if(seg != ".bss")
		{
			Block *old  = NULL;
			char instPad[1] = {(char)0x90};
			for(auto b : sl->blocks){
				//填充小段内的空隙
				if(old != NULL){
					padnum = b->offset - (old->offset + old->size);
					offset += padnum;
					while(padnum--)
						fwrite(instPad,1,1,fp);//填充
				}
				old = b;
				offset += b->size;
				fwrite(b->data,b->size,1,fp);
			}
		}		
	}
	fclose(fp);
	//写入段表，段表符串表，符号表，符号字符串表
	//检查段表字符串表偏移
	assert(offset == exe.shdrTab[".shstrtab"]->sh_offset);
	offset += exe.shstrtabSize;
	assert(offset == exe.ehdr.e_shoff);
	exe.writeSecSym(out);
}

bool Linker::link(string out)
{
	//搜集段/符号信息
	collectInfo();
	//符号引用验证
	if(!symValid())
		return false;
	//分配地址空间
	allocAddr();
	//符号地址解析
	symParser();
	//重定位
	relocate();
	//组装文件exe
	buildExe();
	//输出elf可执行文件
	writeExe(out);
	return true;
}

Linker::~Linker()
{
	//清空合并段序列
	for(auto i : segLists)
		delete i.second;
	segLists.clear();

	//清空符号引用序列
	for(auto i : symLinks)
		delete i;
	symLinks.clear();

	//清空符号定义序列
	for(auto i : symDef)
		delete i;
	symDef.clear();

	//清空目标文件
	for(auto i : elfs)
		delete i;
	elfs.clear();
}
