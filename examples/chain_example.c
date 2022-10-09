#include "../hsC.h"
#include <stdio.h>

int f1(int a) {
    return a+2;
}

int f2(int a) {
    return a -1;
}

int f3(int a) {
    return a*2;
}

int main(void) {

    int *intList = NULL;
    gen(0,10,int,2,intList);

    int(*fp[3])(int) = {f1,f2,f3};
    int *m = NULL;
    chain(intList,5,fp,3,int,m);
    for(int i = 0; i < 5; i++) {
        printf("%d\n",m[i]);
    }

    

    return 0;
}

