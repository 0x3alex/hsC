#define hsC_C
#include "hsC.h"

#include <stdio.h>
#define INT_ARRAY_LENGHT 20

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

    int *list = intGen(1,INT_ARRAY_LENGHT);
    puts("------------Inital list---------");
    for(int i = 0; i < INT_ARRAY_LENGHT; i++) {
        printf("%d\n",list[i]);
    }

    res *mod2 = filterInt(&IsMod2,list,INT_ARRAY_LENGHT);
    puts("--------Filtered if mod2-------");
    for(int i = 0; i < mod2 ->len; i++) {
        printf("%d\n",((int*)(mod2->res))[i]);
    }

    int *mp1 = MapIntToInt(&times3,((int*)(mod2->res)), mod2->len);
    puts("--------Mappend times 3-------");
    for(int i = 0; i < mod2 ->len; i++) {
        printf("%d\n",mp1[i]);
    }

    int *d1 = dropInt(1,mp1,mod2->len);
    puts("-----Dropped 1--------");
    for(int i = 0; i < (mod2 ->len)-1; i++) {
        printf("%d\n",d1[i]);
    }

    res *d2 = dropIntWhile(&lessThan30,d1,(mod2 ->len)-1);
    puts("-----Dropped While <= 30 --------");
    for(int i = 0; i < (d2 ->len); i++) {
        printf("%d\n",((int*)(d2->res))[i]);
    }

    res *d3 = takeIntWhile(&lessThan50,((int*)(d2->res)),d2 ->len);
    puts("-----take While <= 50 --------");
    for(int i = 0; i < (d3 ->len); i++) {
        printf("%d\n",((int*)(d3->res))[i]);
    }

    maybe *f1 = findInt(48,((int*)(d3->res)),d3->len);
    puts("-----find 48 --------");
    if(f1->value == NOTHING) {
        puts("Value not found");
    }else{
        printf("%d\n",((int*)(f1->value))[0]);
    }
    return 0;
}