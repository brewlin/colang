/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Ast.h"
#include "Expression.h"
#include "Statement.h"
#include "Block.h"

string getTokenString(Token tk){
    //invalid identifier eof
    switch (tk) {
        case INVALID:    return "invalid";
        case TK_VAR:   return "ident";
        case TK_EOF:     return "eof";
        case LIT_INT:    return "int";
        case LIT_STR:    return "string";
        case LIT_DOUBLE: return "double";
        case LIT_CHAR:  return "char";
        case TK_BITAND:	return "&";
        case TK_BITOR:	return "|";
        case TK_BITXOR:	return "^";
        case TK_BITNOT:	return "~";
        case TK_SHIFTL:	return "<<";
        case TK_SHIFTR:	return ">>";

        case TK_LOGAND:	return "&&";
        case TK_LOGOR:	return "||";
        case TK_LOGNOT:	return "!";
        case TK_EQ:	return "==";
        case TK_NE:	return "!=";
        case TK_GT:	return ">";
        case TK_GE:	return ">=";
        case TK_LT:	return "<";
        case TK_LE:	return "<=";

            //+ - * / %
        case TK_PLUS:	return "+";
        case TK_MINUS:	return "-";
        case TK_MUL:	return "*";
        case TK_DIV:	return "/";
        case TK_MOD:	return "%";

        case TK_ASSIGN:	return "=";
        case TK_PLUS_AGN:	return "+=";
        case TK_MINUS_AGN:	return "-=";
        case TK_MUL_AGN:	return "*=";
        case TK_DIV_AGN:	return "/=";
        case TK_MOD_AGN:	return "%=";
        case TK_COMMA:	return ",";
        case TK_LPAREN:	return "(";
        case TK_RPAREN:	return ")";
        case TK_LBRACE:	return "{";
        case TK_RBRACE:	return "}";
        case TK_LBRACKET:	return "[";
        case TK_RBRACKET:	return "]";
        case TK_DOT:	return ".";
        case TK_COLON:	return ":";
        case KW_IF:	return "if";
        case KW_ELSE:	return "else";
        case KW_TRUE:	return "true";
        case KW_FALSE:	return "false";
        case KW_WHILE:	return "while";
        case KW_FOR:	return "for";
        case KW_NULL:	return "null";
        case KW_FUNC:	return "func";
        case KW_RETURN:	return "return";
        case KW_BREAK:	return "break";
        case KW_CONTINUE:	return "continue";
        case KW_NEW:	return "new";
        case KW_EXTERN:	return "extern";
        case KW_IMPORT:	return "import";
        case KW_GO:	return "go";
        case KW_CLASS:	return "class";
        case KW_PACKAGE:	return "package";
        case TK_DELREF:	return "(*)var";
        default:	return "undefine";
    }
}

string Expression::toString() { return "Expr()"; }

string Statement::toString() { return "Stmt()"; }

string BoolExpr::toString() {
    return "BoolExpr(" + to_string(literal) + ")";
}

string CharExpr::toString() {
    return "CharExpr(" + to_string(literal) + ")";
}

string NullExpr::toString() { return "NullExpr()"; }

string IntExpr::toString() {
    return to_string(literal);
}

string DoubleExpr::toString() {
    return "DoubleExpr(" + to_string(literal) + ")";
}

string StringExpr::toString() { return "StringExpr(" + literal + ")"; }

string ArrayExpr::toString() {
    string str = "ArrayExpr(elements=[";
    if (literal.size() != 0) {
        for (auto& e : literal) {
            str += e->toString();
        }
    }
    str += "])";
    return str;
}
string MapExpr::toString() {
    string str = "MapExpr(elements={";
    if (literal.size() != 0) {
        for (auto& e : literal) {
            str += e->toString();
        }
    }
    str += "})";
    return str;
}
string KVExpr::toString() {
    string str = "{";
    if (key)   str += key->toString();
    str += ":";
    if (value) str += value->toString();
    str += "}";
    return str;
}

string VarExpr::toString() { return "VarExpr(" + varname + ")"; }
string ClosureExpr::toString() { return "ClosureExpr(" + varname + ")"; }

string AddrExpr::toString(){
    return "AddrExpr(" + package + "." + varname + ")";
}
string DelRefExpr::toString(){
    return "DelRefExpr(" + expr->toString() + ")";
}
string StructMemberExpr::toString(){
    return "StructMemberExpr(" + varname + "<"+structname+">"+"."+member+")";
}

string IndexExpr::toString() {
    string str = "IndexExpr(index=";
    if(index)
        str += index->toString();
    str += ")";
    return str;
}

string ChainExpr::toString() {
    string str = "ChainExpr(";
    str += "left=" + lhs->toString();
    str += ",right=" + rhs->toString();
    str += ")";
    return str;
}

string BinaryExpr::toString() {
    string str = "BinaryExpr(";
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
                str += to_string(opt);
                break;
        }
    }
    if (lhs) {
        str += ",lhs=";
        if(lhs)
            str += lhs->toString();
    }
    if (rhs) {
        str += ",rhs=";
        if(rhs)
            str += rhs->toString();
    }
    str += ")";
    return str;
}

string FunCallExpr::toString() {
    string str = "FunCallExpr[func = ";
    str += package + "." + funcname;
    str += ",args = (";
    for (auto& arg : args) {
        str += arg->toString();
        str += ",";
    }
    str += ")]";
    return str;
}

string AssignExpr::toString() {
    string str = "AssignExpr(lhs=";
    if(lhs)
        str += lhs->toString();
    str += ",rhs=";
    if(rhs)
        str += rhs->toString();
    str += ")";
    return str;
}
string NewClassExpr::toString(){
    string str = "NewExpr(";
    str += package;
    str += ",";
    str += name;
    str += ")";
    return str;
}
string NewExpr::toString(){
    string str = "NewExpr(";
    str += package;
    str += ",";
    str += name;
    str += ")";
    return str;
}

string MemberExpr::toString(){
    string str = "MemberExpr(";
    str += varname;
    str += ".";
    str += membername;
    str += ")";
    return str;
}
string MemberCallExpr::toString() {
    string str = "MemberCallExpr(varname=";
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


string ExpressionStmt::toString() {
    string str = "ExpressionStmt(expr=";
    str += expr->toString();
    str += ")";
    return str;
}

string WhileStmt::toString() {
    string str = "WhileStmt(cond=";
    str += cond->toString();
    str += ",exprs=[";
    for (auto& e : block->stmts) {
        str += e->toString();
        str += ",";
    }
    str += "])";
    return str;
}

string IfStmt::toString() {
    string str = "IfStmt(cond=";
    str += cond->toString();
    str += ",exprs=[";
    for (auto& e : block->stmts) {
        str += e->toString();
        str += ",";
    }
    str += "])";
    return str;
}
string ForStmt::toString() {
    string str = "ForStmt(";
    str += " init="  + init->toString();
    str += ",cond="  + cond->toString();
    str += ",after=" + after->toString();
    str += ",exprs=[";
    for (auto& e : block->stmts) {
        str += e->toString();
        str += ",";
    }
    str += "])";
    return str;
}

string ReturnStmt::toString() {
    string str = "ReturnStmt(";
    if (ret) {
        str += "ret=";
        str += ret->toString();
    }
    str += ")";
    return str;
}

string BreakStmt::toString() { return "BreakStmt()"; }

string ContinueStmt::toString() { return "ContinueStmt()"; }
