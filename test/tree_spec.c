#include <stdlib.h>
#include <string.h>
#include "lib/check.h"
#include "../src/tree.h"


int main()
{
    describe("tree struct", {
        it("sets and gets items", {
            struct tree t;

            set("key0", "value0", &t);
            set("key1", "value1", &t);
            set("key2", "value2", &t);
            set("key3", "value3", &t);
            set("key4", "value4", &t);

            check(! strcmp(get("key0", &t), "value0"));
            check(! strcmp(get("key1", &t), "value1"));
            check(! strcmp(get("key2", &t), "value2"));
            check(! strcmp(get("key3", &t), "value3"));
            check(! strcmp(get("key4", &t), "value4"));

            delete_tree(&t);
        })
    });

    return 0;
}
