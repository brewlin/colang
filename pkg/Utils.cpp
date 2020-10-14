/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Utils.h"
#include <cstdarg>
#include <string>
std::string valueToStdString(Value v) {
    switch (v.type) {
        case Bool:
            return v.cast<bool>() ? "true" : "false";
        case Double:
            return std::to_string(v.cast<double>());
        case Int:
            return std::to_string(v.cast<int>());
        case Null:
            return "null";
        case Char: {
            std::string str;
            str += v.cast<char>();
            return str;
        }
        case Array: {
            std::string str = "[";
            auto elements = v.cast<std::vector<Value>>();
            for (int i = 0; i < elements.size(); i++) {
                str += valueToStdString(elements[i]);

                if (i != elements.size() - 1) {
                    str += ",";
                }
            }
            str += "]";
            return str;
        }
        case String:
            return v.cast<std::string>();
    }
    return "unknown";
}

std::string repeatString(int count, const std::string& str) {
    std::string result;
    for (int i = 0; i < count; i++) {
        result += str;
    }
    return result;
}

std::vector<Value> repeatArray(int count, std::vector<Value>&& arr) {
    std::vector<Value> result;
    for (int i = 0; i < count; i++) {
        result.insert(result.begin(), arr.begin(), arr.end());
    }
    return result;
}


[[noreturn]] void panic(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
std::string llvmTypeToStr(llvm::Type*  value) {
    llvm::Type::TypeID typeID;
    if( value )
        typeID = value->getTypeID();
    else
        return "Value is nullptr";

    switch (typeID){
        case llvm::Type::VoidTyID:
            return "VoidTyID";
        case llvm::Type::HalfTyID:
            return "HalfTyID";
        case llvm::Type::FloatTyID:
            return "FloatTyID";
        case llvm::Type::DoubleTyID:
            return "DoubleTyID";
        case llvm::Type::IntegerTyID:
            return "IntegerTyID";
        case llvm::Type::FunctionTyID:
            return "FunctionTyID";
        case llvm::Type::StructTyID:
            return "StructTyID";
        case llvm::Type::ArrayTyID:
            return "ArrayTyID";
        case llvm::Type::PointerTyID:
            return "PointerTyID";
        case llvm::Type::VectorTyID:
            return "VectorTyID";
        default:
            return "Unknown";
    }
}