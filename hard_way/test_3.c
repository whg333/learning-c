#include <stdio.h>
#include <stdlib.h>

typedef struct Person{
    char* name; // 8 byte
    int age;    // 4 byte
} S_Person;

typedef struct {
    S_Person persons[1];
} Team;

int main() {
    int size_size_t = sizeof(size_t);
    printf("sizeof(size_t)=%d\n", size_size_t);
    int size_char_pointer = sizeof(char*);
    printf("sizeof(char*)=%d\n", size_char_pointer);
    int size_int = sizeof(int);
    printf("sizeof(int)=%d\n", size_int);
    int size_long = sizeof(long);
    printf("sizeof(long)=%d\n", size_long);
    int size_long_int = sizeof(long int);
    printf("sizeof(long int)=%d\n", size_long_int);
    int size_long_long = sizeof(long long);
    printf("sizeof(long long)=%d\n", size_long_long);
    int size_person = sizeof(S_Person);
    printf("sizeof(S_Person)=%d\n", size_person);
    int size_team = sizeof(Team);
    printf("sizeof(Team)=%d\n", size_team);
    Team *team = malloc(size_team);
    S_Person whg = {"whg", 23};
    team->persons[0] = whg;

    printf("%s is %d year old.\n", team->persons[0].name, team->persons[0].age);

    S_Person p_whg = team->persons[0]; // 生成了一个新的局部变量的结构体
    p_whg.age = 37;
    // 不使用指针的话，还得重如下新设置一下，汇编层面也只是做一下值的移动mov赋值
    team->persons[1] = p_whg;

    // S_Person* p_whg = &team->persons[0];
    // p_whg->age = 37;

    printf("%s is %d year old again.\n", team->persons[0].name, team->persons[0].age);

    return 0;
}

/**
typedef struct Person{
    char* name;
    int age;
} S_Person;

int main() {
    struct Person zxc = {"zxc", 13};
    S_Person whg = {"whg", 23};
    return 0;
}

  |
  |
 \|/

.LC0:
        .string "zxc"
.LC1:
        .string "whg"
main:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $.LC0, -16(%rbp)
        movl    $13, -8(%rbp)
        movq    $.LC1, -32(%rbp)
        movl    $23, -24(%rbp)
        movl    $0, %eax
        popq    %rbp
        ret
*/