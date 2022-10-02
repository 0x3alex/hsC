#define hsC_C
#include "hsC.h"

#include <stdio.h>


int timeTwo(int a) {
    return a*2;
}

bool isSix(int a) {
    return a == 6;
}

int main(void) {

    int l = 3;
    int a[l];
    
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    int *n = mapIntToInt(&timeTwo,a,l);

    for(int i = 0; i < l; i++) {
        printf("%d\n",n[i]);
    }

    return 0;
}