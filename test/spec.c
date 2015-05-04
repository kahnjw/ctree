#include "lib/check.h"
#include <stdlib.h>
#include <string.h>
#include "../src/node.h"

int main()
{
    describe("tree", {
        describe("node structure", {
            it("constructs nodes", {
                struct node * n = construct_node("key", "value");
                check(! strcmp((char *)n->value, "value"));

                free(n);
            });

            it("gets node siblings", {
                struct node * parent = construct_node("key", "value");
                struct node * left = construct_node("key", "value");
                struct node * right = construct_node("key", "value");

                parent->left = left;
                parent->right = right;

                left->parent = parent;
                right->parent = parent;

                check(get_sibling(left) == right);
            });
        });    
    });

    return 0;
}
