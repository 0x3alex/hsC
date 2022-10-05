#define hsC_C

#include "../hsC.h"
#include <stdio.h>
#include <ctype.h>


int main(void) {

    float *floatList = NULL;
    gen(0.0,3.5,float,0.15,floatList);
    for(int i = 0; i <= (3.5 / 0.15); i++) {
        printf("%lf\n",floatList[i]);
    }
    puts("---");
    int *intList = NULL;
    gen(0,10,int,1,intList);
    for(int i = 0; i <= 10; i++) {
        printf("%d\n",intList[i]);
    }

    return 0;
}

