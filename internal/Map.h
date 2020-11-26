#ifndef _RBTREE_H_INCLUDED_
#define _RBTREE_H_INCLUDED_

#include "Value.h"

typedef u_int          rbtree_key_t;
typedef int            rbtree_key_int_t;

typedef struct rbtree_node_s  rbtree_node_t;

struct rbtree_node_s {
    rbtree_key_t       key;
    rbtree_node_t     *left;
    rbtree_node_t     *right;
    rbtree_node_t     *parent;
    Value             *value;
    u_char             color;
};


typedef struct rbtree_s  rbtree_t;

typedef void (*rbtree_insert_pt) (rbtree_node_t *root,rbtree_node_t *node, rbtree_node_t *sentinel);

struct rbtree_s {
    rbtree_node_t     *root;
    rbtree_node_t     *sentinel;
    rbtree_insert_pt  insert;
};


#define rbtree_init(tree, s, i)                                           \
    rbtree_sentinel_init(s);                                              \
    (tree)->root = s;                                                         \
    (tree)->sentinel = s;                                                     \
    (tree)->insert = i


#define   hash(key, c)   ((u_int) key * 31 + c)
u_int     hash_key(u_char *data, size_t len);
rbtree_t* map_create();
void      map_insert(rbtree_t *tree, Value* value);
Value*    map_find(rbtree_t *rbtree, Value* key);


void rbtree_insert(rbtree_t *tree, rbtree_node_t *node);
void rbtree_delete(rbtree_t *tree, rbtree_node_t *node);
void rbtree_insert_value(rbtree_node_t *root, rbtree_node_t *node, rbtree_node_t *sentinel);
void rbtree_insert_timer_value(rbtree_node_t *root,rbtree_node_t *node, rbtree_node_t *sentinel);
rbtree_node_t *rbtree_next(rbtree_t *tree,rbtree_node_t *node);


#define rbt_red(node)               ((node)->color = 1)
#define rbt_black(node)             ((node)->color = 0)
#define rbt_is_red(node)            ((node)->color)
#define rbt_is_black(node)          (!rbt_is_red(node))
#define rbt_copy_color(n1, n2)      (n1->color = n2->color)


/* a sentinel must be black */

#define rbtree_sentinel_init(node)  rbt_black(node)


static inline rbtree_node_t *
rbtree_min(rbtree_node_t *node, rbtree_node_t *sentinel)
{
    while (node->left != sentinel) {
        node = node->left;
    }

    return node;
}


#endif /* _RBTREE_H_INCLUDED_ */
