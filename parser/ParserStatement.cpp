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
    switch (getCurrentToken()){
        case KW_IF:
            currentToken = next();
            node = parseIfStmt();
            break;
        case KW_WHILE:
            currentToken = next();
            node = parseWhileStmt();
            break;
        case KW_RETURN:
            currentToken = next();
            node = parseReturnStmt();
            break;
        case KW_BREAK:
            currentToken = next();
            node = new BreakStmt(line,column);
            break;
        case KW_CONTINUE:
            currentToken = next();
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
 * @param filename
 */
IfStmt*   Parser::parseIfStmt()
{
    auto* node = new IfStmt(line,column);
    //去掉左括号
    currentToken = next();
    //解析条件表达式
    node->cond = parseExpression();
    //去掉右括号
    assert(getCurrentToken() == TK_RPAREN);
    currentToken = next();
    //解析语句块
    node->block = parseBlock();
    //如果当前关键字是else， 则继续解析else语句块
    if(getCurrentToken() == KW_ELSE){
        //去掉else关键字
        currentToken = next();
        //解析else语句块
        node->elseBlock = parseBlock();
    }
    return node;
}

/**
 * 解析while语句表达式
 * @return
 */
WhileStmt* Parser::parseWhileStmt() {
    auto* node = new WhileStmt(line, column);
    // 去掉左括号
    currentToken = next();
    // 解析条件表达式
    node->cond = parseExpression();
    // 去掉右括号
    assert(getCurrentToken() == TK_RPAREN);
    currentToken = next();
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