#define hsC_C
#include "hsC.h"

#include <stdio.h>


int timeTwo(int a) {
    return a*2;
}

bool isLessThen10(int a) {
    return a < 10;
}

int main(void) {

    int len = 10;

    puts("iiMap");
    int *n = iiMap(&timeTwo,iGen(0,len),len);
    for(int i = 0; i < len; i++) {
        printf("%d\n",n[i]);
    }
    puts("iTake");
    int *j = iTake(3,n,len);
    for(int i = 0; i < 3; i++) {
        printf("%d\n",j[i]);
    }
    puts("iTakeWhile");

    res *k = iTakeWhile(&isLessThen10,n,len);
    for(int i = 0; i < (k ->len); i++) {
        printf("%d\n",((int*)(k->res))[i]);
    }
    free(k);
    free(j);
    free(n);

    return 0;
}