#include <stdio.h>

int main() {
    char name[] = "1";
    printf("name=%s\n", name);
    printf("name size=%ld\n\n", sizeof(name));

    char other_name[] = {'1'};
    char new_name[] = {'2', '3', '4'};
    printf("other_name=%s\n", other_name);
    printf("other_name size=%ld\n\n", sizeof(other_name));
    printf("new_name=%s\n", new_name);
    printf("new_name size=%ld\n\n", sizeof(new_name));

    char ret = 2 > 1;
    printf("ret=%d, ret=%c\n", ret, ret);
    if(ret){
        printf("ret is true\n");
    }else{
        printf("ret is false\n");
    }
    return 0;
}