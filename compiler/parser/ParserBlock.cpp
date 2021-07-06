/**
 *@ClassName ParserToken
 *@Author brewlin
 *@Date 2020/11/19 0019 上午 11:05
 *@Version 1.0
 **/

#include "Parser.h"
#include "Block.h"
#include "Log.h"

/**
 * 一般解析函数内 {}里的语句列表
 * 逐行记录到 vector中
 * @return
 */
std::vector<Statement*> Parser::parseStatementList()
{
    std::vector<Statement*> node;
    Statement* p;
    while((p = parseStatement()) != nullptr)
    {
        node.push_back(p);
        //1. p = new(a,d,a) 类的创建 需要在后面手动构造一个 p.init()操作
        if (typeid(*p) == typeid(ExpressionStmt)) {
            auto pe = dynamic_cast<ExpressionStmt*>(p);
            if (typeid(*pe->expr) != typeid(AssignExpr)) continue;
            AssignExpr* expr = dynamic_cast<AssignExpr*>(pe->expr);
            //形如 p = new(a,b,c)
            if(typeid(*expr->rhs) == typeid(NewClassExpr) && typeid(*expr->lhs) == typeid(VarExpr)){
                NewClassExpr* ne = dynamic_cast<NewClassExpr*>(expr->rhs);
                VarExpr* obj = dynamic_cast<VarExpr*>(expr->lhs);
                //检查一下函数是否存在
                Package* pkg = this->pkg;
                if(ne->package != ""){
                    string package = this->import[ne->package];
                    pkg = Package::packages[package];
                }
                if(!pkg->checkClassFunc(ne->name,"init"))
                    continue;
                //构造一个函数调用
                auto* call = new FunCallExpr(expr->line,expr->column);
                call->package = obj->varname;
                call->funcname = "init";
                call->args = ne->args;
                call->is_pkgcall = true;
                auto params = call->args;
                call->args.clear();
                call->args.push_back(obj);
                call->args.insert(call->args.end(),params.begin(),params.end());

                auto nd = new ExpressionStmt(call,call->line,call->column);
                node.push_back(nd);
            }
            
        }

    }
    return node;
}
/**
 * 解析 {} 里的逻辑块
 * @return
 */
Block* Parser::parseBlock()
{
    Block* node{new Block};
    scanner->scan();
    node->stmts = parseStatementList();
    //判断是否 {} 闭合
    assert(scanner->curToken == TK_RBRACE);
    scanner->scan();
    return node;
}
/**
 * 解析函数调用的参数列表 func(arg1,arg2,arg3) => [arg1,arg2,arg3]
 * @return
 */
std::vector<std::string> Parser::parseParameterList()
{
    std::vector<std::string> node;
    scanner->scan();
    //是否解析到 ')'
    if(scanner->curToken == TK_RPAREN){
        scanner->scan();
        return std::move(node);
    }

    //解析所有括号内的参数 (..,..,..)
    while(scanner->curToken != TK_RPAREN){
        //所有的参数都必须是 ident 或者 逗号,
        if(scanner->curToken == TK_VAR)
        {
            //将参数单独保存一份 需要计算 栈偏移量
            if(currentFunc){
                VarExpr* var = new VarExpr(scanner->curLex,line,column);
                currentFunc->params_var[scanner->curLex] = var;
                currentFunc->params_order_var.push_back(var);

                scanner->scan();
                //判断有没有声明为memory结构
                if(scanner->curToken == TK_LT){
                    var->structtype = true;
                    scanner->scan();
                    assert(scanner->curToken == TK_VAR);
                    string sname = scanner->curLex;
                    var->structname = sname;
                    scanner->scan();
                    if(scanner->curToken == TK_DOT){
                        scanner->scan();
                        assert(scanner->curToken == TK_VAR);
                        var->package = sname;
                        var->structname = scanner->curLex;
                        scanner->scan();
                    }
                    assert(scanner->curToken == TK_GT);
                    scanner->scan();
                    //下面不允许在由... 格式了
                    continue;
                }
                //不是动态参数
                if(scanner->curToken == TK_COMMA) continue;
                if(scanner->curToken == TK_RPAREN) continue;

                //既不是, 又不是 . （arg...）| (arg,arg2) 那就是有问题
                if(scanner->curToken != TK_DOT){
                    parse_err("SynatxError: should be , or . but got :%s  line:%d column:%d\n",
                              scanner->curLex.c_str(),
                              line,column);
                }
                //去掉第二个点
                scanner->scan();
                if(scanner->curToken != TK_DOT){
                    parse_err("SynatxError: must be . but got :%s  line:%d column:%d\n",
                              scanner->curLex.c_str(),
                              line,column);
                }
                //去掉第三个点
                scanner->scan();
                if(scanner->curToken != TK_DOT){
                    parse_err("SynatxError: should be , or . but got :%s  line:%d column:%d\n",
                              scanner->curLex.c_str(),
                              line,column);
                }
                //走到这里说明一定是 tri-dot
                currentFunc->is_variadic = true;
                var->is_variadic = true;
            }
            node.push_back(scanner->curLex);
        }
        else{
            assert(scanner->curToken == TK_COMMA);
        }
        //继续下一个token读取
        scanner->scan();
    }
    //是否闭合
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    return move(node);
}