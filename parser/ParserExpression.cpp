/**
 *@ClassName ParserExpression
 *@Author brewlin
 *@Date 2020/9/27 0027 上午 11:44
 *@Version 1.0
 **/
#include "Parser.h"
#include "Log.h"
/**
 * 解析条件表达式
 * @return
 */
Expression* Parser::parseExpression(short oldPrecedence)
{
    //解析一元表达式
    auto* p = parseUnaryExpr();

    //解析赋值 = 号
    if (anyone(getCurrentToken(), TK_ASSIGN, TK_PLUS_AGN, TK_MINUS_AGN,
               TK_MUL_AGN, TK_DIV_AGN, TK_MOD_AGN)) {
        // 确保赋值左边是一个变量或者数组索引（arr[x]=5这种)
        if (typeid(*p) != typeid(IdentExpr) &&
            typeid(*p) != typeid(IndexExpr) &&
            typeid(*p) != typeid(MemberExpr)) {
            panic("SyntaxError: can not assign to %s\n", typeid(*p).name());
        }
        // 创建赋值表达式
        auto* assignExpr = new AssignExpr(line, column);
        // 获取赋值符号，因为赋值符号不止=，还有+=，%=这种复合赋值
        assignExpr->opt = getCurrentToken();
        // 左值
        assignExpr->lhs = p;
        // 去掉赋值符号
        currentToken = next();
        // 解析右值
        assignExpr->rhs = parseExpression();
        return assignExpr;
    }

    //解析二元表达式
    while (anyone(getCurrentToken(), TK_BITOR, TK_BITAND, TK_BITNOT, TK_LOGOR,
                  TK_LOGAND, TK_LOGNOT, TK_EQ, TK_NE, TK_GT, TK_GE, TK_LT,
                  TK_LE, TK_PLUS, TK_MINUS, TK_MOD, TK_MUL, TK_DIV)){
        // 获取当前运算符优先级，和前一个比较
        short currentPrecedence = Parser::precedence(getCurrentToken());
        if (oldPrecedence > currentPrecedence)
            // 如果前一个大则停止解析，返回前面的作为单独的表达式
            return p;
        // 创建二元表达式
        auto tmp = new BinaryExpr(line, column);
        // 左侧等于刚刚解析的p
        tmp->lhs = p;
        // 去掉运算符
        tmp->opt = getCurrentToken();
        currentToken = next();
        // 右侧是一个也是一个表达式，所以parseExpression
        tmp->rhs = parseExpression(currentPrecedence + 1);
        // 关键来了，这里把刚刚创建的tmp赋值给之前的p，从意义上说相当于把当前这整个表达式作为一元表达式
        // 如`3+2-5`，解析`3+2`之后把它整体作为二元表达式，然后第二个二元表达式就是左操作数是3+2,右操作数是5,符号是-；
        // 从程序结构上来说，相当于向左偏的二叉树。
        p = tmp;
    }
    return p;
}

/**
 * 解析一元表达式
 * @return
 */
Expression* Parser::parseUnaryExpr()
{
    //如果是一元运算符
    if(anyone(getCurrentToken(),TK_MINUS,TK_LOGNOT,TK_BITNOT)){

        auto val = new BinaryExpr(line,column);
        val->opt = getCurrentToken();
        //解析下一个token
        currentToken = next();
        //继续递归解析token
        val->lhs = parseUnaryExpr();
        //右子树默认为空
        //val->rhs = null;
        //返回后可以挂在一颗左子树上
        return val;
        //如果是字面值，标识符，等，就调用公共表达式解析
    }else if(anyone(getCurrentToken(),LIT_DOUBLE,LIT_INT,LIT_CHAR,LIT_STR,TK_IDENT,TK_LPAREN,TK_LBRACKET,
                    KW_TRUE,KW_FALSE,KW_NULL,KW_NEW,TK_DOT)){
        return parsePrimaryExpr();
    }
    Debug("parseUnaryExpr: not found token:%d-%s",getCurrentToken(),getCurrentLexeme().c_str());
    return nullptr;
}
/**
 * 解析公共标识符
 * @return
 */
Expression* Parser::parsePrimaryExpr()
{
    if(getCurrentToken() == TK_IDENT){
        auto ident = getCurrentLexeme();
        //去掉标识符
        currentToken = next();
        switch (getCurrentToken()){
            //说明可能是函数调用 func()  ident = func
            case TK_LPAREN:{
                currentToken = next();
                auto* val = new FunCallExpr(line,column);
                val->funcname = ident;

                //循环解析实参 func(1,2,3); while( c != ')');
                while(getCurrentToken() != TK_RPAREN){
                    val->args.push_back(parseExpression());
                    //ignore ','
                    if(getCurrentToken() == TK_COMMA)
                        currentToken = next();
                }
                //去掉 )
                assert(getCurrentToken() == TK_RPAREN);
                currentToken = next();
                return val;
            }
                //解析 var[i] 索引表达式
            case TK_LBRACKET:{
                //去掉[
                currentToken = next();
                auto* val = new IndexExpr(line,column);
                val->identname = ident;
                //解析索引
                val->index = parseExpression();
                assert(val->index != nullptr);
                assert(getCurrentToken() == TK_RBRACKET);
                //去掉]
                currentToken = next();
                return val;
            }
            default:
                return new IdentExpr(ident,line,column);
        }
    }else if(getCurrentToken() == TK_DOT)
    {
        Debug("got token dot ");
        auto* val = new MemberExpr(line,column);
        val->varname = getCurrentLexeme();
        //next
        currentToken = next();
        //must ident
        assert(getCurrentToken() == TK_IDENT);
        val->membername = getCurrentLexeme();
        //check ()
        currentToken = next();

        //可能是成员函数调用
        if(getCurrentToken() == TK_LPAREN){

            auto* mce = new MemberCallExpr(line,column);
            mce->varname    = val->varname;
            mce->membername = val->membername;
            currentToken = next();

            //循环解析实参 func(1,2,3); while( c != ')');
            while(getCurrentToken() != TK_RPAREN){
                mce->args.push_back(parseExpression());
                //ignore ','
                if(getCurrentToken() == TK_COMMA)
                    currentToken = next();
            }
            //去掉 )
            assert(getCurrentToken() == TK_RPAREN);
            currentToken = next();
            return mce;
        }
        return val;
    }
    else if(getCurrentToken() == LIT_INT)
    {
        //将 int 转换为 int
        auto val = atoi(getCurrentLexeme().c_str());
        currentToken = next();
        auto* ret = new IntExpr(line,column);
        ret->literal = val;
        return ret;
    }else if(getCurrentToken() == LIT_DOUBLE)
    {
        //将字面值 转换为double
        auto val     = atof(getCurrentLexeme().c_str());
        currentToken = next();
        auto* ret    = new DoubleExpr(line,column);
        ret->literal = val;
        return ret;
    }else if(getCurrentToken() == LIT_STR){
        //将字符串 ... 保存
        auto val     = getCurrentLexeme();
        currentToken = next();
        auto* ret    = new StringExpr(line,column);
        //将静态字符作为全局定义
        rt->strs.push_back(ret);
        ret->literal = val;
        return ret;
    }else if(getCurrentToken() == LIT_CHAR)
    {
        //保存char
        auto val     = getCurrentLexeme();
        currentToken = next();
        auto* ret    = new CharExpr(line,column);
        ret->literal = val[0];
        return ret;
    }else if(getCurrentToken() == KW_TRUE || getCurrentToken() == KW_FALSE)
    {
        auto val     = (KW_TRUE == getCurrentToken());
        currentToken = next();
        auto* ret    = new BoolExpr(line,column);
        ret->literal = val;
        return ret;
    }else if(getCurrentToken() == KW_NULL)
    {
        currentToken = next();
        return new NullExpr(line,column);
    }else if(getCurrentToken() == TK_LPAREN)
    {
        currentToken = next();
        //解析 {} block 块内的表达式
        auto val     = parseExpression();
        assert(getCurrentToken() == TK_RPAREN);
        currentToken = next();
        return val;
    }else if(getCurrentToken() == TK_LBRACKET)
    {
        //解析数组 array
        currentToken = next();
        auto* ret = new ArrayExpr(line,column);
        if(getCurrentToken() != TK_RBRACKET){
            while(getCurrentToken() != TK_RBRACKET) {
                //将参数 push 到 node中
                ret->literal.push_back(parseExpression());
                //解析[1,2,3] 中的 ,
                if(getCurrentToken() == TK_COMMA)
                    currentToken = next();
            }
            assert(getCurrentToken() == TK_RBRACKET);
            currentToken = next();
            return ret;
        }
        //表示是一个空数组
        currentToken = next();
        return ret;
    }else if(getCurrentToken() == KW_NEW)
    {
        //去掉 new
        currentToken = next();
        Debug("got new keywords:%s",getCurrentLexeme().c_str());
        //must ident
        assert(getCurrentToken() == TK_IDENT);
        auto* ret = new NewExpr(line,column);
        ret->type = getCurrentLexeme();
        //must TK_LPAREN TK_RPAREN
        currentToken = next();
        assert(getCurrentToken() == TK_LPAREN);
        currentToken = next();
        assert(getCurrentToken() == TK_RPAREN);
        currentToken = next();
        return ret;
    }
    return nullptr;
}