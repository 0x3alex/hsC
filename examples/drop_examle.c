#define hsC_C

#include "../hsC.h"
#include <stdio.h>


bool isLessThen10(int a) {
    return a <= 10;
}

int main(void) {

    int *intList = NULL;
    gen(1,20,int,1,intList);
    int *ma = NULL;
    drop(5,intList,20,int,ma);
    for(int i = 0; i < 15; i++) {
        printf("%d\n",ma[i]);
    }

    gen(1,20,int,1,intList);
    res *re = NULL;
    dropWhile(isLessThen10,intList,20,int,re);
    for(int i = 0; i < re->len; i++) {
        printf("%d\n",((int*)re->res)[i]);
    }

    return 0;
}

