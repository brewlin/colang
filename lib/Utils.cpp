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
