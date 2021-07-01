/**
 *@ClassName AsmGenFunc
 *@Author brewlin
 *@Date 2021/7/1 0012 下午 2:26
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "Log.h"
#include "Block.h"
#include "Parser.h"
#include "Value.h"

using namespace std;

/**
 * 结构体定义初始化
struct Member{
    string  name;
    Token   type;
    int     size;
    int     idx;
    int     align;
    int     offset;
    bool    bitfield;
    int     bitoffset;
    int     bitwidth;};
struct Struct {
    string  pkg;
    string  name;
    int     size;
    vector<Member*> member;
};
 */
void structDecl(Struct* s) 
{

  //分配偏移量
  int bits = 0;
  //这里就是开始按照对齐方式来计算没给字段偏移量
  for(auto mem : s->member){
    //位图为0则为特殊含义，仅仅是为了对齐
    if (mem->bitfield && mem->bitwidth == 0) 
    {
      bits = ALIGN_UP(bits, mem->size * 8);
    } else if (mem->bitfield) 
    {
      int sz = mem->size;
      if (bits / (sz * 8) != (bits + mem->bitwidth - 1) / (sz * 8))
        bits = ALIGN_UP(bits, sz * 8);

      mem->offset = ALIGN_DOWN(bits / 8, sz);
      mem->bitoffset = bits % (sz * 8);
      bits += mem->bitwidth;
    } else 
    {
        mem->offset = bits / 8;
        bits += mem->size * 8;
    }
  }
  //计算出struct的对齐后的总大小
  s->size = ALIGN_UP(bits, 8) / 8;
}
/**
 * gen struct
 */
void AsmGen::genStruct()
{
	for( auto v : Package::packages ){
		Package* pkg = v.second;
		for(auto v1 : pkg->structs ){
			Struct* s = v1.second;
			structDecl(s);
		}
	}
}
