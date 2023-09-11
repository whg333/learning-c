#include <stdio.h>

int main() {
    printf("Hello, World! I am %d year old.%d\n", 24, 17);
    return 0;
}

/**
.LC0:
        .string "Hello, World! I am %d year old.%d\n"
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $17, %edx
        movl    $24, %esi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf

        movl    $0, %eax
        popq    %rbp
        ret
 */

/**
 * gcc自作聪明的将printf调用改为puts调用，并且字符串为"Hello, World!"而不是"Hello, World!\n"
.LC0:
        .string "Hello, World!"
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $.LC0, %edi
        call    puts

        movl    $0, %eax
        popq    %rbp
        ret
*/