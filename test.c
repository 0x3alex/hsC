#define hsC_C
#include "hsC.h"

#include <ctype.h>

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

int charToInt(char c) {
    return (int) c;
}


int main(void) {

    char *l = strGen('A','Z');
    int *l1 = MapCharToInt(&charToInt,l,(95-65));
    int *l2 = MapIntToInt(&tolower,l1,(95-65));

    for(int i = 0; i < (95-65); i++) {
        printf("%c\n",l2[i]);
    }
    return 0;
}