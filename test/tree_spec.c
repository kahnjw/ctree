#include <stdlib.h>
#include <string.h>
#include "lib/check.h"
#include "../src/tree.h"

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main()
{
    describe("tree struct", {
        it("gets nodes from a large tree", {
            struct tree t;
            int i;
            char * buffer = (char *)malloc(4);

            for (i = 0; i < 1000; i++) {
                tostring(buffer, i);
                set(buffer, buffer, &t);
            }

            tostring(buffer, 999);
            str_eq(get(buffer, &t), buffer);

            tostring(buffer, 567);
            str_eq(get(buffer, &t), buffer);

            tostring(buffer, 876);
            str_eq(get(buffer, &t), buffer);

            tostring(buffer, 123);
            str_eq(get(buffer, &t), buffer);

            free(buffer);
        });
    });

    return 0;
}
