/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Ast.h"
#include "Expression.h"
#include "Statement.h"
std::string Expression::toString() { return "Expr()"; }

std::string Statement::toString() { return "Stmt()"; }

std::string BoolExpr::toString() {
    return "BoolExpr(" + std::to_string(literal) + ")";
}

std::string CharExpr::toString() {
    return "CharExpr(" + std::to_string(literal) + ")";
}

std::string NullExpr::toString() { return "NullExpr()"; }

std::string IntExpr::toString() {
    return "IntExpr(" + std::to_string(literal) + ")";
}

std::string DoubleExpr::toString() {
    return "DoubleExpr(" + std::to_string(literal) + ")";
}

std::string StringExpr::toString() { return "StringExpr(" + literal + ")"; }

std::string ArrayExpr::toString() {
    std::string str = "ArrayExpr(elements=[";
    if (literal.size() != 0) {
        for (auto& e : literal) {
            str += e->toString();
        }
    }
    str += "])";
    return str;
}

std::string IdentExpr::toString() { return "IdentExpr(" + identname + ")"; }

std::string IndexExpr::toString() {
    std::string str = "IndexExpr(index=";
    str += index->toString();
    str += ")";
    return str;
}

std::string BinaryExpr::toString() {
    std::string str = "BinaryExpr(";
    if (opt != INVALID) {
        str += "opt=";
        switch (opt) {
            case TK_BITAND:
                str += "&";
                break;
            case TK_BITOR:
                str += "|";
                break;
            case TK_BITNOT:
                str += "!";
                break;
            case TK_LOGAND:
                str += "&&";
                break;
            case TK_LOGOR:
                str += "||";
                break;
            case TK_LOGNOT:
                str += "!";
                break;
            case TK_PLUS:
                str += "+";
                break;
            case TK_MINUS:
                str += "-";
                break;
            case TK_MUL:
                str += "*";
                break;
            case TK_DIV:
                str += "/";
                break;
            case TK_MOD:
                str += "%";
                break;
            case TK_EQ:
                str += "==";
                break;
            case TK_NE:
                str += "!=";
                break;
            case TK_GT:
                str += ">";
                break;
            case TK_GE:
                str += ">=";
                break;
            case TK_LT:
                str += "<";
                break;
            case TK_LE:
                str += "<=";
                break;
            case TK_ASSIGN:
                str += "=";
                break;
            default:
                str += std::to_string(opt);
                break;
        }
    }
    if (lhs) {
        str += ",lhs=";
        str += lhs->toString();
    }
    if (rhs) {
        str += ",rhs=";
        str += rhs->toString();
    }
    str += ")";
    return str;
}

std::string FunCallExpr::toString() {
    std::string str = "FunCallExpr(func=";
    str += funcname;
    str += ",args=[";
    for (auto& arg : args) {
        str += arg->toString();
        str += ",";
    }
    str += "])";
    return str;
}

std::string AssignExpr::toString() {
    std::string str = "AssignExpr(lhs=";
    str += lhs->toString();
    str += ",rhs=";
    str += rhs->toString();
    str += ")";
    return str;
}
std::string NewExpr::toString(){
    std::string str = "NewExpr(";
    str += type;
    str += ")";
    return str;
}
std::string MemberExpr::toString(){
    std::string str = "MemberExpr(";
    str += varname;
    str += ".";
    str += membername;
    str += ")";
    return str;
}
std::string MemberCallExpr::toString() {
    std::string str = "MemberCallExpr(varname=";
    str += varname;
    str += ",func=";
    str += membername;
    str += ",args=[";
    for (auto& arg : args) {
        str += arg->toString();
        str += ",";
    }
    str += "])";
    return str;
}


std::string ExpressionStmt::toString() {
    std::string str = "ExpressionStmt(expr=";
    str += expr->toString();
    str += ")";
    return str;
}

std::string WhileStmt::toString() {
    std::string str = "WhileStmt(cond=";
    str += cond->toString();
    str += ",exprs=[";
    for (auto& e : block->stmts) {
        str += e->toString();
        str += ",";
    }
    str += "])";
    return str;
}

std::string IfStmt::toString() {
    std::string str = "IfStmt(cond=";
    str += cond->toString();
    str += ",exprs=[";
    for (auto& e : block->stmts) {
        str += e->toString();
        str += ",";
    }
    str += "])";
    return str;
}

std::string ReturnStmt::toString() {
    std::string str = "ReturnStmt(";
    if (ret) {
        str += "ret=";
        str += ret->toString();
    }
    str += ")";
    return str;
}

std::string BreakStmt::toString() { return "BreakStmt()"; }

std::string ContinueStmt::toString() { return "ContinueStmt()"; }
