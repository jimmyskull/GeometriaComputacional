#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "rbtree.h"

#define RB_RED      0
#define RB_BLACK    1
#define color(node)    (node != NULL?  node->color:  RB_BLACK)

static struct rbtree *rbtree_new_node(const Point *value)
{
    struct rbtree *node;

    node = malloc(sizeof(struct rbtree));
    if (node == NULL) {
        fprintf(stderr, "Sem memória para novo nó.\n");
        return NULL;
    }
    node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    node->value = value;
    node->color = RB_RED;
    return node;
}

/* Retorna o nó de um ponto. */
struct rbtree *rbtree_search(struct rbtree *tree, 
    const Point *value)
{
    int cmp;

    while (tree != NULL && (cmp = pointcmp(*value, *tree->value)) != 0)
        tree = cmp < 0? tree->lchild: tree->rchild;
    return tree;
}

struct rbtree *rbtree_min(struct rbtree *tree)
{
    if (tree != NULL && tree->lchild != NULL)
        return rbtree_min(tree->lchild);
    return tree;
}

struct rbtree *rbtree_max(struct rbtree *tree)
{
    if (tree != NULL && tree->rchild != NULL)
        return rbtree_max(tree->rchild);
    return tree;
}

#ifndef NDEBUG
/* Will not admit duplicate values in rbtree */
static void rbtree_test(struct rbtree *ptree)
{
    if (ptree == NULL)
        return;
    if (ptree->parent != NULL) {
        struct rbtree *parent = ptree->parent;
        int left_child = parent->lchild == ptree;
        int right_child = parent->rchild == ptree;
        
        assert(left_child || right_child);
        assert(left_child != right_child);
    }
    if (ptree->lchild != NULL) {
        rbtree_test(ptree->lchild);
        assert(pointcmp(*rbtree_max(ptree->lchild)->value, *ptree->value) < 0);
    }
    if (ptree->rchild != NULL) {
        rbtree_test(ptree->rchild);
        assert(pointcmp(*rbtree_max(ptree->rchild)->value, *ptree->value) > 0);
    }
}
#else
#    define rbtree_test(p)
#endif

struct rbtree *rbtree_successor(struct rbtree *tree)
{
    struct rbtree *parent = tree->parent;

    if (tree->rchild != NULL)
        return rbtree_min(tree->rchild);
    while (parent != NULL && tree == parent->rchild)
        parent = (tree = parent)->parent;
    return parent;
}

struct rbtree *rbtree_predecessor(struct rbtree *tree)
{
    struct rbtree *parent = tree->parent;

    if (tree->lchild != NULL)
        return rbtree_max(tree->lchild);
    while (parent != NULL && tree == parent->lchild)
        parent = (tree = parent)->parent;
    return parent;
}

struct rbtree *rbtree_new(void)
{
    return NULL;
}

void rbtree_free(struct rbtree *tree)
{
    if (tree == NULL)
        return;
    rbtree_free(tree->lchild);
    rbtree_free(tree->rchild);
    free(tree);
}

static void rbtree_left_rotate(struct rbtree **tree, struct rbtree *node)
{
    struct rbtree *y = node->rchild, *parent;

    node->rchild = y->lchild;
    if (y->lchild != NULL)
        y->lchild->parent = node;
    y->parent = node->parent;
    parent = node->parent;
    if (parent == NULL)
        *tree = y;
    else
        if (node == parent->lchild)
            parent->lchild = y;
        else
            parent->rchild = y;
    y->lchild = node;
    node->parent = y;
}

static void rbtree_right_rotate(struct rbtree **tree, struct rbtree *node)
{
    struct rbtree *y = node->lchild, *parent;

    assert(node != NULL);
    assert(y != NULL);
    node->lchild = y->rchild;
    if (y->rchild != NULL)
        y->rchild->parent = node;
    y->parent = node->parent;
    parent = node->parent;
    if (parent == NULL)
        *tree = y;
    else
        if (node == parent->rchild)
            parent->rchild = y;
        else
            parent->lchild = y;
    y->rchild = node;
    node->parent = y;
}

/* Fix the tree after insertion of node 'node'. */
static void rbtree_insert_fixup(struct rbtree **tree, struct rbtree *node)
{
    struct rbtree *parent = node->parent;
    struct rbtree *y, *grandparent;

    while (color(parent) == RB_RED) {
        grandparent = parent->parent;
        if (parent == grandparent->lchild) {
            y = grandparent->rchild;
            if (color(y) == RB_RED) {
                parent->color = RB_BLACK;
                y->color = RB_BLACK;
                grandparent->color = RB_RED;
                node = grandparent;
            } else {
                if (node == parent->rchild) {
                    node = parent;
                    rbtree_left_rotate(tree, node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }
                parent->color = RB_BLACK;
                grandparent->color = RB_RED;
                rbtree_right_rotate(tree, grandparent);
            }
        } else { /* parent == grandparent->rchild */
            y = grandparent->lchild;
            if (color(y) == RB_RED) {
                parent->color = RB_BLACK;
                y->color = RB_BLACK;
                grandparent->color = RB_RED;
                node = grandparent;
            } else {
                if (node == parent->lchild) {
                    node = parent;
                    rbtree_left_rotate(tree, node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }
                parent->color = RB_BLACK;
                grandparent->color = RB_RED;
                rbtree_right_rotate(tree, grandparent);
            }    
        }
        parent = node->parent;
    }
    (*tree)->color = RB_BLACK;
}

/* Insert a value in the rbtree */
void rbtree_insert(struct rbtree **tree, const Point *value)
{
    struct rbtree *prev = NULL, *bst = *tree,
                  *node = rbtree_new_node(value);

    while (bst != NULL) {
        prev = bst;
        bst = pointcmp(*value, *bst->value) < 0?  bst->lchild:  bst->rchild;
    }
    node->parent = prev;
    if (prev == NULL)
        *tree = node;        /* The rbtree is empty. */
    else
        if (pointcmp(*value, *prev->value) < 0)
            prev->lchild = node;
        else
            prev->rchild = node;
    rbtree_insert_fixup(tree, node);
    rbtree_test(*tree);
}

/*
 * If the node has only one child, this child will be child of the
 * parent node, else will be found the successor node of node. 
 * Returns which node will be removed.
 */
static struct rbtree *rbtree_which_node(struct rbtree *node)
{
    if (node->lchild == NULL || node->rchild == NULL)
        return node;
    return rbtree_successor(node);
}

/* Select which node switch with node. */
static struct rbtree *rbtree_which_son_node(struct rbtree *node)
{
    return node->lchild != NULL?  node->lchild:  node->rchild;
}

/*
 * Updates the connection of parent with new child.
 * If the node to be removed is the root, update the rbtree's root.
 * Else will be updated the son, depending whether the node to be removed
 * is on left or right of parent node.
 */
static void rbtree_update_father_node(struct rbtree **ptree, 
    struct rbtree *node, struct rbtree *new_son)
{
    struct rbtree *pai = node->parent;

    if (node->parent == NULL)
        *ptree = new_son;
    else
        if (node == pai->lchild)
            pai->lchild = new_son;
        else
            pai->rchild = new_son;
}

/*
 * Delete a rbtree's node
 * Finds the y node to be removed and its x child that will be the new
 * child of y's parent.  There's a case that y node isn't the node within
 * value to be removed.  In this case, y node is a leaf and its value
 * should be switched with the real node to be removed.
 */
void rbtree_delete(struct rbtree **tree, const Point *value)
{
    struct rbtree *node, *y, *x;

    if (*tree == NULL) {
        fprintf(stderr, "Empty rbtree.\n");
        return;
    }
    node = rbtree_search(*tree, value);
    if (node == NULL) {
        fprintf(stderr, "Node '%p' was not found.\n", value);
        return;
    }
    y = rbtree_which_node(node);
    x = rbtree_which_son_node(y);
    if (x != NULL)
        x->parent = y->parent;
    rbtree_update_father_node(tree, y, x);
    if (y != node)
        node->value = y->value;
    free(y);
    rbtree_test(*tree);
}

void rbtree_walk(struct rbtree *tree, const walk_fn_t callback,
    const enum RBTREE_WALKORDER worder)
{
    if (tree != NULL) {
        struct rbtree *node = tree;

        if (worder == WALK_PREORDER)
            callback(node);
            
        rbtree_walk(node->lchild, callback, worder);
        
        if (worder == WALK_INORDER)
            callback(node);
            
        rbtree_walk(node->rchild, callback, worder);
        
        if (worder == WALK_POSORDER)
            callback(node);
    }
}

