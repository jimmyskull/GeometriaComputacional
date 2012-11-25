#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <stdint.h>

struct rbtree {
    struct rbtree *parent, *lchild, *rchild;
    const Point *value;
    uint8_t color;
};

enum RBTREE_WALKORDER {
	WALK_INORDER,
	WALK_PREORDER,
	WALK_POSORDER
};

typedef void (*walk_fn_t)(const struct rbtree *);

extern struct rbtree *rbtree_search(struct rbtree *, const Point *);
extern struct rbtree *rbtree_min(struct rbtree *);
extern struct rbtree *rbtree_max(struct rbtree *);
extern struct rbtree *rbtree_successor(struct rbtree *);
extern struct rbtree *rbtree_predecessor(struct rbtree *);
extern struct rbtree *rbtree_new(void);
extern void rbtree_free(struct rbtree *);
extern void rbtree_insert(struct rbtree **, const Point *);
extern void rbtree_delete(struct rbtree **, const Point *);
extern void rbtree_walk(struct rbtree *, const walk_fn_t,
    const enum RBTREE_WALKORDER);

#endif

