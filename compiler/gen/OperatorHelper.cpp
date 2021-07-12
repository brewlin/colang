/*
 * @author brewlin
 * @date   2021/7/12
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"
#include "OperatorHelper.h"
using namespace std;


Expression* OperatorHelper::gen()
{
	Expression* left  = genLeft();
	Expression* right = genRight(); 

	StructMemberExpr* smember = nullptr;
	Member* 		  m   	  = nullptr;
	VarExpr*		  svar    = nullptr;

    if(typeid(*left) == typeid(VarExpr))					svar = dynamic_cast<VarExpr*>(left);
	else if(typeid(*left) == typeid(StructMemberExpr))	smember = dynamic_cast<StructMemberExpr*>(left);
	else												parse_err("OperatorHelper: unknow assign left expression");

	// 右值的大小,默认8字节
	int  size = 8;
	bool isunsigned = false;
	//左边是成员变量
	if(smember){
		m = smember->getMember();
		isunsigned = m->isunsigned;
		size = m->size;
		if(m->pointer) size = 8;
	}
	//如果左边值是成员变量赋值，则需要将右值转换一下
	if(smember && m->bitfield){
		AsmGen::writeln("	mov %%rax, %%rdi");
		AsmGen::writeln("   and $%ld, %%rdi", (1L << m->bitwidth) - 1);
		AsmGen::writeln("	shl $%d, %%rdi", m->bitoffset);
		AsmGen::writeln("   mov (%%rsp), %%rax");
		AsmGen::Load(m->size,m->isunsigned);
		long mask = ((1L << m->bitwidth) - 1) << m->bitoffset;
		AsmGen::writeln("  mov $%ld, %%r9", ~mask);
		AsmGen::writeln("  and %%r9, %%rax");
		AsmGen::writeln("  or %%rdi, %%rax");
	}
	string ax,di,dx;
	//如果left 足够大就用8字节的寄存器
	if (size == 8) {
		ax = "%rax";
		di = "%rdi";
		dx = "%rdx";
	} else {
		ax = "%eax";
		di = "%edi";
		dx = "%edx";
	}
	switch(opt)
	{
		case TK_ASSIGN:{ 	// lhs = rhs
			AsmGen::Store(size);
			return nullptr;
		}
		case TK_PLUS_AGN:{  // lhs += rhs
			AsmGen::writeln("	mov %%rax,%%rdi");
			AsmGen::Pop("%rax");
			AsmGen::Push();
			AsmGen::Load(size,isunsigned);
			AsmGen::writeln("	add %s, %s", di.c_str(), ax.c_str());
			AsmGen::Store(size);
			return nullptr;
		}
	}
	return nullptr;
}
/**
 * 处理  p.a = (expression)
 * 1. 右值需要 根据左值进行强制转换
 */
Expression* OperatorHelper::genLeft()
{
	//如果是var<struct>.member
	if(typeid(*lhs) == typeid(StructMemberExpr)){
		StructMemberExpr* smember = dynamic_cast<StructMemberExpr*>(lhs);
		//左边求值
		smember->asmgen(ctx);
		AsmGen::Push();
		Member* m = smember->getMember();

		return smember;
	//如果是var<struct>
	}else if (typeid(*lhs) == typeid(VarExpr)){
		if(!var->structtype)
        	parse_err("genLeft: lhs not structExpr %s \n",lhs->toString().c_str());
		//左边求值
		AsmGen::GenAddr(var);
		AsmGen::Push();
		return var;
	}
	parse_err("genLeft: unknow left type");
}
Expression* OperatorHelper::genRight()
{
	//如果右边是字面值 可以直接 直接优化直接赋值
	// TODO: only for int
	if(typeid(*rhs) == typeid(IntExpr)){
		IntExpr* ie = dynamic_cast<IntExpr*>(rhs);	
		AsmGen::writeln("	mov $%d,%%rax",ie->literal);
		return ie;
	}else{
	//其他的统一求值即可
		return rhs->asmgen(ctx);
	}
}