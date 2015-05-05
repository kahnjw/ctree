#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"


struct tree
{
    struct node * root;
    void (*free_func)(void *);
};

struct tree construct_tree(void (*free_func)(void *))
{
    struct tree t;
    t.free_func = free_func;

    return t;
}

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

void insert(long key, void * value, struct node * current_node)
{
    struct node * new_node;

    if (key < current_node->key) {

        if (current_node->left != NULL) {
            insert(key, value, current_node->left);
        } else {
            new_node = construct_node(key, value);
            current_node->left = new_node;
            new_node->parent = current_node;
        }

    } else if (key > current_node->key) {

        if (current_node->right != NULL) {
            insert(key, value, current_node->right);
        } else {
            new_node = construct_node(key, value);
            current_node->right = new_node;
            new_node->parent = current_node;
        }

    } else if (key == current_node->key) {
        current_node->value = value;
    }
}

void set(const char * key, void * value, struct tree * t)
{
    long hash_key = hash_sdbm(key);

    if(t->root == NULL) {
        t->root = construct_node(hash_key, value);
        return;
    }

    insert(hash_key, value, t->root);
}

void * search(long key, struct node * n)
{
    if (n != NULL) {

        if (key == n->key) {
            return n->value;
        } else if (key < n->key) {
            return search(key, n->left);
        }

        return search(key, n->right);
    }

    return NULL;
}

void * get(const char * key, struct tree * t)
{
    long hash_key = hash_sdbm(key);

    return search(hash_key, t->root);
}

void delete(struct node * n, struct tree * t)
{
    if (n->left != NULL) {
        delete(n->left, t);
    }

    if (n->right != NULL) {
        delete(n->right, t);
    }

    if (n->value != NULL) {
        t->free_func(n->value);
        n->value = NULL;
    }

    free(n);
}

void delete_tree(struct tree * t)
{
    delete(t->root, t);
    t->root = NULL;
}
