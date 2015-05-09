#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"


struct tree
{
    struct node * root;
    void (*free_func)(void *);
};

struct tree * construct_tree(void (*free_func)(void *))
{
    struct tree * t = (struct tree *)malloc(sizeof(struct tree));
    t->free_func = free_func;
    t->root = NULL;

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

void trinode_restructure(struct node * child, struct tree * t)
{
    bool grandparent_is_left;
    struct node * parent;
    struct node * grandparent;
    struct node * great_grandparent;
    struct node * brother;

    brother = get_sibling(child);
    parent = child->parent;
    grandparent = parent->parent;
    great_grandparent = grandparent->parent;
    grandparent_is_left = is_left(grandparent);

    if (is_left(child) && is_left(parent)) {

        set_left(grandparent, brother);
        set_right(parent, grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            set_left(great_grandparent, parent);
        } else if (great_grandparent != NULL) {
            set_right(great_grandparent, parent);
        } else if (grandparent == t->root) {
            t->root = parent;
            parent->parent = NULL;
        }

        parent->is_red = false;
        grandparent->is_red = true;

    } else if (is_right(child) && is_left(parent)) {

        set_right(parent, child->left);

        set_left(grandparent, child->right);

        set_left(child, parent);
        set_right(child, grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            set_left(great_grandparent, child);
        } else if (great_grandparent != NULL) {
            set_right(great_grandparent, child);
        } else if (grandparent == t->root) {
            t->root = child;
            child->parent = NULL;
        }

        child->is_red = false;
        grandparent->is_red = true;

    } else if (is_right(child) && is_right(parent)) {

        set_right(grandparent, brother);
        set_left(parent, grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            set_left(great_grandparent, parent);
        } else if (great_grandparent != NULL) {
            set_right(great_grandparent, parent);
        } else if (grandparent == t->root) {
            t->root = parent;
            parent->parent = NULL;
        }

        parent->is_red = false;
        grandparent->is_red = true;

    } else if (is_left(child) && is_right(parent)) {

        set_left(parent, child->right);

        set_right(grandparent, child->left);

        set_right(child, parent);
        set_left(child, grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            set_left(great_grandparent, child);
        } else if (great_grandparent != NULL) {
            set_right(great_grandparent, child);
        } else if (grandparent == t->root) {
            t->root = child;
            child->parent = NULL;
        }

        child->is_red = false;
        grandparent->is_red = true;

    }
}

void double_red(struct node * child, struct tree * t)
{
    struct node * parent;
    struct node * grandparent;
    struct node * great_grandparent;
    struct node * uncle;

    parent = child->parent;

    if(parent == NULL) {
        printf("Node's parent is NULL\n");
        exit(1);
    }

    grandparent = parent->parent;

    if(grandparent == NULL) {
        printf("Node's grandparent is NULL\n");
        exit(1);
    }

    uncle = get_sibling(parent);

    if(uncle == NULL || !uncle->is_red) {
        trinode_restructure(child, t);
        return;
    } else {
        parent->is_red = false;
        uncle->is_red = false;

        // Check that the grandparent is not NULL and not the
        // root node (parent is not NULL)
        if(grandparent != NULL && grandparent->parent != NULL) {
            grandparent->is_red = true;
            great_grandparent = grandparent->parent;

            if(great_grandparent != NULL && great_grandparent->is_red) {
                double_red(grandparent, t);
                return;
            }
        }
    }
}

void insert(long key, void * value, struct node * current_node, struct tree * t)
{
    struct node * new_node;

    if (key < current_node->key) {

        if (current_node->left != NULL) {
            insert(key, value, current_node->left, t);
        } else {
            new_node = construct_node(key, value);
            current_node->left = new_node;
            new_node->parent = current_node;

            if (current_node->is_red) {
                double_red(new_node, t);
                return;
            }
        }

    } else if (key > current_node->key) {

        if (current_node->right != NULL) {
            insert(key, value, current_node->right, t);
        } else {
            new_node = construct_node(key, value);
            current_node->right = new_node;
            new_node->parent = current_node;

            if (current_node->is_red) {
                double_red(new_node, t);
                return;
            }
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
        t->root->is_red = false;
        return;
    }

    insert(hash_key, value, t->root, t);
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
    free(t);
}
