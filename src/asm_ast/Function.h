/**
 *@ClassName Function
 *@Author brewlin
 *@Date 2020/12/15 0015 下午 4:26
 *@Version 1.0
 **/
#ifndef COLANG_FUNCTION_H
#define COLANG_FUNCTION_H

#include <iostream>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "Instruct.h"

namespace asmer{
    class Function{
    public:
        Function(std::string name):labelname(name){}
        ~Function(){}

        //记录有序的符号数据定义
        std::vector<Instruct*>    instructs;
        //标签名
        std::string               labelname;
    };
};

#endif //COLANG_FUNCTION_H
