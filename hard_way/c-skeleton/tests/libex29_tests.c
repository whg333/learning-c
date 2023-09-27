//
// Created by whg on 2023/9/27.
//

#include "../src/minunit.h"

char *test_dlopen(){
    return NULL;
}

char *test_functions(){
    return NULL;
}

char *test_failed(){
    return NULL;
}

char *test_dlclose(){
    return NULL;
}

char *all_tests(){
    mu_suite_start();

    mu_run_test(test_dlopen);
    mu_run_test(test_functions);
    mu_run_test(test_failed);
    mu_run_test(test_dlclose);

    return NULL;
}

RUN_TESTS(all_tests);