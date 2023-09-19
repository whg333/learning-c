//
// Created by whg on 2023/9/20.
//

#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum {
    BLUE_EYES,
    GREEN_EYES,
    BROWN_EYES,
    BLACK_EYES,
    OTHER_EYES,
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
        "Blue", "Green", "Brown", "Black", "Other",
};

typedef struct {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[]){
    Person you = {.age=0};
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin); // 传递you.first_name数组即代表数组的首位元素的地址了
    check(in != NULL, "Failed to read first name.");

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for(int i=0;i<=OTHER_EYES;i++){
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf(">");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes-1;
    check(you.eyes >= 0 && you.eyes <= OTHER_EYES, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name); // 名字没有使用\n换行，是因为前面在读取输入内容的时候，已经把回车换行符读入了
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;

error:
    return 1;
}