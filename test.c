#define hsC_C
#include "hsC.h"

#include <stdio.h>


int timeTwo(int a) {
    return a*2;
}

bool isLessThen10(int a) {
    return a < 10;
}

bool isLessThen4(int a) {
    return a < 4;
}

int main(void) {

    int len = 10;

    puts ("iGen");
    int *gen = iGen(0,len);
    puts("iiMap");
    int *n = iiMap(&timeTwo,gen,len);
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

    puts("iDropWhile");
    res *b = iDropWhile(&isLessThen4,n,len);
    for(int i = 0; i < (b ->len); i++) {
        printf("%d\n",((int*)(b->res))[i]);
    }

    puts("iFind");
    maybe *a = iFind(20,gen,len);
    if(a->value == NOTHING) {
        puts("Value not found");
    }else{
        printf("%d\n", ((int*)(a->value)));
    }

    free(k);
    free(j);
    free(n);

    return 0;
}