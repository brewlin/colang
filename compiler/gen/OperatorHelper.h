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
	OperatorHelper(deque<Context*> ctx,Expression* lhs,Expression* rhs,Token opt)
	:ctx(ctx),lhs(lhs),rhs(rhs),opt(opt){};

	Expression* gen();
private:
	Expression* genLeft();
	Expression* genRight();
};


#endif //CO_LANG_OperatorHelper_H
