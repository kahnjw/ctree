#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node
{
    long key;
    void * value;
    struct node * left;
    struct node * right;
    struct node * parent;
};

long hash_sdbm(const char * str)
{
    long hash = 0;
    int c;

    /* Move through the char * bit by bit, scramble hash
     * and add it to the accumulated hash value.
     */
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

struct node * construct_node(const char * key, void * value)
{
    struct node * n =  (struct node*) malloc(sizeof(struct node));
    long hashed_key = hash_sdbm(key);

    n->key = hashed_key;
    n->value = value;

    return n;
}

bool is_left(struct node * n)
{
    struct node * parent;
    struct node * left;

    parent = n->parent;

    if (parent == NULL) {
        return false;
    }

    left = parent->left;

    return n == left;
}

struct node * get_sibling(struct node * n)
{
    struct node * parent;

    parent = n->parent;

    if (parent == NULL) {
        return NULL;
    }

    if(is_left(n)) {
        return parent->right;
    }

    return parent->left;
}

