/**
 *@ClassName ParserExpression
 *@Author brewlin
 *@Date 2020/9/27 0027 上午 11:44
 *@Version 1.0
 **/
#include "Parser.h"
#include "Log.h"
using namespace std;
/**
 * 解析条件表达式
 * @return
 */
Expression* Parser::parseExpression(short oldPrecedence)
{
    //解析一元表达式
    auto* p = parseUnaryExpr();
    //这里尝试优先去解析链式表达式
    if(anyone(scanner->curToken,TK_DOT,TK_LPAREN,TK_LBRACKET)){
        //构造一颗右偏的二叉树
        ChainExpr* chainExpr = new ChainExpr(line,column);
        chainExpr->lhs = p;
        chainExpr->rhs = parseExpression();
        return chainExpr;
    }
    //解析赋值 = 号
    if (anyone(scanner->curToken, TK_ASSIGN, TK_PLUS_AGN, TK_MINUS_AGN,
               TK_MUL_AGN, TK_DIV_AGN, TK_MOD_AGN,TK_BITAND_AGN,TK_BITOR_AGN,TK_SHIFTL_AGN,TK_SHIFTR_AGN)) {
        // 确保赋值左边是一个变量或者数组索引（arr[x]=5这种)
        if (typeid(*p) != typeid(VarExpr) &&
            typeid(*p) != typeid(IndexExpr) &&
            typeid(*p) != typeid(MemberExpr) &&
            typeid(*p) != typeid(StructMemberExpr)) {
            parse_err("SyntaxError: can not assign to %s\n", typeid(*p).name());
        }
        //结构体赋值
        if (typeid(*p) == typeid(StructMemberExpr) && currentFunc){
            StructMemberExpr* sm = dynamic_cast<StructMemberExpr*>(p);
            sm->assign = true;
        }
        if (typeid(*p) == typeid(VarExpr) && currentFunc){
            VarExpr* var = dynamic_cast<VarExpr*>(p);
            //先判断一下这个变量是否是属于参数变量，否则不需要在本地存储一份 不然在栈偏移量计算的时候会出错
            if(!currentFunc->params_var.count(var->varname)){
                currentFunc->locals[var->varname] = var;
            }
        }

        // 创建赋值表达式
        auto* assignExpr = new AssignExpr(line, column);
        // 获取赋值符号，因为赋值符号不止=，还有+=，%=这种复合赋值
        assignExpr->opt = scanner->curToken;
        // 左值
        assignExpr->lhs = p;
        // 去掉赋值符号
        scanner->scan();
        // 解析右值
        assignExpr->rhs = parseExpression();
        return assignExpr;
    }

    //解析二元表达式
    while (anyone(scanner->curToken,TK_SHIFTL,TK_SHIFTR,TK_BITOR, TK_BITAND, TK_BITNOT, TK_LOGOR,
                  TK_LOGAND, TK_LOGNOT, TK_EQ, TK_NE, TK_GT, TK_GE, TK_LT,
                  TK_LE, TK_PLUS, TK_MINUS, TK_MOD, TK_MUL, TK_DIV)){
        // 获取当前运算符优先级，和前一个比较
        short currentPrecedence = scanner->precedence(scanner->curToken);
        if (oldPrecedence > currentPrecedence)
            // 如果前一个大则停止解析，返回前面的作为单独的表达式
            return p;
        // 创建二元表达式
        auto tmp = new BinaryExpr(line, column);
        // 左侧等于刚刚解析的p
        tmp->lhs = p;
        // 去掉运算符
        tmp->opt = scanner->curToken;
        scanner->scan();
        // 右侧是一个也是一个表达式，所以parseExpression
        tmp->rhs = parseExpression(currentPrecedence + 1);
        // 关键来了，这里把刚刚创建的tmp赋值给之前的p，从意义上说相当于把当前这整个表达式作为一元表达式
        // 如`3+2-5`，解析`3+2`之后把它整体作为二元表达式，然后第二个二元表达式就是左操作数是3+2,右操作数是5,符号是-；
        // 从程序结构上来说，相当于向左偏的二叉树。
        p = tmp;
    }
    //fix: （a = 1 1 => a = 1 + 1）,(a = 1 -1 => a = 1 + -1) 自动补充+符号
    while (anyone(scanner->curToken,LIT_DOUBLE,LIT_INT,LIT_CHAR,LIT_STR)){
        //自动补充一个 + 号
        short currentPrecedence = scanner->precedence(TK_PLUS);
        if (oldPrecedence > currentPrecedence)
            // 如果前一个大则停止解析，返回前面的作为单独的表达式
            return p;
        // 创建二元表达式
        auto tmp = new BinaryExpr(line, column);
        // 左侧等于刚刚解析的p
        tmp->lhs = p;
        tmp->opt = TK_PLUS;
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
    if(anyone(scanner->curToken,TK_MINUS,TK_LOGNOT,TK_BITNOT)){

        auto val = new BinaryExpr(line,column);
        val->opt = scanner->curToken;
        //解析下一个token
        scanner->scan();
        //继续递归解析token
        val->lhs = parseUnaryExpr();
        //右子树默认为空
        //val->rhs = null;
        //返回后可以挂在一颗左子树上
        return val;
        //如果是字面值，标识符，等，就调用公共表达式解析
    }else if(anyone(scanner->curToken,LIT_DOUBLE,LIT_INT,LIT_CHAR,LIT_STR,TK_VAR,KW_FUNC,TK_LPAREN,TK_LBRACKET,
                    TK_LBRACE,TK_RBRACE,KW_TRUE,KW_FALSE,KW_NULL,KW_NEW,TK_DOT,TK_DELREF,TK_BITAND,BUILTIN_FUNC)){
        return parsePrimaryExpr();
    }

    Debug("parseUnaryExpr: not found token:%d-%s",scanner->curToken,scanner->curLex.c_str());
    return nullptr;
}
/**
 * 解析公共标识符
 * @return
 */
Expression* Parser::parsePrimaryExpr()
{
    Token tk   = scanner->curToken;
    Token prev = scanner->prevToken;
    //string(),int()
    if(tk == BUILTIN_FUNC){
        BuiltinFuncExpr* builtinfunc = new BuiltinFuncExpr(scanner->curLex,scanner->line,scanner->column);
        assert(scanner->scan() == TK_LPAREN);
        scanner->scan();
        builtinfunc->expr = parsePrimaryExpr();
        assert(scanner->curToken == TK_RPAREN);
        scanner->scan();
        return builtinfunc;
    }
    //& 取地址
    if(tk == TK_BITAND){
        auto addr = new AddrExpr(scanner->line,scanner->column);
        tk = scanner->scan();
        if(tk == TK_VAR){
            addr->varname = scanner->curLex;
        }
        tk = scanner->scan();
        if(tk == TK_DOT){
            addr->package = addr->varname;
            scanner->scan();
            assert(scanner->curToken == TK_VAR);
            addr->varname = scanner->curLex;
            scanner->scan();
        }
        return addr;
    }
    //说明是一个解引用操作，注意此操作非常危险 需要注意和c函数的交互
    if(tk == TK_DELREF){
        Debug("find token delref");
        //eat *
        scanner->scan();
        //接下来肯定是一个变量 否则就报错
        Expression *p = parsePrimaryExpr();
        DelRefExpr *delref = new DelRefExpr(line,column);
        delref->expr = p;
        return delref;
    //单独出现在这里 . () [] 一般是只有在链式表达式才会出现在这里
    }else if(tk == TK_DOT){
        scanner->scan();
        assert(scanner->curToken == TK_VAR);
        MemberExpr *me = new MemberExpr(line,column);
        me->membername = scanner->curLex;
        //next
        scanner->scan();
        return me;
    }else if(tk == TK_LPAREN){
        return parseFuncallExpr("");
    //a()[] 和 a[0][] 这两种情况可能就会当作链式索引访问
    }else if(tk == TK_LBRACKET && (prev == TK_RBRACKET || prev == TK_RPAREN)){
        return parseIndexExpr("");
    }
    //处理嵌套闭包的情况
    else if(tk == KW_FUNC)
    {
        Function* prev    = currentFunc;
        Function* closure = parseFuncDef(false,true);
        prev->closures.push_back(closure);
        //替换为一个ClosureExpression
        ClosureExpr* var = new ClosureExpr("placeholder",line,column);
        closure->receiver = var;
        //恢复func
        currentFunc = prev;
        return var;
    }else if(tk == TK_VAR)
    {
        auto var = scanner->curLex;
        //去掉标识符
        scanner->scan();
        return parseVarExpr(var);
    }else if(tk == LIT_INT)
    {
        //将 int 转换为 int
        auto val = atoi(scanner->curLex.c_str());
        scanner->scan();
        auto* ret = new IntExpr(line,column);
        ret->literal = val;
        return ret;
    }else if(tk == LIT_DOUBLE)
    {
        //将字面值 转换为double
        auto val     = atof(scanner->curLex.c_str());
        scanner->scan();
        auto* ret    = new DoubleExpr(line,column);
        ret->literal = val;
        return ret;
    }else if(tk == LIT_STR){
        //将字符串 ... 保存
        auto val     = scanner->curLex;
        scanner->scan();
        auto* ret    = new StringExpr(line,column);
        //将静态字符作为全局定义
        strs.push_back(ret);
        ret->literal = val;
        return ret;
    }else if(tk == LIT_CHAR)
    {
        //保存char
        auto val     = scanner->curLex;
        scanner->scan();
        auto* ret    = new CharExpr(line,column);
        ret->literal = val[0];
        return ret;
    }else if(tk == KW_TRUE || tk == KW_FALSE)
    {
        auto val     = (KW_TRUE == scanner->curToken);
        scanner->scan();
        auto* ret    = new BoolExpr(line,column);
        ret->literal = val;
        return ret;
    }else if(tk == KW_NULL)
    {
        scanner->scan();
        return new NullExpr(line,column);
    }else if(tk == TK_LBRACKET)
    {
        //解析数组 array
        scanner->scan();
        auto* ret = new ArrayExpr(line,column);
        if(scanner->curToken != TK_RBRACKET){
            while(scanner->curToken != TK_RBRACKET) {
                //将参数 push 到 node中
                ret->literal.push_back(parseExpression());
                //解析[1,2,3] 中的 ,
                if(scanner->curToken == TK_COMMA)
                    scanner->scan();
            }
            assert(scanner->curToken == TK_RBRACKET);
            scanner->scan();
            return ret;
        }
        //表示是一个空数组
        scanner->scan();
        return ret;

    // 解析map = {}
    }else if(tk == TK_LBRACE)
    {
        scanner->scan();
        auto* ret = new MapExpr(line,column);
        if(scanner->curToken != TK_RBRACE){
            while(scanner->curToken != TK_RBRACE) {
                KVExpr* kv = new KVExpr(line,column);
                //解析key
                kv->key    = parseExpression();
                //接下来必须是 : TK_COLON
                if(scanner->curToken != TK_COLON)
                    parse_err("ParserError: should be ':' token at line:%d column:%d\n",line,column);
                scanner->scan();
                //解析value
                kv->value  = parseExpression();
                //将参数 push 到 node中
                ret->literal.push_back(kv);
                //解析[1,2,3] 中的 ,
                if(scanner->curToken == TK_COMMA)
                    scanner->scan();
            }
            assert(scanner->curToken == TK_RBRACE);
            scanner->scan();
            return ret;
        }
        //表示是一个空数组
        scanner->scan();
        return ret;
        // 解析map = {}
    }else if(tk == KW_NEW)
    {
        //去掉 new
        scanner->scan();
        Debug("got new keywords:%s",scanner->curLex.c_str());
        //must var
        assert(scanner->curToken == TK_VAR);
        return parseNewExpr();

    }
    return nullptr;
}
/**
 * 1. obj = new p.p1.p2(a,b,d) class的创建
 * 2. st  = new p.p1.p2.A      struct的创建
 * 3. mem = len                内存的申请
 * 4. mem = 100                内存的申请 字节是单位
 */
Expression* Parser::parseNewExpr()
{
    if(scanner->curToken == LIT_INT){
        auto ret = new NewExpr(line,column);
        ret->len = atoi(scanner->curLex.c_str());
        return ret;
    }

    //有可能是包的方式进行访问
    string package = "";
    string name    = scanner->curLex;
    //must TK_LPAREN TK_RPAREN
    scanner->scan();
    if(scanner->curToken == TK_DOT){
        scanner->scan();
        assert(scanner->curToken == TK_VAR);
        package = name;
        name = scanner->curLex;
        scanner->scan();
    }
    // p<struct> = new struct 这种就没有括号 需要提前结束
    if(scanner->curToken != TK_LPAREN) {
        auto ret = new NewExpr(line,column);
        ret->package = package;
        ret->name    = name;
        return ret;
    }
    auto ret = new NewClassExpr(line,column);
    ret->package = package;
    ret->name = name;
    // p = new class(a,b,c) 这种还需要继续解析
    //eat (
    scanner->scan();
    //循环解析实参 func(1,2,3); while( c != ')');
    while(scanner->curToken != TK_RPAREN){
        ret->args.push_back(parseExpression());
        //ignore ','
        if(scanner->curToken == TK_COMMA)
            scanner->scan();
    }
    //去掉 )
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    return ret;
}
//1 解析变量定义 : var
//2 解析包名调用 : fmt.println()
//3 解析全局调用 : fmt.variable
Expression* Parser::parseVarExpr(std::string var)
{
    //处理包名映射
    string package(var);
    //如果为包名调用则优先用包名
    if(var != "_" && var != "__" && import.count(var)){
        package = import[var];
    }
    
    switch (scanner->curToken){

        //1. fmt.println 说明是一种包名的函数调用
        //2. fmt.global_var 说明是一种全局变量调用
        case TK_DOT:{
            //去掉.
            scanner->scan();
            assert(scanner->curToken == TK_VAR);
            std::string pfuncname = scanner->curLex;

            //下一个如果是 `(` 则说明为跨包函数调用 | 或者内部函数调用
            scanner->scan();
            if( scanner->curToken == TK_LPAREN)
            {
                FunCallExpr* call = dynamic_cast<FunCallExpr*>(parseFuncallExpr(pfuncname));
                call->is_pkgcall  = true;
                //这里处理映射关系
                call->package = package;
               if(package == "_" || package == "__")
                    call->is_extern = true;
                call->is_delref = package == "__";
                //这里判断如果 包名是之前的一个变量说明这个函数调用为成员函数调用
                VarExpr* obj;
                if(currentFunc->locals.count(var))
                    obj = currentFunc->locals[var];
                else
                    obj = currentFunc->params_var[var];
                //表明为成员函数调用
                if(obj){
                    auto params = call->args;
                    call->args.clear();
                    call->args.push_back(obj);
                    call->args.insert(call->args.end(),params.begin(),params.end());
                }
                return call;
            }else if(scanner->curToken == TK_LBRACKET){
                IndexExpr* index = dynamic_cast<IndexExpr*>(parseIndexExpr(pfuncname));
                index->is_pkgcall  = true;
                index->package = package;
                return index;
            }else{
                //说明是跨包全局变量访问: pkg.var
                //也有可能是对象成员变量访问:this.memeber
                //也有可能是struct成员变量访问
                //检查一下package是不是object
                VarExpr* mvar;
                if((mvar = currentFunc->getVar(package)) && mvar->structname != ""){
                    //找到成员变量访问了
                    StructMemberExpr* mexpr = new StructMemberExpr(package,scanner->line,scanner->column);
                    //去找到struct
                    mexpr->var = mvar;
                    mexpr->member = pfuncname;
                    return mexpr;
                }
                VarExpr* gvar    = new VarExpr(pfuncname,line,column);
                gvar->package    = package;
                gvar->is_local   = false;
                return gvar;
            }
        }
        //说明可能是函数调用 func()  var = func
        case TK_LPAREN:
            return parseFuncallExpr(var);
        //解析 var[i] 索引表达式
        case TK_LBRACKET:
            return parseIndexExpr(var);
        //解析 var<name> 结构体表达式
        //如果 不是这种就需要回退 < varname > 
        case TK_LT:{
            scanner->transaction();

            VarExpr* expr = new VarExpr(var,line,column);
            VarExpr* varexpr = new VarExpr(var,line,column);
            expr->structtype = true;
            scanner->scan();
            // var<p
            if(scanner->curToken == TK_VAR){
                string sname = scanner->curLex;
                expr->structname = sname;
                scanner->scan();
                if(scanner->curToken == TK_DOT){
                    scanner->scan();
                    assert(scanner->curToken == TK_VAR);
                    expr->package = sname;
                    expr->structname = scanner->curLex;
                    scanner->scan();
                }
                //判断一下可能类型为基础类型i8-u64 而且有可能是指针
                if(keywords.count(expr->structname) > 0){
                    auto i = keywords[expr->structname];
                    assert(i >= KW_I8 && i <= KW_U64);
                    expr->size = typesize[i];

                    if(i >= KW_U8 && i <= KW_U64)
                        expr->isunsigned = true;
                    if(scanner->curToken == TK_MUL){
                        expr->pointer = true;
                        scanner->scan();
                    }
                }                
                //如果不为 > 说明不满足  var<struct> || var<pkg.struct> 则回滚
                if(scanner->curToken != TK_GT){
                    scanner->rollback();
                    return varexpr;
                }
                scanner->scan();

                return expr;
            }
            //到这里说明肯定不是 p<struct>这种结构
            scanner->rollback();
            return varexpr;
        }
        default:
            VarExpr* varexpr = new VarExpr(var,line,column);
            return varexpr;
    } 
}
Expression*     Parser::parseFuncallExpr(std::string callname)
{
    scanner->scan();
    auto* val = new FunCallExpr(line,column);
    val->funcname = callname;

    //循环解析实参 func(1,2,3); while( c != ')');
    while(scanner->curToken != TK_RPAREN){
        val->args.push_back(parseExpression());
        //ignore ','
        if(scanner->curToken == TK_COMMA)
            scanner->scan();
    }
    //去掉 )
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    return val;  
}
Expression* Parser::parseIndexExpr(std::string varname){
    //去掉[
    scanner->scan();
    auto* val = new IndexExpr(line,column);
    val->varname = varname;
    //解析索引 没有索引则走新增操作
    val->index = parseExpression();
    assert(scanner->curToken == TK_RBRACKET);
    //去掉]
    scanner->scan();
    return val;
}