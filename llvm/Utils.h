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
#include "Value.h"


// llvm ---------------------------- vmll

std::string  llvmTypeToStr(llvm::Type*  value);

#endif //LANG_UTILS_H
