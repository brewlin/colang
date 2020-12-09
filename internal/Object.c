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

void member_insert_or_update(rbtree_node_t *temp, rbtree_node_t *node,rbtree_node_t *sentinel)
{
    rbtree_node_t  **p;

    for ( ;; ) {

        if(node->key == temp->key){
            temp->v = node->v;
        }
        p = (node->key < temp->key) ? &temp->left : &temp->right;

        if (*p == sentinel) {
            break;
        }

        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    rbt_red(node);
}
/**
 * @param size
 * @return
 */
rbtree_t* object_create(int size){
    rbtree_t      *tree     = gc_malloc(sizeof(rbtree_t));
    rbtree_node_t *sentinel = gc_malloc(sizeof(rbtree_node_t));
    rbtree_init(tree,sentinel,member_insert_or_update);

    if (tree == NULL) {
        printf("[object_create] failed to create\n");
        return NULL;
    }
    return tree;
}
Value* object_member_update(Value* object,uint_t k,Value* v){

    Value* key = newobject(Int,k);

    map_insert(object,key,v);
}
Value* object_member_get(Value* object, uint_t k){
    Value* key = newobject(Int,k);

    Value* value = map_find(object,key);
    if(value == NULL){
        printf("object_get] not find the memeber:%d value\n",key);
        return newobject(Null,0);
    }
    return value;
}
void object_operator(int opt,Value* object,uint_t k,Value* value){
    if( !object || !value ){
        printf(" [object-op] probably wrong at there! object:%p rhs:%p\n",object,value);
        return NULL;
    }
    Value* key = object_member_get(object,k);
    Value* ret = unary_operator_switch(opt,key,value);
    object_member_update(object,k,ret);
}
