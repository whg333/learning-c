//
// Created by whg on 2023/9/21.
//

#include <stdlib.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer) {
    *out_string = calloc(1, max_buffer+1);
    check_mem(*out_string);

    char *result = fgets(*out_string, max_buffer, stdin);
    check(result != NULL, "Input error.");
    return 0;

error:
    if(*out_string) free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(long *out_int) {
    char *input = NULL;
    char *end = NULL;
    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "Failed to read number.");

    *out_int = strtol(input, &end, 10);
    check((*end == '\0' || *end == '\n') && *input != '\0', "Failed to read number.");

    free(input);
    return 0;

error:
    if(input) free(input);
    return -1;
}

int read_scan(const char *fmt, ...) {
    int rc = 0;
    long *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    va_list argp;
    va_start(argp, fmt);

    for(int i=0;fmt[i] != '\0';i++){
        if(fmt[i] == '%'){
            i++;
            switch(fmt[i]){
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;
                case 'd':
                    out_int = va_arg(argp, long *);
                    rc = read_int(out_int);
                    check(rc == 0, "Failed to read int.");
                    break;
                case 'c':
                    out_char = va_arg(argp, char *);
                    *out_char = fgetc(stdin);
                    break;
                case 's':
                    max_buffer = va_arg(argp, int);
                    out_string = va_arg(argp, char **);
                    rc = read_string(out_string, max_buffer);
                    check(rc == 0, "Failed to read string.");
                    break;
                default:
                    sentinel("Invalid format.");
            }
        }else{
            fgetc(stdin);
        }

        check(!feof(stdin) && !ferror(stdin), "Input error.")
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int main(){
    char *first_name = NULL;
    char init = ' ';
    char *last_name = NULL;
    long age = 0;

    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name);
    check(rc == 0, "Failed first name.");

    printf("What's your init? ");
    rc = read_scan("%c\n", &init);
    check(rc == 0, "Failed init.");

    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "Failed last name.");

    printf("How old are you? ");
    rc = read_scan("%d", &age);
    check(rc == 0, "Failed to read age.");

    printf("---- RESULT ----\n");
    printf("First Name: %s", first_name);
    printf("Init: '%c'\n", init);
    printf("Last Name: %s", last_name);
    printf("Age: %ld\n", age);

    free(first_name);
    free(last_name);
    return 0;

error:
    return -1;
}