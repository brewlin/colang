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
 * 处理  p.a = (expression)
 */
void struct_member_assign(deque<Context*> ctx,AssignExpr* assign)
{

	//左边必须是 Struct.Member 表达式
    if(typeid(*assign->lhs) != typeid(StructMemberExpr)){
        parse_err("assign: struct.member: lhs not structMemberExpr %s \n",assign->lhs->toString().c_str());
	}
	StructMemberExpr* smember = dynamic_cast<StructMemberExpr*>(assign->lhs);
	//左边求值
	smember->asmgen(ctx);
	AsmGen::Push();
	//如果右边是字面值 可以直接 直接优化直接赋值
	// TODO: only for int
	if(typeid(*assign->rhs) == typeid(IntExpr)){
		IntExpr* ie = dynamic_cast<IntExpr*>(assign->rhs);	
		AsmGen::writeln("	mov $%d,%%rax",ie->literal);
	}else{
	//其他的统一求值即可
		assign->rhs->asmgen(ctx);
	}
	//查询左值的 member
	Member* m = smember->getMember();
	//bit位赋值
    if (m->bitfield) {
    	AsmGen::writeln("	mov %%rax, %%r8");
      	AsmGen::writeln("	mov %%rax, %%rdi");
      	AsmGen::writeln("   and $%ld, %%rdi", (1L << m->bitwidth) - 1);
      	AsmGen::writeln("	shl $%d, %%rdi", m->bitoffset);

      	AsmGen::writeln("   mov (%%rsp), %%rax");
		AsmGen::Load();
      	long mask = ((1L << m->bitwidth) - 1) << m->bitoffset;
      	AsmGen::writeln("  mov $%ld, %%r9", ~mask);
      	AsmGen::writeln("  and %%r9, %%rax");
      	AsmGen::writeln("  or %%rdi, %%rax");
		AsmGen::Store();
      	AsmGen::writeln("  mov %%r8, %%rax");
      return;
    }
	//不是位操作直接存储即可
    AsmGen::Store();
}
/**
 * 处理p<struct> = (expression|int,bool,pointer)等这种优化
 * 不需要再调用binary_operator来进行统一处理
 */
void struct_assign(deque<Context*> ctx,AssignExpr* assign)
{
	//左边必须是 var<Struct> 表达式
    if(typeid(*assign->lhs) != typeid(VarExpr))
        parse_err("assign: struct.member: lhs not structExpr %s \n",assign->lhs->toString().c_str());
	VarExpr* var = dynamic_cast<VarExpr*>(assign->lhs);
	if(!var->structtype)
        parse_err("assign: struct.member: lhs not structExpr %s \n",assign->lhs->toString().c_str());

	//左边求值
	AsmGen::GenAddr(var);
	AsmGen::Push();
	//右边求值
	assign->rhs->asmgen(ctx);
	//执行赋值
	AsmGen::Store();

}
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
void  StructMemberExpr::asmgen(std::deque<Context*> ctx)
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
		AsmGen::Load();
		if (m->bitfield) {
			AsmGen::writeln("	shl $%d, %%rax", 64 - m->bitwidth - m->bitoffset);
      		if (m->isunsigned)
        		AsmGen::writeln("	shr $%d, %%rax", 64 - m->bitwidth);
      		else
       		 	AsmGen::writeln("	sar $%d, %%rax", 64 - m->bitwidth);
    	}
	}
}

