/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Value.h"
#include "Utils.h"

Value Value::operator+(Value rhs) {
    Value result;
    // Basic
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = cast<int>() + rhs.cast<int>();
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<double>() + rhs.cast<double>();
    } else if (isType<Int>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<int>() + rhs.cast<double>();
    } else if (isType<Double>() && rhs.isType<Int>()) {
        result.type = Double;
        result.data = cast<double>() + rhs.cast<int>();
    } else if (isType<Char>() && rhs.isType<Int>()) {
        result.type = Char;
        result.data = static_cast<char>(cast<char>() + rhs.cast<int>());
    } else if (isType<Int>() && rhs.isType<Char>()) {
        result.type = Char;
        result.data = static_cast<char>(cast<int>() + rhs.cast<char>());
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Char;
        result.data = static_cast<char>(cast<char>() + rhs.cast<char>());
    }
        // String
        // One of operands has string type, we say the result value was a string
    else if (isType<String>() || rhs.isType<String>()) {
        result.type = String;
        result.data = valueToStdString(*this) + valueToStdString(rhs);
    }
        // Array
    else if (isType<Array>()) {
        result.type = Array;
        auto resultArr = this->cast<std::vector<Value>>();
        resultArr.push_back(rhs);
        result.data = resultArr;
    } else if (rhs.isType<Array>()) {
        result.type = Array;
        auto resultArr = rhs.cast<std::vector<Value>>();
        resultArr.push_back(*this);
        result.data = resultArr;
    }
        // Invalid
    else {
        panic("TypeError: unexpected arguments of operator +");
    }
    return result;
}

Value Value::operator-(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = cast<int>() - rhs.cast<int>();
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<double>() - rhs.cast<double>();
    } else if (isType<Int>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<int>() - rhs.cast<double>();
    } else if (isType<Double>() && rhs.isType<Int>()) {
        result.type = Double;
        result.data = cast<double>() - rhs.cast<int>();
    } else if (isType<Char>() && rhs.isType<Int>()) {
        result.type = Char;
        result.data = static_cast<char>(cast<char>() - rhs.cast<int>());
    } else if (isType<Int>() && rhs.isType<Char>()) {
        result.type = Char;
        result.data = static_cast<char>(cast<int>() - rhs.cast<char>());
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Char;
        result.data = static_cast<char>(cast<char>() - rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator -");
    }

    return result;
}

Value Value::operator*(Value rhs) {
    Value result;
    // Basic
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = cast<int>() * rhs.cast<int>();
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<double>() * rhs.cast<double>();
    } else if (isType<Int>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<int>() * rhs.cast<double>();
    } else if (isType<Double>() && rhs.isType<Int>()) {
        result.type = Double;
        result.data = cast<double>() * rhs.cast<int>();
    }
        // String
    else if (isType<String>() && rhs.isType<Int>()) {
        result.type = String;
        result.data = repeatString(rhs.cast<int>(), cast<std::string>());
        //TODO: 2 * "1 " 这种情况会异常  期望:2 实际: 1 1
    } else if (isType<Int>() && rhs.isType<String>()) {
        result.type = String;
        result.data = repeatString(cast<int>(), rhs.cast<std::string>());
    }
        // Array
    else if (isType<Int>() && rhs.isType<Array>()) {
        result.type = Array;
        result.data = repeatArray(
                cast<int>(), std::move(rhs.cast<std::vector<Value>>()));
    } else if (isType<Array>() && rhs.isType<Int>()) {
        result.type = Array;
        result.data = repeatArray(rhs.cast<int>(),
                                  std::move(cast<std::vector<Value>>()));
    } else {
        panic("TypeError: unexpected arguments of operator *");
    }
    return result;
}

Value Value::operator/(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = cast<int>() / rhs.cast<int>();
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<double>() / rhs.cast<double>();
    } else if (isType<Int>() && rhs.isType<Double>()) {
        result.type = Double;
        result.data = cast<int>() / rhs.cast<double>();
    } else if (isType<Double>() && rhs.isType<Int>()) {
        result.type = Double;
        result.data = cast<double>() / rhs.cast<int>();
    } else {
        panic("TypeError: unexpected arguments of operator /");
    }
    return result;
}

Value Value::operator%(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = (int)cast<int>() % rhs.cast<int>();
    } else {
        panic("TypeError: unexpected arguments of operator %");
    }
    return result;
}

Value Value::operator&&(Value rhs) {
    Value result;
    if (isType<Bool>() && rhs.isType<Bool>()) {
        result.type = Bool;
        result.data = (cast<bool>() && rhs.cast<bool>());
    } else {
        panic("TypeError: unexpected arguments of operator &&");
    }
    return result;
}

Value Value::operator||(Value rhs) {
    Value result;
    if (isType<Bool>() && rhs.isType<Bool>()) {
        result.type = Bool;
        result.data = (cast<bool>() || rhs.cast<bool>());
    } else {
        panic("TypeError: unexpected arguments of operator ||");
    }
    return result;
}

Value Value::operator==(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Bool;
        result.data = (cast<int>() == rhs.cast<int>());
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Bool;
        result.data = (cast<double>() == rhs.cast<double>());
    } else if (isType<String>() && rhs.isType<String>()) {
        result.type = Bool;
        std::string lhsStr, rhsStr;
        lhsStr = valueToStdString(*this);
        rhsStr = valueToStdString(rhs);
        result.data = (lhsStr == rhsStr);
    } else if (isType<Bool>() && rhs.isType<Bool>()) {
        result.type = Bool;
        result.data = (cast<bool>() == rhs.cast<bool>());
    } else if (this->type == Null && rhs.type == Null) {
        result.type = Bool;
        result.data = std::make_any<bool>(true);
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Bool;
        result.data = (cast<char>() == rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator ==");
    }
    return result;
}

Value Value::operator!=(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Bool;
        result.data = (cast<int>() != rhs.cast<int>());
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Bool;
        result.data = (cast<double>() != rhs.cast<double>());
    } else if (isType<String>() && rhs.isType<String>()) {
        result.type = Bool;
        std::string lhsStr, rhsStr;
        lhsStr = valueToStdString(*this);
        rhsStr = valueToStdString(rhs);
        result.data = (lhsStr != rhsStr);
    } else if (isType<Bool>() && rhs.isType<Bool>()) {
        result.type = Bool;
        result.data = (cast<bool>() != rhs.cast<bool>());
    } else if (this->type == Null && rhs.type == Null) {
        result.type = Bool;
        result.data = std::make_any<bool>(false);
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Bool;
        result.data = (cast<char>() != rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator !=");
    }
    return result;
}

Value Value::operator>(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Bool;
        result.data = (cast<int>() > rhs.cast<int>());
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Bool;
        result.data = (cast<double>() > rhs.cast<double>());
    } else if (isType<String>() && rhs.isType<String>()) {
        result.type = Bool;
        std::string lhsStr, rhsStr;
        lhsStr = valueToStdString(*this);
        rhsStr = valueToStdString(rhs);
        result.data = (lhsStr > rhsStr);
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Bool;
        result.data = (cast<char>() > rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator >");
    }
    return result;
}

Value Value::operator>=(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Bool;
        result.data = (cast<int>() >= rhs.cast<int>());
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Bool;
        result.data = (cast<double>() >= rhs.cast<double>());
    } else if (isType<String>() && rhs.isType<String>()) {
        result.type = Bool;
        std::string lhsStr, rhsStr;
        lhsStr = valueToStdString(*this);
        rhsStr = valueToStdString(rhs);
        result.data = (lhsStr >= rhsStr);
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Bool;
        result.data = (cast<char>() >= rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator >=");
    }
    return result;
}

Value Value::operator<(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Bool;
        result.data = (cast<int>() < rhs.cast<int>());
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Bool;
        result.data = (cast<double>() < rhs.cast<double>());
    } else if (isType<String>() && rhs.isType<String>()) {
        result.type = Bool;
        std::string lhsStr, rhsStr;
        lhsStr = valueToStdString(*this);
        rhsStr = valueToStdString(rhs);
        result.data = (lhsStr < rhsStr);
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Bool;
        result.data = (cast<char>() < rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator <");
    }
    return result;
}

Value Value::operator<=(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Bool;
        result.data = (cast<int>() <= rhs.cast<int>());
    } else if (isType<Double>() && rhs.isType<Double>()) {
        result.type = Bool;
        result.data = (cast<double>() <= rhs.cast<double>());
    } else if (isType<String>() && rhs.isType<String>()) {
        result.type = Bool;
        std::string lhsStr, rhsStr;
        lhsStr = valueToStdString(*this);
        rhsStr = valueToStdString(rhs);
        result.data = (lhsStr <= rhsStr);
    } else if (isType<Char>() && rhs.isType<Char>()) {
        result.type = Bool;
        result.data = (cast<char>() <= rhs.cast<char>());
    } else {
        panic("TypeError: unexpected arguments of operator <=");
    }
    return result;
}

Value Value::operator&(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = (cast<int>() & rhs.cast<int>());
    } else {
        panic("TypeError: unexpected arguments of operator &");
    }
    return result;
}

Value Value::operator|(Value rhs) {
    Value result;
    if (isType<Int>() && rhs.isType<Int>()) {
        result.type = Int;
        result.data = (cast<int>() | rhs.cast<int>());
    } else {
        panic("TypeError: unexpected arguments of operator |");
    }
    return result;
}

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
    else panic("TypeError: unexpected arguments of operator !=");
}
