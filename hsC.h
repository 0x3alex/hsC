#ifndef hsC_H
#define hsC_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOTHING 0x0
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
    *Simple struct to use tuples in c
*/
typedef struct {
    void *val1;
    void *val2;
} tuple;

/*
    *get first element of the tuple
*/
void *fst(tuple *t) {
    return t->val1;
}

/*
    *get second element of the tuple
*/
void *snd(tuple *t) {
    return t->val2;
}

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
        out = calloc(length,sizeof(typ)); \
        if(out != NULL) { \
            for(int i = 0; i < length; i++) { \
                out[i] = func(list[i]); \
            } \
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
        out = calloc(amount,sizeof(type)); \
        if(out != NULL) { \
            for(int i = 0; i < amount; i++) { \
                out[i] = list[i]; \
            } \
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
        type start = sta; \
        type stop = sto; \
        int i = 0; \
        out = calloc((start/step),sizeof(type)); \
        if(out != NULL) { \
            while(start >= stop) { \
                out[i++] = start-step;\
            }\
        }else{out = NULL;} \
    }else{ \
        type start = sta; \
        type stop = sto; \
        int i = 0; \
        out = calloc((stop / step),sizeof(type));\
        if(out != NULL) {\
            while(start <= stop) {\
                out[i++] = start;\
                start += step; \
            }\
        }else{out = NULL;}\
    }

/*
    * list is the list that is going to be chain-mapped over
    * list_length is the length of the list
    * funcs is the list of funcs, must have the same type as list, type and out
        *(input type should be output type and input type should be the same as type, out and list)
    * funcs_length is the length of the functions list
    * type is the type
    * out is the output    
    * [x] -> [x -> x] -> [x]    
*/
#define chain(list,list_length,funcs,funcs_length,type,out) \
    if(list != NULL) { \
        out = calloc(list_length,sizeof(type)); \
        if(out != NULL) { \
            map(funcs[0],list,list_length,type,out); \
            for(int i = 1; i < funcs_length; i++) { \
                for(int j = 0; j < list_length; j++) { \
                    out[j] = funcs[i](out[j]); \
                } \
            } \
        }else{out = NULL;} \
    }else{out = NULL;}

/*
    *val is the value to be checked for
    *list is the list to be checked in
    *isString has to be true if list is type char* or greater
    *length is the length of the list
    *out is the output, which is a bool
*/
#define elem(val,list,isString,length,out) \
    if (list != NULL) { \
        for(int i = 0; i < length; i++) { \
            if(isString) { \
                if(strcmp(val,list[i]) == 0) { \
                    out = true; \
                } \
            }else{ \
                if(val == list[i]) { \
                    out = true; \
                } \
            } \
        } \
        if(!out) { \
            out = false; \
        } \
    }else{ out = false; } \


/*
    *list is the list to reverse
    *list_length is the length of the list
    *type is the type of the list
    *out is the output and needs to be the same type as type
*/
#define reverse(list,list_length,type,out) \
    if(list != NULL) { \
        out = calloc(list_length,sizeof(type)); \
        int ridx = 0; \
        for(int i = list_length-1; i >= 0 ; i--) { \
            out[ridx++] = list[i]; \
        } \
    }else{out = NULL;}
     
#ifdef HSC_STR
/*
    Something like *find* just for stings. Returns instead of "nothing" and the res, true and false
    * value is the value to check for
    * value_length is the length of the value
    * list is the list to search in
    * list_length is the length of the list
 */

bool isInfixOf(char *value, int value_length,char *list, int list_length) {
    if(list == NULL) return false;
    for(int i = 0; i < list_length; i++) {
        if(i+value_length > list_length) {
            return false;
        }
        char *tmp = (char*)calloc(value_length,sizeof(char));
        for(int j = 0; j <= value_length; j++) {
            tmp[j] = list[i+j];
        }
        if(strncmp(value,tmp,value_length) == 0) {
            free(tmp);
            return true;
        }
        free(tmp);
    }
}

char digitToInt(int a) {
    return a + '0';
}

int occurrencesInString(char *string, char c) {
    int r = 0;
    while(*string) {
        if(*string++ == c) {
            r++;
        }
    }
    return r;
}

/*
    *list is the string to split
    *list_lenght is the length of the string
    *f is a function that returns true or falese the given char is the splitter
    *splitter is the splitter to split at
*/
res *splitAt(char *list,int list_length,bool(*f)(char),char splitter) {
    /*
        * caluclate length of result list
    */
    int so = 1 + occurrencesInString(list,splitter);
    char **splitted = calloc(so,sizeof(char*));
    int ridx = 0;
    while(so > 0) {
        /*
            * Get String until Space
        */
        res *r = NULL;
        takeWhile(f,list,list_length,char,r);
        /*
            * copy over
        */
        splitted[ridx++] = (char*)(r->res);
        free(r);
        /*
            * Drop Until Space is reached and set list to new list 
        */
        dropWhile(f,list,list_length,char*,r);
        /*
            * recalculate
        */
        so--;
        list = (char*)r->res;
        *list++;
        free(r);
        
    }
    /*
        *Put it into a res struct to provide the length of the char** list
    */
    res* rr = calloc(1,sizeof(res));
    rr->len = ridx;
    rr->res = (void*)splitted;
    return rr;
}

#endif
#endif
