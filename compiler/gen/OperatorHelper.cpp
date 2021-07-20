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
#include <algorithm>
using namespace std;

OperatorHelper::OperatorHelper(deque<Context*> ctx,Expression* lhs,Expression* rhs,Token opt)
	:ctx(ctx),lhs(lhs),rhs(rhs),
	opt(opt),ltypesize(8),lvarsize(1),ltoken(KW_I8),
	lisunsigned(false),lispointer(false),needassign(false)
{
	lmember = nullptr;
	ax = "%rax";
	di = "%rdi";
	dx = "%rdx";
	if(opt >= TK_ASSIGN && opt <= TK_BITOR_AGN)
		needassign = true;
}

/**
 * 检查是否需要直接运算
 */
bool OperatorHelper::memoryOp(Expression* lhs,Expression* rhs)
{
	//1. (struct.member) op *
	//2. * op (struct.member)
	//3. (struct) op *
	//4. * op (struct)
	//5. (delref) op *
	//6. * op (delref)
	return true;

}
Expression* OperatorHelper::gen()
{
	//1 += 这种 需要存储 lhs, (lhs)
	//2 (lh + rhs) 只需要存储 （lhs)
	//3 lhs = rhs  只需要存储 lhs
	if(needassign){
		genLeft();
		AsmGen::Push(); //save left
		//不是单纯但赋值 都需要读取右边值顺便读取一下左边的值 给运算过程使用
		if(opt != TK_ASSIGN){
			if(lmember) AsmGen::Load(lmember);
			else        AsmGen::Load(ltypesize,lisunsigned);
			AsmGen::Push();
		}
	}else{
		genRight(true,lhs);
		AsmGen::Push();
	}

	genRight(false,rhs); 

	//如果left 足够大就用8字节的寄存器
	if (ltypesize != 8) {
		ax = "%eax";
		di = "%edi";
		dx = "%edx";
	}
	if(needassign) return assign();
	else	 	   return binary();
}
Expression* OperatorHelper::assign()
{
	//先去运算
	Expression* ret = binary();

	//如果不是需要赋值的类型直接返回即可
	if(!needassign) return ret;
	//读取运算的时候不需要，只有赋值如果左边值是成员变量赋值，则需要将右值转换一下
	if(lmember && lmember->bitfield)
	{
		AsmGen::writeln("	mov %%rax, %%rdi");
		AsmGen::writeln("   and $%ld, %%rdi", (1L << lmember->bitwidth) - 1);
		AsmGen::writeln("	shl $%d, %%rdi", lmember->bitoffset);
		AsmGen::writeln("   mov (%%rsp), %%rax");
		AsmGen::Load(lmember->size,lmember->isunsigned);
		long mask = ((1L << lmember->bitwidth) - 1) << lmember->bitoffset;
		AsmGen::writeln("  mov $%ld, %%r9", ~mask);
		AsmGen::writeln("  and %%r9, %%rax");
		AsmGen::writeln("  or %%rdi, %%rax");
	}
	//根据左值类型进行存储
	AsmGen::Store(ltypesize);
}
Expression* OperatorHelper::binary()
{
	Token base = max(rtoken,ltoken);
	assert(base >= KW_I8 && base <= KW_U64);

	//成员变量  + expression
	switch(opt){
		case TK_PLUS_AGN:
		case TK_PLUS:{
			//如果左右两边有
			//将右边 cast到左边到类型
			AsmGen::Cast(rtoken,base);
			AsmGen::writeln("	mov %%rax,%%rdi");

			AsmGen::Pop("%rax");
			AsmGen::Cast(ltoken,base);
			AsmGen::writeln("	add %s, %s", di.c_str(), ax.c_str());
			break;
		}
		case TK_MINUS_AGN:
		case TK_MINUS:{
			AsmGen::Cast(rtoken,base);
			AsmGen::writeln("	mov %%rax,%%rdi");

			AsmGen::Pop("%rax");
			AsmGen::Cast(ltoken,base);
			AsmGen::writeln("	sub %s,%s,",di.c_str(),ax.c_str());
			break;
		}
		default:{
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
		//初始化提取一些类型
		Member* m = smember->getMember();
		lmember = m;
		initcond(true,m->pointer ? 8 : m->size,m->size,m->type,m->isunsigned,m->pointer);
		return smember;
	//如果是var<struct>
	}else if (typeid(*lhs) == typeid(VarExpr)){
		if(!var->structtype)
        	parse_err("genLeft: lhs not structExpr %s \n",lhs->toString().c_str());
		//这个var asignExpr传过来的
		initcond(true,var->pointer ? 8 : var->size,var->size,var->type,var->isunsigned,var->pointer);
		//左边求值
		AsmGen::GenAddr(var);
		return var;
	}
	parse_err("genLeft: unknow left type");
}
Expression* OperatorHelper::genRight(bool isleft,Expression* expr)
{
	//如果右边是字面值 可以直接 直接优化直接赋值
	// TODO: only for int
	if(typeid(*expr) == typeid(IntExpr)){
		IntExpr* ie = dynamic_cast<IntExpr*>(expr);	
		// AsmGen::writeln("	mov $%ld,%%rax",ie->literal);
		AsmGen::writeln("	mov $%s,%%rax",ie->literal.c_str());
		initcond(isleft,8,8,KW_I64,false,false);
		return ie;
	}
	//其他的统一求值即可
	Expression* ret = expr->asmgen(ctx);
	if(typeid(*expr) == typeid(BinaryExpr)){
		Token t = expr->getType(ctx);
		int size = typesize[t];
		bool iu = false;
		if(t == KW_U8 || t == KW_U16 || t == KW_U32 || t == KW_U64)
			iu = true;
		initcond(isleft,size,size,t,iu,false);
	}else if(typeid(*expr) == typeid(AddrExpr)){
		initcond(isleft,8,8,KW_U64,true,true);
	}else if(typeid(*ret) == typeid(NewExpr)){
		//申请内存
		initcond(isleft,8,8,KW_U64,true,false);
	}else if(typeid(*ret) == typeid(VarExpr))
	{
		auto v = dynamic_cast<VarExpr*>(ret);
		if(!v->structtype)
			initcond(isleft,8,8,KW_I64,false,false);
		else
			initcond(isleft,v->pointer ? 8 : v->size,v->size,v->type,v->isunsigned,v->pointer);
	}else if(typeid(*ret) == typeid(StructMemberExpr))
	{
		auto m = dynamic_cast<StructMemberExpr*>(ret);
		auto v = m->getMember(); 
		initcond(isleft,v->pointer ? 8 : v->size,v->size,v->type,v->isunsigned,v->pointer);
		//目前所有的struct.member都需要自己load 值,除非遇到&地址引用
		if(typeid(*expr) != typeid(AddrExpr)){
			AsmGen::Load(v);
		}
	}else{
		parse_err("not allowed expression in memory operator:%s\n",ret->toString().c_str());
	}
	return ret;
}
/**
 * 初始化一些条件，给operator用
 */
Expression* OperatorHelper::initcond(bool left,int typesize,int varsize,Token type,bool isunsigned,bool ispointer)
{
	if(left){
		ltypesize = typesize;
		lvarsize  = varsize;
		ltoken    = type;
		lisunsigned = isunsigned;
		lispointer  = ispointer;
		if(ispointer) ltoken = KW_U64;
		return nullptr;
	}
	rtypesize = typesize;
	rvarsize  = varsize;
	rtoken    = type;
	risunsigned = isunsigned;
	rispointer  = ispointer;
	if(ispointer) rtoken = KW_U64;

}