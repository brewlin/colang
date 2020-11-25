#include "Array.h"

int_t array_init(array_t *array, uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;

    array->elts = gc_malloc(n * size);
    if (array->elts == NULL) {
        return ERROR;
    }

    return OK;
}
array_t *array_create(uint_t n, size_t size)
{
    array_t *a;

    a = gc_malloc(sizeof(array_t));
    if (a == NULL) {
        printf("[arr_create] failed to create\n");
        return NULL;
    }

    if (array_init(a,  n, size) != OK) {
        printf("[arr_init] failed to init\n");
        return NULL;
    }

    return a;
}


void array_destroy(array_t *a)
{
    //TODO:释放array
    gc_free(a);
}


void *array_push(array_t *a)
{
    void        *elt, *new;
    size_t       size;

    if (a->nelts == a->nalloc) {

        // 数组满了
        size = a->size * a->nalloc;
        //直接扩充2倍大小
        new = gc_malloc(2 * size);
        if (new == NULL) {
            printf("[arr_pushn] failed to expand memeory\n");
            return NULL;
        }

        memcpy(new, a->elts, size);
        //手动释放之前决定不会用到的数组 降低gc压力
        gc_free(a->elts);
        a->elts = new;
        a->nalloc *= 2;
    }

    elt = (u_char *) a->elts + a->size * a->nelts;
    a->nelts++;
    return elt;
}


void *
array_push_n(array_t *a, uint_t n)
{
    void        *elt, *new;
    size_t       size;
    uint_t   nalloc;

    size = n * a->size;

    if (a->nelts + n > a->nalloc) {
        //数组满了

        nalloc = 2 * ((n >= a->nalloc) ? n : a->nalloc);

        new = gc_malloc(nalloc * a->size);
        if (new == NULL) {
            printf("[arr_pushn] failed to expand memeory");
            return NULL;
        }
        memcpy(new, a->elts, a->nelts * a->size);
        //手动释放拷贝前的数组降低gc压力
        gc_free(a->elts);
        a->elts = new;
        a->nalloc = nalloc;
    }
    elt = (u_char *) a->elts + a->size * a->nelts;
    a->nelts += n;

    return elt;
}
