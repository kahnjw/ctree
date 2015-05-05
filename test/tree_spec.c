#include <stdlib.h>
#include <string.h>
#include "lib/helpers.h"
#include "lib/check.h"
#include "../src/tree.h"


int main()
{
    describe("tree struct", {
        it("gets nodes from a large tree", {
            struct tree * t = construct_tree(&free);
            int i;
            char * buffer;

            for (i = 0; i < 1000; i++) {
                buffer = (char *)malloc(4);
                tostring(buffer, i);
                set(buffer, buffer, t);
            }

            tostring(buffer, 999);
            str_eq(get(buffer, t), buffer);

            tostring(buffer, 567);
            str_eq(get(buffer, t), buffer);

            tostring(buffer, 876);
            str_eq(get(buffer, t), buffer);

            tostring(buffer, 123);
            str_eq(get(buffer, t), buffer);

            delete_tree(t);
        });
    });

    return 0;
}
