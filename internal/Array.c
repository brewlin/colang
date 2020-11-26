#include "Array.h"
#include "Value.h"
#include "String.h"
#include "gcmalloc.h"

Value* arr_get(Value* varr,Value* index){
    if(!varr || !varr->data || !index){
        printf("[arr_get] arr or index is null ,probably something wrong\n");
        return NULL;
    }
    array_t *arr = (array_t*)varr->data;
    //计算索引
    int i = 0;
    switch(index->type){
        case Int:
        case Double:
            i = (long)index->data;
            break;
        case String:
            i = stringlen(index->data);
    }
    if(i >= arr->used){
        printf("[arr_get] index is over the max size,return null now!\n");
        return newobject(Null,0);
    }

    Value** var = arr->addr;
    return var[i];
}
void arr_pushone(Value* varr,Value* var){
    if(!varr || !varr->data ||  !var){
        printf("[arr_pushone] arr or var is null ,probably something wrong\n");
        return;
    }
    array_t* arr = (array_t*)varr->data;
    Value** insert = array_push(arr);
    *insert = var;
}
void arr_updateone(Value* varr,Value* index,Value* var){
    if(!varr || !varr->data || !index || !var){
        printf("[arr_updateone] arr or var or index is null ,probably something wrong\n");
        return;
    }
    array_t *arr = (array_t*)varr->data;
    //计算索引
    int i = 0;
    switch(index->type){
        case Int:
        case Double:
            i = (long)index->data;
            break;
        case String:
            i = stringlen(index->data);
    }
    //TODO:如果索引超出了 当前array的范围则需要扩充
    if(i >= arr->used){
        printf("[arr_updateone] index is over the max size\n");
        return;
    }
    Value** array = arr->addr;
    array[i]      = var;
}

int_t array_init(array_t *array, uint_t n, size_t size)
{
    array->used = 0;
    array->size = size;
    array->total = n;

    array->addr = gc_malloc(n * size);
    if (array->addr == NULL) {
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

    if (a->used == a->total) {

        // 数组满了
        size = a->size * a->total;
        //直接扩充2倍大小
        new = gc_malloc(2 * size);
        if (new == NULL) {
            printf("[arr_pushn] failed to expand memeory\n");
            return NULL;
        }

        memcpy(new, a->addr, size);
        //手动释放之前决定不会用到的数组 降低gc压力
        gc_free(a->addr);
        a->addr = new;
        a->total *= 2;
    }

    elt = (u_char *) a->addr + a->size * a->used;
    a->used++;
    return elt;
}


void *
array_push_n(array_t *a, uint_t n)
{
    void        *elt, *new;
    size_t       size;
    uint_t   total;

    size = n * a->size;

    if (a->used + n > a->total) {
        //数组满了

        total = 2 * ((n >= a->total) ? n : a->total);

        new = gc_malloc(total * a->size);
        if (new == NULL) {
            printf("[arr_pushn] failed to expand memeory");
            return NULL;
        }
        memcpy(new, a->addr, a->used * a->size);
        //手动释放拷贝前的数组降低gc压力
        gc_free(a->addr);
        a->addr = new;
        a->total = total;
    }
    elt = (u_char *) a->addr + a->size * a->used;
    a->used += n;

    return elt;
}
