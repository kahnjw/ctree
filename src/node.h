#include <errno.h>
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

void log_error(char * msg, int _errno)
{
    fprintf(stderr, "ERRNO %d: %s\n", _errno, msg);
}

struct node * construct_node(long key, void * value)
{
    struct node * n =  (struct node*) malloc(sizeof(struct node));

    /* Most likely ENOMEM; save program from segfaulting. */
    if (n == NULL) {
        int local_err = errno;
        log_error("Unable to allocate memory in construct_node()", local_err);

        return NULL;
    }

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

void set_left(struct node * n, struct node *left)
{
    n->left = left;

    if (left != NULL) {
        left->parent = n;
    }
}

void set_right(struct node * n, struct node *right)
{
    n->right = right;

    if (right != NULL) {
        right->parent = n;
    }
}
