#include "../hsC.h"

int main(void) {
    char *t = "test";
	char *o = NULL;
	reverse(t,4,char,o);
	printf("%s\n",o);

    char **t2 = calloc(2,sizeof(char*));
    char *c1 = "hello";
    char *c2 = "world";
    t2[0] = c1;
    t2[1] = c2;
    char **o2 = NULL;
    reverse(t2,2,char*,o2);
    for(int i = 0; i < 2; i++) {
        printf("%s\n",o2[i]);
    }
}