//
// Created by whg on 2023/9/14.
//
// gcc ex22_main.c ex22.o -o ex22_main

#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count){
    log_info("count is: %d", count);
    if(count > 10){
        int count = 100;
        log_info("count in this scope is %d", count);
    }
    log_info("count is at exit: %d", count);

    count = 3000;
    log_info("count after assign: %d", count);
}

int main(){
    log_info("My name: %s, age: %d", MY_NAME, get_age()); // Zed A. Shaw, 37
    set_age(100);
    log_info("My age is now: %d", get_age()); // 100

    log_info("THE_SIZE is: %d", THE_SIZE); // 1000
    print_size(); // 1000

    THE_SIZE = 9;

    log_info("THE_SIZE is now: %d", THE_SIZE); // 9
    print_size(); // 1000，错了，是9

    log_info("Ratio at first: %f", update_ratio(2.0)); // 1.0
    log_info("Ratio again: %f", update_ratio(10.0)); // 1.0，错了，是2.0
    log_info("Ratio once more: %f", update_ratio(300.0)); // 1.0，错了，是10.0

    int count = 4;
    scope_demo(count); // 4, 4, 3000
    scope_demo(count * 20); // 80, 100, 80, 3000

    log_info("count after calling scope_demo: %d", count); // 4

    return 0;
}