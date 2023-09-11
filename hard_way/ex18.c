#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message){
    if(errno){
        perror(message);
    }else{
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

typedef int (*compare_cb)(int a, int b);

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

int *bubble_sort(int *numbers, int count, compare_cb cmp){
    size_t numbers_size = count * sizeof(int);
    int *target = malloc(numbers_size);
    if(!target){
        die("Memory error!");
    }

    memcpy(target, numbers,numbers_size);

    for(int i=0;i<count;i++){
        for(int j=0;j<count-1;j++){
            if(cmp(target[j], target[j+1]) > 0){
                swap(&target[j], &target[j+1]);
            }
        }
    }

    return target;
}

int sorted_order(int a, int b){
    return a - b;
}

int reverse_order(int a, int b){
    return b - a;
}

int strange_order(int a, int b){
   if(a == 0 || b == 0){
       return 0;
   }else{
       return a % b;
   }
}

void test_sorting(int *numbers, int count, compare_cb cmp){
    int *sorted = bubble_sort(numbers, count, cmp);
    if(!sorted){
        die("Failed to sort as requested!");
    }

    for(int i=0;i<count;i++){
        printf("%d ", sorted[i]);
    }
    puts("");

    free(sorted);

    unsigned char * data = (unsigned char *)cmp;
    for(int i=0;i<25;i++){
        printf("%02X:", data[i]);
        // printf("%c:", data[i]);
    }
    puts("");
}

int main(int argc, char *argv[]) {
    if(argc < 2){
        die("USAFE: ./ex18 4 3 1 5 6");
    }

    int count = argc - 1;
    char **inputs = argv + 1; // 从第2个参数开始

    int *numbers = malloc(count * sizeof(int));
    if(!numbers){
        die("Memory error!");
    }

    for(int i=0;i<count;i++){
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);

    return 0;
}