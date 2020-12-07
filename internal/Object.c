/**
 *@ClassName Object
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/7 0007 下午 5:54
 *@Version 1.0
 **/

#include "Object.h"
#include "Value.h"
/**
 * @param size
 * @return
 */
array_t* object_create(int size){
    array_t *obj;

    obj = gc_malloc(sizeof(array_t));
    if (obj == NULL) {
        printf("[object_create] failed to create\n");
        return NULL;
    }

    if (array_init(obj,  size, sizeof(Value*)) != OK) {
        printf("[object_init] failed to init\n");
        return NULL;
    }

    return obj;
}
