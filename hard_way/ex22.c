//
// Created by whg on 2023/9/14.
//
/**
 * 编译细节加上-c参数，Compile and assemble, but do not link
gcc ex22.c -c -o ex22.o
 * 否则会报错
gcc ex22.c -o ex22.o
/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crt1.o: In function `_start':
(.text+0x20): undefined reference to `main'
collect2: error: ld returned 1 exit status
 */

#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age(){
    return THE_AGE;
}

void set_age(int age){
    THE_AGE = age;
}

double update_ratio(double new_ratio){
    static double ratio = 1.0;
    double old_ratio = ratio;
    ratio = new_ratio;
    return old_ratio;
}

void print_size(){
    log_info("I think size is: %d", THE_SIZE);
}