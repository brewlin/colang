/**
 *@ClassName Interpreter
 *@Author brewlin
 *@Date 2020/9/3 0003 下午 3:38
 *@Version 1.0
 **/
#include "Interpreter.h"
#include "Parser.h"
#include "Log.h"


Interpreter::Interpreter(const std::string &filename)
{
	rt = new Runtime;
	p  = new Parser(filename,rt);
}
Interpreter::~Interpreter() {
    delete  p;
    delete rt;
}
/**
 * 这个地方表示 该表达式没有被实现
 * 那么父类就会抛出一个异常
 * @param rt
 * @param ctx
 * @return
 */
Value Expression::eval(Runtime *rt, std::deque<Context *> ctx)
{
    panic(
        "RuntimeError: can not evaluate abstract expression at line %d, column "
        "%d\n",
        line, column);
}
/**
 * 说明 语句没有被实现，那么父类方法被调用到时就抛出异常
 * @param rt
 * @param ctx
 * @return
 */
ExecResult Statement::interpret(Runtime *rt, std::deque<Context *> ctx)
{
    panic(
        "RuntimeError: can not interpret abstract statement at line %d, column "
        "%d\n",
        line, column);
}
/**
 * 程序启动api
 */
void Interpreter::execute()
{
    Debug("start interpreter");
    //词法解析 语法解析
    this->p->parse();
    //全局变量环境保存在runtime的全局变量表中
    //这里表示开辟新的上下文环境，因为每个函数的变量会和全局隔离
    /**
     * a = 1
     * func test(){
     * # 这里的a 是临时变量 非上面的全部变量
     * a = 2
     * }
     * 所以需要开辟新的Context来隔离资源
     */
    this->ctx.push_back(new Context);

    Debug("interpret statements");
    auto stmts = rt->getStatements();
    //顺序执行语句
    for(auto stmt : stmts){
//        std::cout << stmt->toString() << "\n";
        //执行表达式语句
        stmt->interpret(rt,ctx);
    }
    Debug("end interpreter");
}
//创建上下文 准备执行函数
void Interpreter::enterContext(std::deque<Context *> ctx)
{
    auto* temp = new Context;
    ctx.push_back(temp);
}
//离开上下文
void Interpreter::leaveContext(std::deque<Context *> ctx)
{
    auto* tempContext = ctx.back();
    ctx.pop_back();
    delete tempContext;

}
/**
 * 执行用户自定义函数
 * @param rt
 * @param f
 * @param prevCtxChain
 * @param args
 * @return
 */
Value Interpreter::callFunction(Runtime *rt, Function *f, std::deque<Context *> prevCtxChain,
                                    std::vector<Expression *> args){

    //创建一个新的上下文链
    std::deque<Context*> funcCtxChain;
    //进入新的上下文
    Interpreter::enterContext(funcCtxChain);

    //获取最近的一个上下文，就上面那个
    auto* funcCtx = funcCtxChain.back();
    //这里对实参进行求值
    //在fucallExpr 中只有内置函数才会求值，自定义函数在这里求值
    for(int i = 0; i < f->params.size() ; i ++){
        //获取实参名
        std::string paramname = f->params[i];
        //从之前的上下文链中求实参的值
        //TODO: need figure out
        Value argvalue = args[i]->eval(rt,prevCtxChain);
        //将实参值放入新的上下文中 创建变量
        funcCtx->createVar(f->params[i],argvalue);
    }

    //保留返回结果
    ExecResult ret(ExecNormal);
    //遍历用户函数的语句并执行
    for(auto& stmt : f->block->stmts){
        ret = stmt->interpret(rt,funcCtxChain);
        if(ret.execType == ExecReturn)
            break;
    }
    //离开上下文
    //TODO: need figure out
    Interpreter::leaveContext(funcCtxChain);
    return ret.retValue;
}


/**
 * 赋值操作
 * @param opt
 * @param lhs
 * @param rhs
 * @return
 */
Value Interpreter::assignSwitch(Token opt, Value lhs, Value rhs)
{
    switch (opt){
        case TK_ASSIGN:
            return rhs;
        case TK_PLUS_AGN:
            return lhs + rhs;
        case TK_MINUS_AGN:
            return lhs - rhs;
        case TK_MUL_AGN:
            return lhs * rhs;
        case TK_DIV_AGN:
            return lhs / rhs;
        case TK_MOD_AGN:
            return lhs % rhs;
        default:
            panic("InteralError: unexpects branch reached\n");

    }
}
/**
 * 二元求值
 * @param lhs
 * @param opt
 * @param rhs
 * @param line
 * @param column
 * @return
 */
Value Interpreter::calcBinaryExpr(Value lhs, Token opt, Value rhs, int line, int column) {
    Value result{Null};

    switch (opt) {
        case TK_PLUS:
            result = (lhs + rhs);
            break;
        case TK_MINUS:
            result = (lhs - rhs);
            break;
        case TK_MUL:
            result = (lhs * rhs);
            break;
        case TK_DIV:
            result = (lhs / rhs);
            break;
        case TK_MOD:
            result = (lhs % rhs);
            break;
        case TK_LOGAND:
            result = (lhs && rhs);
            break;
        case TK_LOGOR:
            result = (lhs || rhs);
            break;
        case TK_EQ:
            result = (lhs == rhs);
            break;
        case TK_NE:
            result = (lhs != rhs);
            break;
        case TK_GT:
            result = (lhs > rhs);
            break;
        case TK_GE:
            result = (lhs >= rhs);
            break;
        case TK_LT:
            result = (lhs < rhs);
            break;
        case TK_LE:
            result = (lhs <= rhs);
            break;
        case TK_BITAND:
            result = (lhs & rhs);
            break;
        case TK_BITOR:
            result = (lhs | rhs);
            break;
        default:
            panic("Unknow binary expr:%d\n",opt);
            break;
    }

    return result;
}
/**
 * 一元表达式求值
 * @param lhs
 * @param opt
 * @param line
 * @param column
 * @return
 */
Value Interpreter::calcUnaryExpr(Value& lhs, Token opt, int line,
                                      int column) {
    switch (opt) {
        case TK_MINUS:
            switch (lhs.type) {
                case Int:
                    return Value(Int, -std::any_cast<int>(lhs.data));
                case Double:
                    return Value(Double,
                                      -std::any_cast<double>(lhs.data));
                default:
                    panic(
                        "TypeError: invalid operand type for operator "
                        "-(negative) at line %d, col %d\n",
                        line, column);
            }
            break;
        case TK_LOGNOT:
            //对所有变量!
            return Value(Bool,!lhs.isTrue());
        case TK_BITNOT:
            if (lhs.type == Int) {
                return Value(Int, ~std::any_cast<int>(lhs.data));
            } else {
                panic(
                    "TypeError: invalid operand type for operator "
                    "~(bit not) at line %d, col %d\n",
                    line, column);
            }
            break;
        default:
            panic(
                "TypeError: Unsupport invalid operand type for operator "
                "~(bit not) at line %d, col %d\n",
                line, column);

    }

    return lhs;
}
