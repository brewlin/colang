/**
 *@ClassName Builtin
 *@Author brewlin
 *@Date 2020/9/4 0004 上午 10:39
 *@Version 1.0
 **/
#ifndef LANG_BUILTIN_H
#define LANG_BUILTIN_H

#include <deque>
#include <string>
#include "Runtime.h"
#include "Context.h"

Value do_print(Runtime* rt,
                           std::deque<Context*> ctx,
                           std::vector<Value> args);

Value do_println(Runtime* rt,
                           std::deque<Context*> ctx,
                           std::vector<Value> args);
Value do_input(Runtime* rt,
                           std::deque<Context*> ctx,
                           std::vector<Value> args);

Value do_typeof(Runtime* rt,
                           std::deque<Context*> ctx,
                           std::vector<Value> args);

Value do_len(Runtime* rt,
                           std::deque<Context*> ctx,
                           std::vector<Value> args);

Value do_time(Runtime* rt,
                       std::deque<Context*> ctx,
                       std::vector<Value> args);

#endif //LANG_BUILTIN_H
