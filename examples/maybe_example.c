#include "../hsC.h"
#include <stdio.h>

int main(void) {

    int *intList = NULL;
    gen(0,10,int,1,intList);
    maybe *m = NULL;
    find(9,intList,10,int,m);
    int fM = NULL;
    int defVal = -1;
    fromMaybe(m,defVal,int,fM);
    printf("%d\n",fM);

    char* charList = NULL;
    gen('a','z',char,1,charList);
    maybe *mc = NULL;
    find('j',charList,26,char,mc);
    char fC = NULL;
    char dC = '_';
    fromMaybe(mc,dC,char,fC);
    printf("%c\n",fC);
    
    /*
        * For char* or char**,... use 'isInfixOf'
    */



    return 0;
}

