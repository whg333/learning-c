#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

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