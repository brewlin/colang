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
	switch(opt)
	{
		case TK_ASSIGN:{
			return assign();
		}
	}
	return nullptr;

}
Expression* OperatorHelper::assign(){
	//左边是var<type>
    if(typeid(*lhs) == typeid(VarExpr)){
		return structAssign();
	}else if(typeid(*lhs) == typeid(StructMemberExpr)){
		return structMemberAssign();
	}else{
		parse_err("OperatorHelper: unknow assign left expression");
	}
}
/**
 * 处理  p.a = (expression)
 * 1. 右值需要 根据左值进行强制转换
 */
Expression* OperatorHelper::structMemberAssign()
{
	StructMemberExpr* smember = dynamic_cast<StructMemberExpr*>(lhs);
	//左边求值
	smember->asmgen(ctx);
	AsmGen::Push();
	//如果右边是字面值 可以直接 直接优化直接赋值
	// TODO: only for int
	if(typeid(*rhs) == typeid(IntExpr)){
		IntExpr* ie = dynamic_cast<IntExpr*>(rhs);	
		AsmGen::writeln("	mov $%d,%%rax",ie->literal);
	}else{
	//其他的统一求值即可
		rhs->asmgen(ctx);
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
		AsmGen::Load(m->size,m->isunsigned);
      	long mask = ((1L << m->bitwidth) - 1) << m->bitoffset;
      	AsmGen::writeln("  mov $%ld, %%r9", ~mask);
      	AsmGen::writeln("  and %%r9, %%rax");
      	AsmGen::writeln("  or %%rdi, %%rax");
		//左值的类型
		AsmGen::Store(m->size);
      	AsmGen::writeln("  mov %%r8, %%rax");
      return nullptr;
    }
	//进行一次转换
	// AsmGen::Cast()
	//不是位操作直接存储即可
	//如果是指针则存储8为
	int size = m->size;
	if(m->pointer)
		size = 8;
    AsmGen::Store(size);
}
/**
 * 处理p<struct> = (expression|int,bool,pointer)等这种优化
 * 不需要再调用binary_operator来进行统一处理
 */
Expression* OperatorHelper::structAssign()
{
	if(!var->structtype)
        parse_err("assign: struct.member: lhs not structExpr %s \n",lhs->toString().c_str());

	//左边求值
	AsmGen::GenAddr(var);
	AsmGen::Push();
	//右边求值
	rhs->asmgen(ctx);
	//执行赋值
	AsmGen::Store();

}

