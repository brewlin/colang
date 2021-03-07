#include "Internal.h"
#include "asm/AsmGen.h"
#include <functional>
#include <string>
/**
 * rsp 栈顶是 lhs
 * rax 寄存器是 rhs
 * binaryOper(opt,lhs,rhs) 只有三个参数
 * "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r10"
 * @param opt
 */
void Internal::call_operator(Token opt,std::string name)
{
    //注意参数顺序

    //第一个参数
    AsmGen::writeln("    mov $%ld, %%rdi", opt);
    //第三个参数 rhs 在栈顶的
    AsmGen::Pop("%rdx");
    //第二个参数 lhs 在栈顶的
    AsmGen::Pop("%rsi");
    call(name);
}

void Internal::call_object_operator(Token opt, std::string name,std::string method) {
    //第一个参数
    AsmGen::writeln("    mov $%ld, %%rdi", opt);
    //第四个参数是 rhs
    AsmGen::Pop("%rcx");

    //第三个参数  name
    std::hash<std::string> hash_key;
    size_t hk = hash_key(name);
    AsmGen::writeln("    mov $%ld,%%rdx",hk);

    //第二个参数  obj
    AsmGen::Pop("%rsi");
    call(method);
}
void Internal::gc_malloc()
{
    AsmGen::writeln("    mov $%ld, %%rdi", sizeof(Value));
    call("malloc");
}
/**
 * @return
 */
void Internal::newobject(int type, long data)
{
    AsmGen::writeln("    push %%rdi");
    AsmGen::writeln("    push %%rsi");

    AsmGen::writeln("    mov $%ld, %%rdi", type);
    if(type != String)
        AsmGen::writeln("    mov $%ld, %%rsi", data);

    call("newobject");

    AsmGen::writeln("    pop %%rsi");
    AsmGen::writeln("    pop %%rdi");
}
void Internal::isTrue()
{
    AsmGen::writeln("    mov %%rax, %%rdi");
    call("isTrue");
}
void Internal::get_object_value()
{
    AsmGen::writeln("    push %%rdi");
    AsmGen::writeln("    mov %%rax, %%rdi");
    call("get_object_value");
    AsmGen::writeln("    pop %%rdi");
}

void Internal::arr_pushone() {
    //rsi var
    AsmGen::Pop("%rsi");
    //rdi arr
    AsmGen::writeln("    mov (%rsp),%rdi");
    call("arr_pushone");
}

void Internal::kv_update() {
    //rdx var
    AsmGen::Pop("%rdx");
    //rsi index
    AsmGen::Pop("%rsi");
    //rdi arr
    AsmGen::writeln("    mov (%rsp),%rdi");
    call("kv_update");
}

void Internal::kv_get() {
    //rsi index
    AsmGen::Pop("%rsi");
    //rdi arr
    AsmGen::Pop("%rdi");
    call("kv_get");
}
void Internal::call(std::string funcname)
{
    AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
    AsmGen::writeln("    mov %%rax, %%r10");
    AsmGen::writeln("    mov $%d, %%rax", 0);
    AsmGen::writeln("    call *%%r10");
}
void Internal::object_member_get(std::string name)
{
    //第一个参数 object
    AsmGen::Pop("%rdi");

    //第二个参数  key
    std::hash<std::string> hash_key;
    size_t hk = hash_key(name);
    AsmGen::writeln("    mov $%ld,%%rsi",hk);

    call("object_member_get");

}
void Internal::object_func_add(std::string name)
{
    //func addr
    AsmGen::Pop("%rdx");

    //rsi func_name
    //第二个参数  key
    std::hash<std::string> hash_key;
    size_t hk = hash_key(name);
    AsmGen::writeln("    mov $%zu,%%rsi",hk);

    //object
    AsmGen::writeln("    mov (%rsp),%rdi");

    call("object_func_add");
}
void Internal::object_func_addr(std::string name)
{
    //第一个参数 object
    AsmGen::Pop("%rdi");

    //第二个参数  key
    std::hash<std::string> hash_key;
    size_t hk = hash_key(name);
    AsmGen::writeln("    mov $%zu,%%rsi",hk);

    call("object_func_addr");
}
