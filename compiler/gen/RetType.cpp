/*
 * @author brewlin
 * @date   2021/7/18
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"
#include "algorithm"
using namespace std;

Token  BoolExpr::getType(deque<Context*> ctx){
	return KW_U8;
}
Token  CharExpr::getType(deque<Context*> ctx){
	return KW_I8;
}
Token  NullExpr::getType(deque<Context*> ctx){
	return KW_U8;
}
Token  IntExpr::getType(deque<Context*> ctx){
	return KW_I64;
}
Token  DoubleExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport double\n");
}
Token  StringExpr::getType(deque<Context*> ctx){
	return KW_U64;
}
Token  ArrayExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport array\n");
}
Token  MapExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport map\n");
}
Token  KVExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport kv\n");
}
Token  ChainExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport chain\n");
}
Token  VarExpr::getType(deque<Context*> ctx){
	getVarType(ctx);
	if(ret->pointer) return KW_U64;

	return ret->type;
}
Token  ClosureExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport closure\n");
}
Token  StructMemberExpr::getType(deque<Context*> ctx){
	Member* m = getMember();
	if(m->pointer) return KW_U64;
	return m->type;
}
Token  AddrExpr::getType(deque<Context*> ctx){
	return KW_U64;
}
Token  DelRefExpr::getType(deque<Context*> ctx){
	if(typeid(*expr) == typeid(VarExpr)){
		VarExpr* var = dynamic_cast<VarExpr*>(expr);
		var = var->getVar(ctx);
		if(var->pointer) return KW_U64;
		return var->type;
	}else if(typeid(*expr) == typeid(StructMemberExpr)){
		StructMemberExpr* e = dynamic_cast<StructMemberExpr*>(expr);
		Member* m = e->getMember();
		if(m->pointer) return KW_U64;
		return m->type;
	}
	return expr->getType(ctx);
}
Token  IndexExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport IndexExpr\n");
}
Token  BinaryExpr::getType(deque<Context*> ctx){
	Token l = lhs->getType(ctx);
	Token r = rhs->getType(ctx);
	return max(l,r);
}
Token  FunCallExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport FunCall\n");
}
Token  AssignExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport Assign\n");
}
Token  NewClassExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport new class\n");
}
Token  BuiltinFuncExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport builtin\n");
}
Token  NewExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport new \n");
}
Token  MemberExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport Member\n");
}
Token  MemberCallExpr::getType(deque<Context*> ctx){
	parse_err("getType: unsupport MemberCall\n");
}