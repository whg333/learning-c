//
// Created by whg on 2023/9/26.
//

/**
 * gcc -std=c99 -fPIC -c libex29.c -o libex29.o
 * gcc -shared -o libex29.so libex29.o
 * gcc -Wall -g -std=c99 ex29.c -ldl -o ex29
 */

#include <ctype.h>
#include "dbg.h"

int println(const char *msg){
    printf("A STRING: %s\n", msg);
    return 0;
}

int uppercase(const char *msg){
    for(int i=0;msg[i]!='\0';i++){
        printf("%c", toupper(msg[i]));
    }
    printf("\n");
    return 0;
}

int lowercase(const char *msg){
    for(int i=0;msg[i]!='\0';i++){
        printf("%c", tolower(msg[i]));
    }
    printf("\n");
    return 0;
}

int fail_on_purpose(const char *msg){
    return 1;
}