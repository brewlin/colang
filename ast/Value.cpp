/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Value.h"
#include "Utils.h"

/**
 * 一般将 value 用于条件判断是否为true
 * @return
 */
bool Value::isTrue()
{
    if (isType<Int>())
        return cast<int>() != 0;
    else if (isType<Double>())
        return cast<double>() != 0;
    else if(isType<String>())
        return valueToStdString(*this) != "";
    else if(isType<Bool>())
        return cast<bool>();
    else if(this->type == Null)
        return false;
    else if(isType<Char>())
        return valueToStdString(*this) != "";
    else if(isType<Array>())
        return cast<std::vector<Value>>().size() != 0;
    else parse_err("TypeError: unexpected arguments of operator !=");
}
