/**
 *@Author brewlin
 *@Date 2020/9/27 0027 上午 11:43
 *@Version 1.0
 **/

#include "Parser.h"
/**
 * 解析语法表达式
 * @return
 */
Statement* Parser::parseStatement()
{
    Statement* node;
    switch (scanner->curToken){
        case KW_IF:
            scanner->scan();
            node = parseIfStmt();
            break;
        case KW_FOR:
            scanner->scan();
            node = parseForStmt();
            break;
        case KW_WHILE:
            scanner->scan();
            node = parseWhileStmt();
            break;
        case KW_RETURN:
            scanner->scan();
            node = parseReturnStmt();
            break;
        case KW_BREAK:
            scanner->scan();
            node = new BreakStmt(line,column);
            break;
        case KW_CONTINUE:
            scanner->scan();
            node = new ContinueStmt(line,column);
            break;
        default:
            node = parseExpressionStmt();
            break;
    }
    return node;
}
/**
 * 解析if语句表达式
 * 
 */
IfStmt*   Parser::parseIfStmt()
{
    auto* node = new IfStmt(line,column);
    //去掉左括号
    scanner->scan();
    //解析条件表达式
    node->cond = parseExpression();
    //去掉右括号
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    //解析语句块
    node->block = parseBlock();
    //如果当前关键字是else， 则继续解析else语句块
    if(scanner->curToken == KW_ELSE){
        //去掉else关键字
        scanner->scan();
        //解析else语句块
        node->elseBlock = parseBlock();
    }
    return node;
}
/**
 * 解析for语句表达式
 * 
 */
ForStmt*   Parser::parseForStmt()
{
    auto* node = new ForStmt(line,column);
    //去掉左括号
    scanner->scan();
    //解析初始化表达式
    node->init = parseExpression();
    //去掉;
    assert(scanner->curToken == TK_SEMICOLON);
    scanner->scan();

    //解析条件表达式
    node->cond = parseExpression();
    //去掉;
    assert(scanner->curToken == TK_SEMICOLON);
    scanner->scan();

    //解析后置操作
    node->after = parseExpression();

    //去掉右括号
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    //解析语句块
    node->block = parseBlock();
    return node;
}


/**
 * 解析while语句表达式
 * @return
 */
WhileStmt* Parser::parseWhileStmt() {
    auto* node = new WhileStmt(line, column);
    // 去掉左括号
    scanner->scan();
    // 解析条件表达式
    node->cond = parseExpression();
    // 去掉右括号
    assert(scanner->curToken == TK_RPAREN);
    scanner->scan();
    // 解析语句块
    node->block = parseBlock();
    return node;
}
/**
 * 解析return语句表达式
 * @return
 */
ReturnStmt* Parser::parseReturnStmt() {
    auto* node = new ReturnStmt(line, column);
    // 解析返回值表达式
    node->ret = parseExpression();
    return node;
}
/**
 *
 * 解析表达式语句
 * @return
 */
ExpressionStmt* Parser::parseExpressionStmt()
{
    ExpressionStmt* node = nullptr;
    if(auto p = parseExpression() ; p != nullptr)
        node = new ExpressionStmt(p,line,column);
    return node;
}