#include "Value.h"
#include <iostream>
using namespace std;
/**
 * find member
 */
Member* Struct::getMember(string name)
{
  for(auto i : member){
    if(i->name == name)
      return i;
  }
  return nullptr;
}
void Struct::compute()
{
  //分配偏移量
  int bits = 0;
  int align = 1;
  //这里就是开始按照对齐方式来计算没给字段偏移量
  for(auto mem : member){
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
        //不考虑压缩的话就根据当前类型进行对齐
        bits = ALIGN_UP(bits,mem->align * 8);
        mem->offset = bits / 8;
        //如果是指针的话默认是8字节
        if(mem->pointer)
          bits += 8 * 8;
        else
          bits += mem->size * 8;
    }
    if(align < mem->align)
      align = mem->align;
  }
  //计算出struct的对齐后的总大小
  this->size = ALIGN_UP(bits, align * 8) / 8;

}