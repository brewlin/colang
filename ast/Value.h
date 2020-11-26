/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_TYPE_H
#define LANG_TYPE_H
#include <deque>
#include <string>
#include <vector>
#include "Function.h"

/**
 * 函数
 */
struct Struct {
    //函数定义 函数声明  外部函数
    explicit Struct(){};
    ~Struct(){}

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


#endif //LANG_TYPE_H
