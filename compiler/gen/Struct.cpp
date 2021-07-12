/*
 * @author brewlin
 * @date   2021/6/9
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"


Member* StructMemberExpr::getMember()
{
	Struct* s = getStruct();
	if(s == nullptr) return nullptr;
	//判断成员变量
	Member* m = s->getMember(this->member);
	if(m == nullptr){
        parse_err("struct.member: struct member:%s not exist\n",this->member.c_str());
	}
	return m;
}
Struct* StructMemberExpr::getStruct()
{
	string package = var->package;
	Struct* s = nullptr;
	//处理映射
	package = AsmGen::parser->import[package];
	if(Package::packages.count(package) < 1){
        parse_err("struct.member: struct package:%s not exist \n",package.c_str());
	}
	s = Package::packages[package]->getStruct(var->structname);
	if(s == nullptr){
        parse_err("struct.member: struct :%s not exist  \n",var->structname.c_str());
	}
	return s;
}
/**
 * string  varname;
 * string  member;
 * VarExpr* var;
 * @param ctx
 * @return
 */
Expression*  StructMemberExpr::asmgen(std::deque<Context*> ctx)
{
	string filename = AsmGen::parser->filename;
	//判断成员变量
	Member* m = getMember();
	if(m == nullptr){
        parse_err("struct.member: struct member:%s not exist  file:%s\n",this->member.c_str(),filename.c_str());
	}
	//获取到首地址
	AsmGen::GenAddr(this->var);
	//指针类型
	AsmGen::Load();
	//加载偏移量
	AsmGen::writeln("	add $%d, %%rax", m->offset);
	//如果不是出现在赋值语句中 则自动读取内存
	if(!assign){
		//如果是指针需要加载8字节
		if(m->pointer)
			AsmGen::Load(8,true);
		else
			AsmGen::Load(m->size,m->isunsigned);
		if (m->bitfield) {
			AsmGen::writeln("	shl $%d, %%rax", 64 - m->bitwidth - m->bitoffset);
      		if (m->isunsigned)
        		AsmGen::writeln("	shr $%d, %%rax", 64 - m->bitwidth);
      		else
       		 	AsmGen::writeln("	sar $%d, %%rax", 64 - m->bitwidth);
    	}
	}
	this->ret = m;
	return this;
}

