#define hsC_C

#include "../hsC.h"
#include <stdio.h>

int main(void) {

    char *test = "hello world";
    res *r = words(test,13);
    for(int i = 0; i < r->len; i++) {
        printf("%s\n",((char**)r->res)[i]);
    }

    return 0;
}

