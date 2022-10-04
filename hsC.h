#ifndef hsC_H
#define hsC_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define NOTHING 0x0

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
    * Func is the function that is going to be mapped, it does not need to be passed int with a &
        * The func should take the datatype of the list as input and return the datatype of "out"
            * f.E list is type char* and out is type int* then the function would be -> int(*f)(char)    
    * List is the list that is going to be mapped over
    * Length is the length of the list
    * type is the output type of "out"
    * "out" is the output list and should be initialized to NULL
*/
#define map(func,list,length,typ,out)  \
    if(list != NULL) {\
        typ *t = calloc(length,sizeof(typ)); \
        if(t != NULL) { \
            for(int i = 0; i < length; i++) { \
                t[i] = func(list[i]); \
            } \
            out = t; \
        }else{out = NULL;} \
    }else{out = NULL;}



/*
    * Func is the function that is going to be used as the filter
        * should take in the type of the list and return bool!
    * list ist the list
    * len is the length of the list
    * type is the type of the list
        *type needs to be the same type as list    
    * res is an res struct (defined above) initialized to null
        * res should be a pointer
*/
#define filter(func,list,length,type,res_struct) \
    res *a = calloc(1,sizeof(res)); \
    type *tmp = calloc(length,sizeof(type));\
    if(tmp != NULL) { \
        int tidx = 0; \
        for(int i = 0; i < length; i++) {\
            if(func(list[i]) == true) {\
                tmp[tidx++] = list[i];\
            } \
        } \
        int *p = calloc(tidx,sizeof(type)); \
        if(p != NULL) { \
            memcpy(p,tmp,tidx*sizeof(type)); \
            free(tmp); \
            a -> len = tidx; \
            a -> res = (void*) p; \
            res_struct = a; \
        }else{ \
            a -> len = 0; \
            a -> res = NULL;\
            res_struct = a; \
        } \
    }else{ \
        a -> len = 0; \
        a -> res = NULL; \
        res_struct = a; \
    } 

/* 
    * Amount is the amount to be taken from the list
    * List is the list that should be taken from
    * length is the length of the list
    * type is the type of the output list
        * input and output list should have the same type
    * out is the output list and should have the same type as type and list and is initialized to null
*/
#define take(amount, list, length, type, out) \
    if(list != NULL && amount <= length) { \
        type *p = calloc(amount,sizeof(type)); \
        if(p != NULL) { \
            for(int i = 0; i < amount; i++) { \
                p[i] = list[i]; \
            } \
            out = p; \
        } else { out = NULL ;} \
    } else { out = NULL; }


/*
    *func is the function that checks if the current values in the list fit
        * should take in the type of list and return bool
    * length is the length of the list
    * type is the type of the list
    * res_struct is the res struct (defined above) initialized to NULL
*/
#define takeWhile(func,list,length,type,res_struct) \
    if(list != NULL) { \
        type *tmp = calloc(length,sizeof(type)); \
        int idx = 0; \
        for(int i = 0; i < length; i++) { \
            if(func(list[i]) == true) { \
                tmp[idx++] = list[i]; \
                continue; \
            } \
            break; \
        } \
        type *p = calloc(idx,sizeof(type)); \
        memcpy(p,tmp,idx*sizeof(type)); \
        free(tmp); \
        res *a = calloc(1,sizeof(res)); \
        a -> len = idx; \
        a -> res = (void*) p; \
        res_struct = a; \
    }

/* 
    * Amount is the amount to be dropped from the list
    * List is the list that should be dropped from
    * length is the length of the list
    * type is the type of the output list
        * input and output list should have the same type
    * out is the output list and should have the same type as type and list and is initialized to null
*/
#define drop(amount, list, length, type, out) \
    if(list != NULL && amount <= length) { \
        for(int i = 0; i < amount; i++) { \
            *list++; \
        } \
        out = list; \
    } else {out = NULL;} \

/*
    *func is the function that checks if the current values in the list fit
        * should take in the type of list and return bool
    * length is the length of the list
    * type is the type of the list
    * res_struct is the res struct (defined above) initialized to NULL
*/
#define dropWhile(func,list,length,type,res_struct) \
    if(list != NULL) { \
        int idx = 0; \
        for(int i = 0; i < length; i++) { \
            if(func(*list) == false) { \
                break; \
            } \
            idx++; \
            *list++;\
        }\
        res *a = calloc(1,sizeof(res)); \
        a -> len = idx; \
        a -> res = list;\
        res_struct = a; \
    } else{res_struct = NULL;}


/*
    * sta is the start value
    * sto is the stop value
    * type is the type of the values
    * step is the step width
*/
#define gen(sta,sto,type,step,out) \
    if(sto < sta) { \
        type *p = NULL; \
        type start = sta; \
        type stop = sto; \
        int i = 0; \
        p = calloc((start-stop)+1,sizeof(type)); \
        if(p != NULL) { \
            while(start >= stop) { \
                if(start % step == 0) { \
                    p[i++] = start--;\
                }else{start--;} \
            }\
            out = p;\
        }else{out = NULL;} \
    }else{ \
        type *p = NULL; \
        type start = sta; \
        type stop = sto; \
        int i = 0; \
        p = calloc((stop-start)+1,sizeof(type));\
        if(p != NULL) {\
            while(start <= stop) {\
                if(start % step == 0) { \
                    p[i++] = start++;\
                }else{start++;} \
            }\
        }else{out = NULL;}\
        out = p; \
    }

/*
    * Val is the value to seach for
    * list is the list to search in
    * length is the length of the list
    * type is the type of the list
    * maybe_struct is the res struct
    [ ! ] - If value is found, value in maybe_struct is the value. If not, value in maybe_struct is NOTHING
*/
#define find(val,list,length,type,maybe_struct) \
    maybe *p = calloc(1,sizeof(maybe));\
    if(list != NULL) { \
        if(p != NULL) { \
            int f = 0; \
            for(int i = 0; i < length; i++) { \
                if(*list == val) { \
                    f = 1; \
                    p -> value = (void*) list; \
                    break; \
                } \
                *list++; \
            } \
            if(f == 0) p -> value = NOTHING; \
        }else{p -> value = NOTHING; } \
    }else{p -> value = NOTHING; } \
    maybe_struct = p;

#endif