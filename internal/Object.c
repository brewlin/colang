/**
 *@ClassName Object
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/7 0007 下午 5:54
 *@Version 1.0
 **/

#include "Object.h"
#include "Value.h"
#include "Map.h"
#include "string.h"
#include "gcmalloc.h"
/**
 * @param size
 * @return
 */
rbtree_t* object_create(int size){
    rbtree_t *obj = map_create();
    if (obj == NULL) {
        printf("[object_create] failed to create\n");
        return NULL;
    }
    return obj;
}
Value* object_member_update(Value* object,char* name,Value* v){

    Value* key = newobject(String,name);

    map_insert(object,name,v);
}
Value* object_member_get(Value* object, char* name){
    Value* key = newobject(String,name);

    Value* value = map_find(object,key);
    if(value == NULL){
        printf("object_get] not find the memeber:%s value\n",name);
        return newobject(Null,0);
    }
    return value;
}
void object_operator(int opt,Value* object,uint_t k,Value* value){
    if( !object || !value ){
        printf(" [object-op] probably wrong at there! object:%p rhs:%p\n",object,value);
        return NULL;
    }
    Value* ret;
    Value* key = newobject(Int,k);
    switch (opt){
        case TK_ASSIGN:
            map_insert(object,key,value);
            break;
//        case TK_PLUS_AGN:
//            ret = value_plus(*(Value**)lhs,rhs);break;
//        case TK_MINUS_AGN:
//            ret = value_minus(*(Value**)lhs,rhs);break;
//        case TK_MUL_AGN:
//            ret = value_mul(*(Value**)lhs,rhs);break;
//        case TK_DIV_AGN:
//            ret = value_div(*(Value**)lhs,rhs);break;
//        case TK_BITAND_AGN:
//            ret = value_bitand(*(Value**)lhs,rhs);break;
//        case TK_BITOR_AGN:
//            ret = value_bitor(*(Value**)lhs,rhs);break;
//        case TK_SHIFTL_AGN:
//            ret = value_shift_left(*(Value**)lhs,rhs);break;
//        case TK_SHIFTR_AGN:
//            ret = value_shift_right(*(Value**)lhs,rhs);break;
        default:
            printf(" [obj-unary-op] unkown op:%d\n",opt);
//            ret = rhs;
    }
    // assign =
//    *(Value**)lhs = ret;

}
