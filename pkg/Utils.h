/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef LANG_UTILS_H
#define LANG_UTILS_H
#include <any>
#include <deque>
#include <string>
#include <iostream>
#include "Llvm.h"
#include "Value.h"


std::string valueToStdString(Value v);

std::string repeatString(int count, const std::string& str);

std::vector<Value> repeatArray(int count, std::vector<Value>&& arr);

[[noreturn]] void parse_err(char const* const format, ...);

template <typename _DesireType, typename... _ArgumentType>
inline bool anyone(_DesireType k, _ArgumentType... args) {
    return ((args == k) || ...);
}


// llvm ---------------------------- vmll

std::string  llvmTypeToStr(llvm::Type*  value);

#endif //LANG_UTILS_H
