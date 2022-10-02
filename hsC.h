/*
    *HEADER
*/
#ifndef hsC_H
#define hsC_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define NOTHING 0x0

/*
    * Struct for dropWhile and takeWhile to store length
*/

// => Structs
typedef struct {
    void *res;
    int len;
} res;

typedef void* MaybeValue;



typedef struct {
    MaybeValue value;
} maybe;

// => Mapping
// -> Int to ...
int         *iiMap(int(*f)(int), int *list, int len);
float       *ifMap(float(*f)(int),int *list, int len);

// -> Char to ..
char        *ccMap(char(*f)(char),char *list, int len);


// => Filter
res     *iFilter(bool(*f)(int),int *list,int len);

// => Take
int     *iTake(int amount, int *list, int len);
char    *sTake(int amount, char *list, int len);
res     *sTakeWhile(bool(*f)(char),int *list, int len);
res     *iTakeWhile(bool(*f)(int),int *list, int len);

// => Drop
res        *iDropWhile(bool(*f)(int),int *list, int len);
res        *sDropWhile(bool(*f)(char),int *list, int len);


// => Gen
int     *iGen(int start, int stop);

// => Find
maybe *iFind(int value, int *list, int len);


#endif

/*
    *IMPLEMENTATION
*/

#ifdef hsC_C

// => Mapping
// -> Int to ..
int *iiMap(int(*f)(int), int* list, int len) {
    int *t = calloc(len,sizeof(int));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;

}

// -> Char to ...
char *ccMap(char(*f)(char),char *list, int len) {
    char *t = calloc(len,sizeof(char));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

// => Fiter


// => Take
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


// => Drop
res *iDropWhile(bool(*f)(int),int *list, int len) {
    int nl = 0;
    for(int i = 0; i < len; i++) {
        if(f(*list) == false) {
            break;
        }
        *list++;
        nl++;
    }
    res *re =  calloc(1,sizeof(res));
    re ->len = nl;
    re ->res = list;
}

// => Gen
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


// => find
maybe *iFind(int value, int *list, int len) {
    maybe *m = calloc(1,sizeof(maybe));
    for(int i = 0; i < len; i++) {
        if(*list == value) {
            m ->value = (void*) &list;
            return m;
        }
        *list++;
    }
    m ->value = NOTHING;
    return m;
}



#endif