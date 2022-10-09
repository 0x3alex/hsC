#include "../hsC.h"
#include <stdio.h>

bool isEven(int a) {
    return a % 2 == 0;
}

int main(void) {

    int *intList = NULL;
    gen(1,20,int,1,intList);
    bool res = NULL;
    int v = 10;
    elem(v,intList,false,20,res);
    printf("Found? %s\n", res ? "Yes" : "No");
    
    char **strList = calloc(2,sizeof(char*));
    strList[0] = "hello";
    strList[1] = "world";
    char *cv = "hello";
    bool cres = NULL;
    elem(cv,strList,true,2,cres);
    printf("Found? %s\n", cres ? "Yes" : "No");
    return 0;
}

