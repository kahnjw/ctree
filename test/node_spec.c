#include <stdlib.h>
#include <string.h>
#include "lib/check.h"
#include "../src/node.h"

int main()
{
    describe("node struct", {
        it("constructs nodes", {
            struct node * n = construct_node(123, "value");
            check(! strcmp((char *)n->value, "value"));

            free(n);
        });

        it("can tell if it is the left node", {
            struct node * parent = construct_node(123, "value");
            struct node * left = construct_node(123, "value");

            parent->left = left;

            left->parent = parent;

            check(is_left(left));
            check(! is_right(left));

            free(parent);
            free(left);
        });

        it("can tell if it is the right node", {
            struct node * parent = construct_node(123, "value");
            struct node * right = construct_node(123, "value");

            parent->right = right;

            right->parent = parent;

            check(is_right(right));
            check(! is_left(right));

            free(parent);
            free(right);
        });

        it("gets node siblings", {
            struct node * parent = construct_node(123, "value");
            struct node * left = construct_node(123, "value");
            struct node * right = construct_node(123, "value");

            parent->left = left;
            parent->right = right;

            left->parent = parent;
            right->parent = parent;

            check(get_sibling(left) == right);

            free(parent);
            free(right);
            free(left);
        });
    });

    return 0;
}
