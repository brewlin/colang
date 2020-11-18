/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_TYPE_H
#define LANG_TYPE_H
#include <any>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>
#include "Block.h"
#include "Function.h"


enum ValueType { Int,Double,String,Bool,Char,Null,Array};
enum ExecutionResultType{ ExecNormal,ExecReturn,ExecBreak,ExecContinue};



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

/**
 * 动态变量类型定义
 */
struct Value{
    explicit Value(){}
    explicit Value(ValueType type)
            :type(type){}
    explicit Value(ValueType type,std::any data)
            :type(type),data(std::move(data)){}

    template <int doType>
    inline  bool isType(){
        return this->type == doType;
    }
    template <typename _CastingType>
    inline _CastingType cast(){
        return std::any_cast<_CastingType>(data);
    }
    template <typename  _DataType>
    inline  void set(_DataType data){
        this->data = std::make_any<_DataType>(std::move(data));
    }

    //value 的类型
    ValueType  type{};
    ///可以存储任意类型
    std::any data;
};


#endif //LANG_TYPE_H
