/*
    *HEADER
*/
#ifndef hsC_H
#define hsC_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
    * No general typed functions for saftey
*/
int     *mapIntToInt(int(*f)(int), int *list, int len);
int     *takeInt(int amount, int *list, int len);
int     *takeWhileInt(bool(*f)(int),int *list, int len);
int     *dropWhileInt(bool(*f)(int),int *list, int len);


char        *mapChar(char(*f)(char),char *list, int len);
char        *takeChar(int amount, char *list, int len);
char        *takeWhileChar(bool(*f)(char),int *list, int len);
char        *dropWhileChar(bool(*f)(char),int *list, int len);


#endif

/*
    *IMPLEMENTATION
*/

#ifdef hsC_C

int *mapIntToInt(int(*f)(int), int* list, int len) {
    int *t = calloc(len,sizeof(int));
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;

}

int *takeInt(int amount, int *list, int len) {
    if(amount > len) return NULL;
    int p = calloc(amount,sizeof(int));
    for(int i = 0; i < amount; i++) {
        p[i] = list[i];
    }
    return p;
}

char *mapChar(char(*f)(char),char* list, int len) {
    int *t = calloc(len,sizeof(char));
    for(int i = 0; i < len; i++) {
        t[i] = f(list[i]);
    }
    return t;

}

#endif