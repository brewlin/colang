/**
 *@Author brewlin
 *@Date 2020/9/22 0022 下午 3:26
 *@Version 1.0
 **/
#ifndef COMPILER_BLOCK_H
#define COMPILER_BLOCK_H
#include <vector>

struct Statement;
/**
 * 一般是用于存储 func 函数内的语句列表
 * 在execte阶段调用函数式 顺序遍历该语句执行
 * Block 语句块
*/
struct Block{
    explicit Block() = default;
    std::vector<Statement*> stmts;
};



#endif //COMPILER_BLOCK_H
