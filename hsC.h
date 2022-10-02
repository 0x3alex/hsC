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

typedef enum {
    INT = sizeof(int),
    FLOAT = sizeof(float),
    STRING = sizeof(char)
} supportet_types;

// => Structs
    /*
        * Struct is used for functions that return a new pointer
        * user can get result list and length, since calulcating length of an pointer
        * is not possible
    */
typedef struct {
    void *res;
    int len;
} res;

    /*
        * Struct is used for functions that return either the value or nothing
        * not really needed, since it could be done by an void pointer
        * but its better for processing the values afterwards and clearness   
    */
typedef void* MaybeValue;
typedef struct {
    MaybeValue value;
} maybe;

// => Mapping
            //Map with function int to int
int         *MapIntToInt(int(*f)(int), int *list, int len);
            //Map with function int to float
float       *MapIntToFloat(float(*f)(int),int *list, int len);

            //Map with function char to char
char        *MapCharToChar(char(*f)(char),char *list, int len);



// => Filter
res     *filterInt(bool(*f)(int),int *list,int len);

// => Take
int     *takeInt(int amount, int *list, int len);
char    *takeChar(int amount, char *list, int len);
res     *takeCharWhile(bool(*f)(char),int *list, int len);
res     *takeIntWhile(bool(*f)(int),int *list, int len);

// => Drop
int     *dropInt(int amount, int *list, int len);
res     *dropIntWhile(bool(*f)(int),int *list, int len);
res     *dropCharWhile(bool(*f)(char),int *list, int len);


// => Gen
int     *intGen(int start, int stop);
char    *strGen(char start, char stop);

// => Find
maybe   *findInt(int value, int *list, int len);
maybe   *findChar(char value, char *list, int len);


#endif

/*
    *IMPLEMENTATION
*/

#ifdef hsC_C

// => Mapping
        /*
            *Int to Int
        */
int     *MapIntToInt(int(*f)(int), int* list, int len) {
    int *t = calloc(len,sizeof(int));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;

}
        /*
            *Int to Float
        */
float   *MapIntToFloat(float(*f)(int),int *list, int len) {
    float *t = calloc(len,sizeof(float));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}
        /*
            *Char to char
        */
char    *ccMap(char(*f)(char),char *list, int len) {
    char *t = calloc(len,sizeof(char));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

// => Fiter
res     *filterInt(bool(*f)(int),int *list,int len) {
    res *r = calloc(1,sizeof(res));
    int *tmp = calloc(len,sizeof(int));
    int tmpIdx = 0;
    for(int i = 0; i < len; i++) {
        if(f(list[i]) == true) {
            tmp[tmpIdx++] = list[i];
        }
    }
    int *p = calloc(tmpIdx,sizeof(int));
    memcpy(p,tmp,tmpIdx*sizeof(int));
    r ->len = tmpIdx;
    r ->res = (void*) p;
    return r;
}

// => Take
int *takeInt(int amount, int *list, int len) {
    if(amount > len) return NULL;
    int *p = calloc(amount,sizeof(int));
    if(p == NULL) return NULL;
    for(int i = 0; i < amount; i++) {
        p[i] = list[i];
    }
    return p;
}

res *takeIntWhile(bool(*f)(int),int *list, int len) {
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

int     *dropInt(int amount, int *list, int len) {
    if(amount > len) return NULL;
    for(int i = 0; i < amount; i++) {
        *list++;
    }
    return list;
}

res *dropIntWhile(bool(*f)(int),int *list, int len) {
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
int *intGen(int start, int stop) {
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
maybe *findInt(int value, int *list, int len) {
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