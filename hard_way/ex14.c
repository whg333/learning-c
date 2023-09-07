#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// void print_letters(char *string);
// bool can_print(char letter);

bool can_print(char letter) {
    return isalpha(letter) || isblank(letter);
}

void print_letters(char *string) {
    char letter;
    for(int i=0; (letter=string[i]) != '\0'; i++){
        if(can_print(letter)){
            printf("'%c' == %d ", letter, letter);
        }
    }
    printf("\n");
}

void print_arguments(int argc, char *argv[]){
    for(int i=0;i<argc;i++){
        print_letters(argv[i]);
    }
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}