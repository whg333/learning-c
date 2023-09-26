//
// Created by whg on 2023/9/27.
//

#include <dlfcn.h>
#include "dbg.h"

typedef int (*lib_function)(const char *msg);

int main(int argc, char *argv[]){
    check(argc == 4, "USAGE: ./ex29 libex29.so function data");

    char *lib_file = argv[1];
    char *lib_func = argv[2];
    char *data = argv[3];

    void *lib = dlopen(lib_file, RTLD_NOW);
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

    lib_function func = dlsym(lib, lib_func);
    check(func != NULL, "Did not find %s function in the library %s: %s", lib_func, lib_file, dlerror());

    int rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", lib_func, rc, data);

    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return 1;
}