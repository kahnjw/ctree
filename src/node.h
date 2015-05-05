#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>

struct node
{
    long key;
    void * value;
    struct node * left;
    struct node * right;
    struct node * parent;
    bool is_red;
};

struct node * construct_node(long key, void * value)
{
    struct node * n =  (struct node*) malloc(sizeof(struct node));

    n->key = key;
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->is_red = true;

    return n;
}

bool is_left(struct node * n)
{
    if (n == NULL || n->parent == NULL) {
        return false;
    }

    return n == n->parent->left;
}

bool is_right(struct node * n)
{
    if (n == NULL || n->parent == NULL) {
        return false;
    }

    return n == n->parent->right;
}

struct node * get_sibling(struct node * n)
{
    if (n->parent == NULL) {
        return NULL;
    }

    if(is_left(n)) {
        return n->parent->right;
    }

    return n->parent->left;
}

