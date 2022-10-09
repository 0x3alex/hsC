#define HSC_STR

#include "../hsC.h"
#include <stdio.h>

bool isNotSpace(char a) {
    return a != ' ';
}

int main(void) {

    char *test = "hello world how are you ?";
    res *r = splitAt(test,13,isNotSpace,' ');
    for(int i = 0; i < r->len; i++) {
        printf("%s\n",((char**)r->res)[i]);
    }

    return 0;
}

