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
#include "String.h"
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
Value* member_find(rbtree_t* rbtree, Value* key){
    rbtree_node_t  *node, *sentinel;

    rbtree_key_int_t hk = 0;
    switch (key->type){
        case Bool:
        case Int:
        case Double:
            hk = (rbtree_key_int_t)key->data;break;
        case String:
            hk = hash_key(key->data,stringlen(key->data));
            break;
    }
    node = rbtree->root;
    sentinel = rbtree->sentinel;

    while (node != sentinel) {

        if (hk != node->key) {
            node = (hk < node->key) ? node->left : node->right;
            continue;
        }
        if(node->k->type == key->type){
            return node->v;
        }
    }
    return NULL;
}
void member_insert(rbtree_t* tree, Value* key,Value* value)
{

    rbtree_node_t* node = gc_malloc(sizeof(rbtree_node_t));
    rbtree_key_int_t hk = 0;
    switch(key->type){
        case Bool:
        case Int:
        case Double:
            hk = (rbtree_key_int_t)key->data;break;
        case String:
            hk = hash_key(key->data,stringlen(key->data));
    }
    node->key   = hk;
    node->k     = key;
    node->v     = value;
    rbtree_insert(tree,node);
}
/**
 * @param size
 * @return
 */
Class* object_create(int size){
    Class* c = gc_malloc(sizeof(Class));
    if (c == NULL) {
        printf("[object_create] failed to create\n");
        return NULL;
    }

    rbtree_t      *members          = gc_malloc(sizeof(rbtree_t));
    rbtree_node_t *members_sentinel = gc_malloc(sizeof(rbtree_node_t));
    rbtree_init(members,members_sentinel,member_insert_or_update);

    rbtree_t      *funcs            = gc_malloc(sizeof(rbtree_t));
    rbtree_node_t *funcs_sentinel   = gc_malloc(sizeof(rbtree_node_t));
    rbtree_init(funcs,funcs_sentinel,member_insert_or_update);

    c->members = members;
    c->funcs   = funcs;

    return c;
}

Value* object_member_update(Value* object,uint_t k,Value* v){

    Value* key = newobject(Int,k);
    Class* c   = object->data;
    member_insert(c->members,key,v);
}
Value* object_member_get(Value* object, uint_t k){
    Value* key = newobject(Int,k);
    Class* c   = object->data;
    Value* value = member_find(c->members,key);
    if(value == NULL){
        printf("object_get] not find the memeber:%d value\n",key);
        return newobject(Null,0);
    }
    return value;
}
void object_unary_operator(int opt,Value* object,uint_t k,Value* value){
    if( !object || !value ){
        printf(" [object-uop] probably wrong at there! object:%p rhs:%p\n",object,value);
        return NULL;
    }
    Value* key = object_member_get(object,k);
    Value* ret = operator_switch(opt,key,value);
    object_member_update(object,k,ret);
}
void object_func_add(Value* object,uint_t k,void* addr){

    Value* key = newobject(Int,k);
    Class* c   = object->data;
    member_insert(c->funcs,key,addr);
}
void* object_func_addr(Value* object,uint_t k){
    Value* key = newobject(Int,k);
    Class* c   = object->data;
    void* func = member_find(c->funcs,key);
    if(func == NULL){
        printf("[object-func] func not exist\n");
    }
    return func;
}


