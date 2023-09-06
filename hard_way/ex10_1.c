#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 2){
        puts("You need one arguments.");
        return 1;
    }

    char a = '\0';
    printf("a=%c, a=%d\n", a, a);

    int i;
    char letter;
    for(i=0; (letter = argv[1][i]) != '\0'; i++){
        printf("%c", letter);
    }
    puts("");
    return 0;
}