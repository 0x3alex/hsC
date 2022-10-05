#define hsC_C

#include "../hsC.h"
#include <stdio.h>
#include <ctype.h>

int t2(int a) {
    if (a % 2 == 0) {
        return a*1;
    }
    return a * 3;
}

char toUpper_(char c) {
    return toupper(c);
}

char *test(char *c) {
    return "test";
}

int main(void) {

    //int list
    int *intList = NULL;
    gen(0,10,int,2,intList);
    for(int i = 0; i < 5; i++) {
        printf("%d\n",intList[i]);
    }

    int *ma = NULL;
    map(t2,intList,5,int,ma);
    for(int i = 0; i < 5; i++) {
        printf("%d\n",ma[i]);
    }

    //char list
    char *charList = NULL;
    gen('a','e',char,1,charList);
    char *mc = NULL;
    map(toUpper_,charList,5,char,mc);
    for(int i = 0; i < 5; i++) {
        printf("%c\n",mc[i]);
    }

    //double char list
    char *c1 = "Hello";
    char *c2 = "World";
    char **c3 = calloc(2,sizeof(char*));
    c3[0] = c1;
    c3[1] = c2; 
    char **c4 = NULL;
    map(test,c3,2,char*,c4);
    for(int i = 0; i < 2; i++) {
        printf("%s\n",c4[i]);
    }

    return 0;
}

