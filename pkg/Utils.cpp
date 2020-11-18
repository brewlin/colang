/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Utils.h"
#include <cstdarg>
#include <string>

[[noreturn]] void parse_err(char const* const format, ...) {
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