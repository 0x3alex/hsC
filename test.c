#define hsC_C
#include "hsC.h"

#include <stdio.h>

bool IsMod2(int a) {
    return a % 2 == 0;
}

int times3(int a) {
    return a*3;
}

bool lessThan30(int a) {
    return a <= 30;
}

bool lessThan50(int a) {
    return a <= 50;
}

int main(void) {

    char *list = strGen('a','z');
    while(*list != 'z') {
        printf("%c\n",*list++);
    }
    return 0;
}