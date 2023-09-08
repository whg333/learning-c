#include <stdio.h>

int main() {
    int ages[] = {23, 43, 12, 89,2};
    char *names[] = {"Alan", "Bob", "Cook", "Dick", "Ella"};

    int count = sizeof(ages) / sizeof(int);
    int i;

    for(i=count-1;i>=0;i--){
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
    printf("--------------------\n");

    int* cur_age = ages;
    char** cur_name = names;

    for(i=count-1;i>=0;i--){
        // 解引用（指针 + 偏移量）
        printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
    }
    printf("--------------------\n");

    for(i=count-1;i>=0;i--){
        // 指针使用数组方式访问 = 指针 + 偏移量
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }
    printf("--------------------\n");

    long diff;
    cur_name = names;
    cur_age = ages;
    // printf("%p, %p\n", cur_age, ages);
    // 注意指针的运算，会结合类型长度，例如cur_age+1后，地址实际上是加了sizeof(int)即4个字节
    // printf("%lu\n", sizeof(int));
    cur_name+=count-1;
    cur_age+=count-1;
    // printf("%p, %p\n", cur_age, ages);
    for(;(diff=cur_age-ages)>=0;cur_name--,cur_age--){
        printf("%p - %p = %ld\n", cur_age, ages, diff);
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
    printf("--------------------\n");

    return 0;
}
