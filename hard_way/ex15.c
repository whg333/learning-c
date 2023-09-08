#include <stdio.h>

int main() {
    int ages[] = {23, 43, 12, 89,2};
    char *names[] = {"Alan", "Frank", "Mary", "John", "Lisa"};

    int count = sizeof(ages) / sizeof(int);
    int i;

    for(i=0;i<count;i++){
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
    printf("--------------------\n");

    int *cur_age = ages;
    char **cur_name = names;

    for(i=0;i<count;i++){
        // 解引用（指针 + 偏移量）
        printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
    }
    printf("--------------------\n");

    for(i=0;i<count;i++){
        // 指针使用数组方式访问 = 指针 + 偏移量
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }
    printf("--------------------\n");

    long diff;
    for(cur_name=names,cur_age=ages;(diff=cur_age-ages)<count;cur_name++,cur_age++){
        printf("%p - %p = %ld\n", cur_age, ages, diff);
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
    printf("--------------------\n");

    return 0;
}
