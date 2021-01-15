#ifndef COLANG_LINKER_H
#define colang_LINKER_H

#include "ElfFile.h"
//STL模板库
#include <map>
#include <vector>
using namespace std;
using namespace __gnu_cxx;

//一个数据块
struct Block
{
	char *data;
	unsigned int offset;//块偏移
	unsigned int size;//块大小
	Block(char*d,unsigned int off,unsigned int s);
	~Block();
};
//将头类型的段合并为一个列表
struct SegList
{
	unsigned int baseAddr;//分配基地址
	unsigned int offset;//合并后的文件偏移
	unsigned int size;//合并后大小
	unsigned int begin;//对齐前开始位置偏移
	vector<ElfFile*>ownerList;//拥有该段的文件序列
	vector<Block*>blocks;//记录合并后的数据块序列

	void allocAddr(string name,unsigned int& base,unsigned int& off);//每种类型的段计算自己的段修正后位置
	void relocAddr(unsigned int relAddr,unsigned char type,unsigned int symAddr, int addend);//根据提供的重定位信息重定位地址
	~SegList();
};

//符号引用对象，每一次外部符号引用都会产生
struct SymLink
{
	string name;//引用的符号名
	ElfFile *recv;//引用符号文件
	ElfFile *prov;//提供符号的文件，符号未定义时必然是NULL
};

//链接器类，完成目标文件*.o的链接
#define START "mini_crt_entry"//程序入口位置
#define BASE_ADDR 0x08040000//默认加载地址
//#define BASE_ADDR 0x4000e8//默认加载地址
#define MEM_ALIGN 4096//默认内存对齐大小4KB
#define DISC_ALIGN 8//默认磁盘对齐大小4B

class Linker
{
	vector<string> 		 segNames;//链接关心的段
	ElfFile  			 exe;//链接后的输出文件
	ElfFile* 			 startOwner;//拥有全局符号START/_start的文件
	int 				 bssaddr = 0;
public:
	static int 			 bytes;
	vector<ElfFile*>     elfs;//所有目标文件对象
	map<string,SegList*> segLists;//所有合并段表序列
	vector<SymLink*>     symLinks;//所有符号引用信息，符号解析前存储未定义的符号prov字段为NULL
	vector<SymLink*>     symDef;//所有符号定义信息recv字段NULL时标示该符号没有被任何文件引用，否则指向本身（同prov）
public:
	Linker();
	void addElf(string obj);//添加一个目标文件
	void collectInfo();//搜集段信息和符号关联信息
	bool symValid();//符号关联验证，分析符号间的关联（定义和引用），全局符号位置，出现非法符号逻辑返回false
	void allocAddr();//分配地址空间[重新计算虚拟地址空间，磁盘空间连续分布不重新计算]，其他的段全部删除
	void symParser();//符号解析，原地计算定义和未定义的符号虚拟地址
	void relocate();//符号重定位，根据所有目标文件的重定位项修正符号地址
	void buildExe();//组装可执行文件
	void writeExe(string out);//输出elf
	bool link(string out);//链接
	~Linker();
};

#endif
