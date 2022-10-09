#include "../hsC.h"
#include <stdio.h>

bool isEven(int a) {
    return a % 2 == 0;
}

int main(void) {

    int *intList = NULL;
    gen(1,20,int,1,intList);
    res *ma = NULL;
    filter(isEven,intList,20,int,ma);
    for(int i = 0; i < ma->len; i++) {
        printf("%d\n",((int*)ma->res)[i]);
    }

    return 0;
}

