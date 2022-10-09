#define HSC_STR
#include "../hsC.h"
#include <stdio.h>


int main(void) {
    
    char *text = "hello world and hello mars!";
    char *s = "and";
    bool f = isInfixOf(s,3,text,27);
    printf("Is %s infix of %s? %s",s,text,f ? "Yes" : "No");
    return 0;
}

