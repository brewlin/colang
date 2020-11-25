
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _ARRAY_H_INCLUDED_
#define _ARRAY_H_INCLUDED_

#include "Value.h"
#include <string.h>

typedef int  int_t;
#define ushort_t  u_short
#define uint_t    u_int
#define ARRAY_SIZE 8

typedef struct {
    void     *addr;
    uint_t   used;
    size_t   size;
    uint_t   total;
} array_t;


void   arr_pushone(Value* varr,Value* var);
void   arr_updateone(Value* varr,Value* index,Value* var);
Value* arr_get(Value* varr,Value* index);


array_t *array_create(uint_t n, size_t size);
void array_destroy(array_t *a);
void *array_push(array_t *a);
void *array_push_n(array_t *a, uint_t n);

#endif /* _ARRAY_H_INCLUDED_ */
