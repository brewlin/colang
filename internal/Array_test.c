#include "String.h"
#include <stdio.h>
#include "help.h"
#include "limits.h"
#include "Array.h"
#include "Value.h"
#include "gcmalloc.h"

void test_array()
{
    //create check
    array_t* arr = array_create(8, sizeof(Value*));
    assert_s("array_create() 8 size",arr != NULL && arr->elts != NULL && arr->nalloc == 8)

    Value** v1;
    Value** tmp;

    //push check
    for (int j = 0; j < 8; ++j) {
        v1 = newobject(Int,j);
        tmp = array_push(arr);
        assert_s("array_push(int)",tmp != NULL);
        assert_s("array_push(int) size -= 1",arr->nelts == j+1);
        *tmp = v1;
    }
    // value check
    Value** var = arr->elts;
    for (int k = 0; k < 8; ++k) {
        assert_s("array check ", (long)var[k]->data == k)
    }

    tmp = array_push(arr);
    assert_s("array_push() auto expand",arr->nalloc == 16);

    arr = array_create(2, sizeof(Value*));
    assert_s("array_create() 2 size",arr->nalloc == 2);
    v1 = newobject(String,"test");
    tmp = array_push(arr);
    *tmp = v1;
    var = arr->elts;
    assert_s("array_push() string == test",memcmp(var[0]->data,"test",4) == 0)

}
