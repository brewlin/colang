/*
 * @author brewlin
 * @date   2021/6/5
 */

 #include "Function.h"
//闭包初始化
int Function::closureidx = 0;

VarExpr* Function::getVar(string name)
{
	if(name.empty()) return nullptr;

	//先从参数列表中去找
	for(auto var : params_var){
		if(var.first == name)
			return var.second;
	}
	//再从本地变量库去寻找
	for(auto var : locals){
		if(var.first == name)
			return var.second;
	}
	return nullptr;
}