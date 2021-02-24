/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef CO_LANG_UTILS_H
#define CO_LANG_UTILS_H
#include <any>
#include <deque>
#include <string>
#include <iostream>


[[noreturn]] void parse_err(char const* const format, ...);

template <typename _DesireType, typename... _ArgumentType>
inline bool anyone(_DesireType k, _ArgumentType... args) {
    return ((args == k) || ...);
}


#endif //CO_LANG_UTILS_H
