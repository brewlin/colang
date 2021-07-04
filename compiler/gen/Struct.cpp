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

/**
 * string  varname;
 * string  member;
 * VarExpr* var;
 * @param ctx
 * @return
 */
void  StructMemberExpr::asmgen(std::deque<Context*> ctx)
{
	string filename = AsmGen::parser->filename;
	//找到对应到结构体
	string package = var->package;
	Struct* s = nullptr;
	Member* m = nullptr;
	//处理映射
	package = AsmGen::parser->import[package];
	if(Package::packages.count(package) < 1){
        parse_err("struct.member: struct package:%s not exist  file:%s\n",package.c_str(),filename.c_str());
	}
	if((s = Package::packages[package]->getStruct(var->structname)) && s == nullptr){
        parse_err("struct.member: struct :%s not exist  file:%s\n",var->structname.c_str(),filename.c_str());
	}
	//判断成员变量
	if((m = s->getMember(this->member)) && m == nullptr){
        parse_err("struct.member: struct member:%s not exist  file:%s\n",this->member.c_str(),filename.c_str());
	}
	//获取到首地址
	AsmGen::GenAddr(this->var);
	//指针类型
	AsmGen::Load();
	//加载偏移量
	AsmGen::writeln("  add $%d, %%rax", m->offset);
}

