/*
 * @author brewlin
 * @date   2021/7/12
 */
#ifndef CO_LANG_OPERATORHELPER_H
#define CO_LANG_OPERATORHELPER_H
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"
using namespace std;


class OperatorHelper
{
public:
	deque<Context*> ctx;
	Expression*		lhs;
	Expression*		rhs;
	Token 			opt;

	VarExpr* 		var;
public:
	//left
	int				ltypesize;
	int 			lvarsize;
	Token			ltoken;
	bool 			lisunsigned;
	Member*			lmember;
	bool 			lispointer;
	//right
	int 			rtypesize;
	int    			rvarsize;
	Token 			rtoken;
	bool 			risunsigned;
	bool 			rispointer;


	string 			ax,di,dx;
	bool			needassign;

public:
	OperatorHelper(deque<Context*> ctx,Expression* lhs,Expression* rhs,Token opt);
	static bool	memoryOp(Expression* lhs,Expression* rhs);
	Expression* gen();
	
	Expression* genLeft();
	Expression* genRight(bool isleft,Expression* expr);

	Expression* assign();
	Expression* binary();
	Expression* initcond(bool left,int typesize,int varsize,Token type,bool isunsigned,bool ispointer);
};


#endif //CO_LANG_OperatorHelper_H
