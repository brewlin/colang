#ifndef _string_H_
#define _string_H_

#include <stdlib.h>
#define gc_malloc malloc
#define gc_free   free
typedef struct {
    char *ptr;
    size_t size;
    size_t len;
} string;

// 初始化字符串
string* string_init();

// 使用C语言char *初始化字符串
string* string_init_str(const char *str);

// 释放字符串分配的内存
void string_free(string *s);

// 重置字符串，将字符串清空，第一个字符设置为'\0'
void string_reset(string *s);

// 扩展字符串长度到new_len
void string_extend(string *s, size_t new_len);

// 拷贝字符串，str_len为拷贝的长度
int string_copy_len(string *s, const char *str, size_t str_len);

// 拷贝字符串
int string_copy(string *s, const char *str);

// 添加字符串s2到s末尾
int string_append_string(string *s, string *s2);

// 添加数字i到字符串末尾
int string_append_int(string *s, int i);

// 添加str到字符串s末尾，添加的长度为str_len
int string_append_len(string *s, const char *str, size_t str_len);

// 添加str到字符串s末尾
int string_append(string *s, const char *str);

// 添加字符ch到字符串s末尾
int string_append_ch(string *s, char ch);

#endif
