/**
 *@ClassName Asmer
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:34
 *@Version 1.0
 **/
#include "Asmer.h"
#include "src/asm_ast/Sym.h"


/**
 * 	按照小端顺序（little endian）输出指定长度数据
	len=1：输出第4字节
	len=2:输出第3,4字节
	len=4:输出第1,2,3,4字节
 * @param value
 * @param len
 */
void Asmer::write(int value, int len)
{
    //计算地址
    asmer::Sym::curAddr += len;
    if(scanLop==2)
    {
        fwrite(&value,len,1,fout);
        inLen+=len;
    }
    //cout<<lb_record::curAddr<<"\t"<<inLen<<endl;
}