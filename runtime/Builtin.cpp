/**
 *@ClassName Builtin
 *@Author brewlin
 *@Date 2020/9/4 0004 上午 10:39
 *@Version 1.0
 **/
#include "Builtin.h"
#include <iostream>
#include <vector>
#include "Ast.h"
#include "Builtin.h"
#include "do.h"
#include "Utils.h"
#include <time.h>

Value do_print(Runtime* rt,
                             std::deque<Context*> ctx,
                             std::vector<Value> args) {
    for (auto arg : args) {
        std::cout << valueToStdString(arg);
    }
    return Value(Int, (int)args.size());
}

Value do_println(Runtime* rt,
                               std::deque<Context*> ctx,
                               std::vector<Value> args) {
    if (args.size() != 0) {
        for (auto arg : args) {
            std::cout << valueToStdString(arg) << "\n";
        }
    } else {
        std::cout << "\n";
    }

    return Value(Int, (int)args.size());
}

Value do_input(Runtime* rt,
                             std::deque<Context*> ctx,
                             std::vector<Value> args) {
    Value result{String};

    std::string str;
    std::cin >> str;
    result.data = std::make_any<std::string>(std::move(str));
    return result;
}

Value do_typeof(Runtime* rt,
                              std::deque<Context*> ctx,
                              std::vector<Value> args) {
    if (args.size() != 1) {
        panic("ArgumentError: expects one argument but got %d\n", args.size());
    }
    Value result(String);
    switch (args[0].type) {
        case Bool:
            result.set<std::string>("bool");
            break;
        case Double:
            result.set<std::string>("double");
            break;
        case Int:
            result.set<std::string>("int");
            break;
        case String:
            result.set<std::string>("string");
            break;
        case Null:
            result.set<std::string>("null");
            break;
        case Char:
            result.set<std::string>("char");
            break;
        case Array:
            result.set<std::string>("array");
            break;
        default:
            //TODO: unkonw type catch
            panic("TypeError: unknown type!\n");
    }
    return result;
}

Value do_len(Runtime* rt,
                              std::deque<Context*> ctx,
                              std::vector<Value> args) {
    if (args.size() != 1) {
        panic("ArgumentError: expects one argument but got %d\n", args.size());
    }

    if (args[0].isType<String>()) {
        return Value(
            Int, std::make_any<int>(args[0].cast<std::string>().length()));
    }
    if (args[0].isType<Array>()) {
        return Value(
            Int,
            std::make_any<int>(args[0].cast<std::vector<Value>>().size()));
    }

    panic(
        "TypeError: unexpected type of arguments, requires string type or "
        "array type\n");
}

Value do_time(Runtime* rt,
                     std::deque<Context*> ctx,
                     std::vector<Value> args) {
    int t = time(NULL);
    return Value(Int,t);
}
