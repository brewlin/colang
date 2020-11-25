
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

typedef struct {
    void     *elts;
    uint_t   nelts;
    size_t   size;
    uint_t   nalloc;
} array_t;


array_t *array_create(uint_t n, size_t size);
void array_destroy(array_t *a);
void *array_push(array_t *a);
void *array_push_n(array_t *a, uint_t n);

#endif /* _ARRAY_H_INCLUDED_ */
