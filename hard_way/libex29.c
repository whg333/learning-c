//
// Created by whg on 2023/9/26.
//

/**
 * 先把.c编译成.o文件，注意使用-fPIC
 * gcc -std=c99 -fPIC -c libex29.c -o libex29.o
 * 再把.o文件变成.so动态库，使用-shared
 * gcc -shared -o libex29.so libex29.o
 * 使用-ldl可加载动态库
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