/*
    *HEADER
*/
#ifndef hsC_H
#define hsC_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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

/*
    * Every data type has its own functions, since i think its safer to operate with type specific functions
*/

// => Mapping
            //Map with function int to int
int         *MapIntToInt(int(*f)(int), int *list, int len);
            //Map with function int to bool
bool        *MapIntToBool(bool(*f)(int),int *list, int len);
            //Map with function int to char
char        *MapIntToChar(char(*f)(int),int *list, int len);
            //Map with function char to char
char        *MapCharToChar(char(*f)(char),char *list, int len);
            //Map with function char to bool
bool        *MapCharToBool(bool(*f)(char),char *list, int len);
            //Map with function char to int
int         *MapCharToInt(int(*f)(char),char *list, int len);

// => Filter
res     *filterInt(bool(*f)(int),int *list,int len);
res     *filterChar(bool(*f)(char),char *list,int len);

// => Take
int     *takeInt(int amount, int *list, int len);
char    *takeChar(int amount, char *list, int len);
res     *takeCharWhile(bool(*f)(char),char *list, int len);
res     *takeIntWhile(bool(*f)(int),int *list, int len);

// => Drop
int     *dropInt(int amount, int *list, int len);
res     *dropIntWhile(bool(*f)(int),int *list, int len);
char    *dropChar(int amount, char *list, int len);
res     *dropCharWhile(bool(*f)(char),char *list, int len);


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
int *MapIntToInt(int(*f)(int), int* list, int len) {
    if(list == NULL) return NULL; 
    int *t = calloc(len,sizeof(int));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;

}
bool *MapIntToBool(bool(*f)(int),int *list, int len) {
    if(list == NULL) return NULL; 
    bool *t = calloc(len,sizeof(bool));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

char *MapIntToChar(char(*f)(int),int *list, int len) {
    if(list == NULL) return NULL; 
    char *t = calloc(len,sizeof(char));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

char *MapCharToChar(char(*f)(char),char *list, int len) {
    if(list == NULL) return NULL; 
    char *t = calloc(len,sizeof(char));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

int *MapCharToInt(int(*f)(char),char *list, int len) {
    if(list == NULL) return NULL; 
    int *t = calloc(len,sizeof(int));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

bool *MapCharToBool(bool(*f)(char),char *list, int len) {
    if(list == NULL) return NULL; 
    bool *t = calloc(len,sizeof(bool));
    if(t == NULL) return NULL;
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;
}

// => Fiter
res *filterInt(bool(*f)(int),int *list,int len) {
    if(list == NULL) return NULL; 
    res *r = calloc(1,sizeof(res));
    int *tmp = calloc(len,sizeof(int));
    if(tmp == NULL) return NULL;
    int tmpIdx = 0;
    for(int i = 0; i < len; i++) {
        if(f(list[i]) == true) {
            tmp[tmpIdx++] = list[i];
        }
    }
    int *p = calloc(tmpIdx,sizeof(int));
    if(p == NULL) return NULL;
    memcpy(p,tmp,tmpIdx*sizeof(int));
    free(tmp);
    r ->len = tmpIdx;
    r ->res = (void*) p;
    return r;
}

res *filterChar(bool(*f)(char),char *list,int len) {
    if(list == NULL) return NULL; 
    res *r = calloc(1,sizeof(res));
    char *tmp = calloc(len,sizeof(char));
    if(tmp == NULL) return NULL;
    int tmpIdx = 0;
    for(int i = 0; i < len; i++) {
        if(f(list[i]) == true) {
            tmp[tmpIdx++] = list[i];
        }
    }
    char *p = calloc(tmpIdx,sizeof(char));
    if(p == NULL) return NULL;
    memcpy(p,tmp,tmpIdx*sizeof(char));
    free(tmp);
    r ->len = tmpIdx;
    r ->res = (void*) p;
    return r;
}

// => Take
int *takeInt(int amount, int *list, int len) {
    if(list == NULL) return NULL; 
    if(amount > len) return NULL;
    int *p = calloc(amount,sizeof(int));
    if(p == NULL) return NULL;
    for(int i = 0; i < amount; i++) {
        p[i] = list[i];
    }
    return p;
}

char *takeChar(int amount, char *list, int len) {
    if(list == NULL) return NULL; 
    if(amount > len) return NULL;
    char *p = calloc(amount,sizeof(char));
    if(p == NULL) return NULL;
    for(int i = 0; i < amount; i++) {
        p[i] = list[i];
    }
    return p;
}

res *takeIntWhile(bool(*f)(int),int *list, int len) { 
    if(list == NULL) return NULL; 
    int *tmp = calloc(len,sizeof(int));
    if(tmp == NULL) return NULL;
    int i = 0;
    for(; i <= len; i++) {
        if(f(list[i]) == true) {
            
            tmp[i] = list[i];
            continue;
        }
        break;  
    }
    int *r = calloc(i,sizeof(int));
    memcpy(r,tmp,i*sizeof(int));
    free(tmp);
    res *re = calloc(1,sizeof(res));
    re ->res = (void*) r;
    re ->len = i;
    return re;
}

res *takeCharWhile(bool(*f)(char),char *list, int len) { 
    if(list == NULL) return NULL; 
    char *tmp = calloc(len,sizeof(char));
    if(tmp == NULL) return NULL;
    int i = 0;
    for(; i <= len; i++) {
        if(f(list[i]) == true) {
            
            tmp[i] = list[i];
            continue;
        }
        break;  
    }
    char *r = calloc(i,sizeof(char));
    memcpy(r,tmp,i*sizeof(char));
    free(tmp);
    res *re = calloc(1,sizeof(res));
    re ->res = (void*) r;
    re ->len = i;
    return re;
}


// => Drop
int *dropInt(int amount, int *list, int len) {
    if(list == NULL) return NULL; 
    if(amount > len) return NULL;
    for(int i = 0; i < amount; i++) {
        *list++;
    }
    return list;
}

char *dropChar(int amount, char *list, int len) {
    if(list == NULL) return NULL; 
    if(amount > len) return NULL;
    for(int i = 0; i < amount; i++) {
        *list++;
    }
    return list;
}


res *dropIntWhile(bool(*f)(int),int *list, int len) {
    if(list == NULL) return NULL; 
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

res *dropCharWhile(bool(*f)(char),char *list, int len) {
    if(list == NULL) return NULL; 
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
    if(stop < start) {
        p = calloc((start-stop)+1,sizeof(int));
        if (p == NULL) return NULL;
        for( ; start >= stop ;) {
            p[index++] = start--;
        }
    }
    p = calloc((stop-start)+1,sizeof(int));
    if (p == NULL) return NULL;
    for( ; start <= stop ; ) {
        p[index++] = start++;
    }
    return p;
    
}

char *strGen(char start, char stop) {
    char *p = NULL;
    int index = 0;
    if(stop < start) {
        p = calloc((start-stop)+1,sizeof(char));
        if (p == NULL) return NULL;
        for( ; start >= stop ;) {
            p[index++] = start--;
        }
    }
    p = calloc((stop-start)+1,sizeof(char));
    if (p == NULL) return NULL;
    for( ; start <= stop ; ) {
        p[index++] = start++;
    }
    return p;
}


// => find
maybe *findInt(int value, int *list, int len) {
    if(list == NULL) return NULL; 
    maybe *m = calloc(1,sizeof(maybe));
    for(int i = 0; i < len; i++) {
        if(*list == value) {
            m ->value = (void*) list;
            return m;
        }
        *list++;
    }
    m ->value = NOTHING;
    return m;
}

maybe *findChar(char value, char *list, int len) {
    if(list == NULL) return NULL; 
    maybe *m = calloc(1,sizeof(maybe));
    for(int i = 0; i < len; i++) {
        if(*list == value) {
            m ->value = (void*) list;
            return m;
        }
        *list++;
    }
    m ->value = NOTHING;
    return m;
}



#endif