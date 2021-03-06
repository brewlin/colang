/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef CO_LANG_TYPE_H
#define CO_LANG_TYPE_H
#include <deque>
#include <string>
#include <vector>
#include "Function.h"
#include "Token.h"
using namespace std;

#define ALIGN_UP(x,a) (((x) + (a - 1)) & ~(a - 1))
#define ALIGN_DOWN(x,a) (ALIGN_UP(x-a+1,a))

struct Class 
{
    //函数定义 函数声明  外部函数
    string name;
    //成员变量
    vector<string> members;
    //成员函数
    vector<Function*> funcs;
};

struct Member
{
    string  name;
    Token   type;
    int     size;
    bool    isunsigned;
    bool    pointer;

    int     idx;
    int     align;
    int     offset;
    //位图的相关属性
    bool    bitfield;
    int     bitoffset;
    int     bitwidth;
};
struct Struct 
{
    string  pkg;
    string  name;
    int     size;
    //成员
    vector<Member*> member;
    void    compute();
    Member* getMember(string name);
};

struct Value
{
    long     type;
    void*    data;
};


#endif //CO_LANG_TYPE_H
