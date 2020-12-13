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

/**
 * 函数
 */
struct Class {
    //函数定义 函数声明  外部函数
    explicit Class(){};
    ~Class(){}

    std::string name;
    //成员变量
    std::vector<std::string> members;
    //成员函数
    std::vector<Function*> funcs;
};

struct Value{
    long     type;
    void*    data;
};


#endif //CO_LANG_TYPE_H
