#define hsC_C

#include "../hsC.h"
#include <stdio.h>
#include <ctype.h>

int main(void) {

    int *intList = NULL;
    gen(0,10,int,1,intList);
    maybe *m = NULL;
    find(9,intList,10,int,m);
    if(m->value == NOTHING) {
        puts("Value not found");
    }else{
        printf("Value found: %d",((int*)m->value)[0]);
    }



    return 0;
}

