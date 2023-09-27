//
// Created by whg on 2023/9/27.
//

#include "../src/minunit.h"
#include <dlfcn.h>

typedef int (*lib_function)(const char *msg);
char *lib_file = "build/libwhg.so";
void *lib = NULL;

int check_function(const char *lib_func, const char *data, int expected){
    lib_function func = dlsym(lib, lib_func);
    check(func != NULL, "Did not find %s function in the library %s: %s", lib_func, lib_file, dlerror());

    int rc = func(data);
    check(rc == expected, "Function %s return %d for data: %s", lib_func, rc, data);

    return 1;

error:
    return 0;
}

char *test_dlopen(){
    lib = dlopen(lib_file, RTLD_NOW);
    mu_assert(lib != NULL, "Failed to open the library to test.");
    return NULL;
}

char *test_functions(){
    mu_assert(check_function("println", "Hello", 0), "println failed.");
    mu_assert(check_function("uppercase", "Hello", 0), "uppercase failed.");
    mu_assert(check_function("lowercase", "Hello", 0), "lowercase failed.");
    return NULL;
}

char *test_failed(){
    mu_assert(check_function("fail_on_purpose", "Hello", 1),
              "fail_on_purpose should fail.")
    return NULL;
}

char *test_dlclose(){
    int rc = dlclose(lib);
    mu_assert(rc == 0, "Failed to close lib.")
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