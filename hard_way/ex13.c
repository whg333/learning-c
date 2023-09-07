#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    for(i=0;i<argc;i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    puts("");

    printf("sizeof_char = %lu\n", sizeof(char));
    printf("sizeof_char_s = %lu\n", sizeof(char *));

    char *states[] = {"1", "234567", "89", "abc"};
    int sizeof_statues = sizeof(states);
    int sizeof_char_ss = sizeof(char **);
    int states_length = sizeof_statues / sizeof_char_ss;
    printf("sizeof_char_ss = %d\n", sizeof_char_ss);
    printf("sizeof_statues = %d\n", sizeof_statues);
    printf("states_length = %d\n", states_length);

    puts("");
    for(i=0;i<states_length;i++){
        printf("states[%d] = %s\n", i, states[i]);
    }
    return 0;
}