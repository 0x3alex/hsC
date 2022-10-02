/*
    *HEADER
*/
#ifndef hsC_H
#define hsC_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
    * Struct for dropWhile and takeWhile to store length
*/

typedef struct {
    void *res;
    int len;
} res;

/*
    * No general typed functions for saftey
*/
int     *iiMap(int(*f)(int), int *list, int len);
int     *iTake(int amount, int *list, int len);
res     *iTakeWhile(bool(*f)(int),int *list, int len);
res     *iDropWhile(bool(*f)(int),int *list, int len);
int     *iGen(int start, int stop);
int     *iGenFilter(int start, int stop, bool(*f)(int));


char        *ccMap(char(*f)(char),char *list, int len);
char        *takeChar(int amount, char *list, int len);
char        *takeWhileChar(bool(*f)(char),int *list, int len);
char        *dropWhileChar(bool(*f)(char),int *list, int len);


#endif

/*
    *IMPLEMENTATION
*/

#ifdef hsC_C

/* Int */

int *iiMap(int(*f)(int), int* list, int len) {
    int *t = calloc(len,sizeof(int));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;

}

int *iTake(int amount, int *list, int len) {
    if(amount > len) return NULL;
    int *p = calloc(amount,sizeof(int));
    if(p == NULL) return NULL;
    for(int i = 0; i < amount; i++) {
        p[i] = list[i];
    }
    return p;
}

res *iTakeWhile(bool(*f)(int),int *list, int len) {
    /*
    *   Create new list with same size, since its not known how many elements will be in int
    */  
    int *tmp = calloc(len,sizeof(int));
    if(tmp == NULL) return NULL;
    int i = 0;

    /*
    *   Copy until false result is reached
    */
    for(; i <= len; i++) {
        if(f(list[i]) == true) {
            
            tmp[i] = list[i];
            continue;
        }
        break;  
    }

    /*
    *   create new list with exact needed length
    */
    int *r = calloc(i,sizeof(int));

    /*
    *   Copy the results
    */
    memcpy(r,tmp,i*sizeof(int));
    free(tmp);

    /*
    *   To provide the length return a struct, which contains length and result
    */
    res *re = calloc(1,sizeof(res));
    re ->res = (void*) r;
    re ->len = i;
    return re;
}

int *iGen(int start, int stop) {
    int *p = NULL;
    int index = 0;
    /*
        *Gen descending list
    */
    if(stop < start) {
        p = calloc((start-stop)+1,sizeof(int));
        if (p == NULL) return NULL;
        for( ; start >= stop ;) {
            p[index++] = start--;
        }
    }

    /*
        *Gen ascending list
    */
    p = calloc((stop-start)+1,sizeof(int));
    if (p == NULL) return NULL;
    for( ; start <= stop ; ) {
        p[index++] = start++;
    }
    return p;
    
}


/* String */

char *ccMap(char(*f)(char),char *list, int len) {
    char *t = calloc(len,sizeof(char));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

#endif