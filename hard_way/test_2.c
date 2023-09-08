#include <stdio.h>

int main() {
    int a = 13;
    int* a_p;
    // printf("a address=%p, a_p address=%p, a_p=%p\n",&a, &a_p, a_p);
    a_p = &a;
    // printf("a address=%p, a_p address=%p, a_p=%p\n",&a, &a_p, a_p);
    // printf("a=%d, *a_p=%d\n",a, *a_p);
    *a_p = 11;
    // printf("a=%d, *a_p=%d\n",a, *a_p);
    return 0;
}

/**
 * lea指令=只是用来获得内存地址，它不会加载内存中的实际数据，只是地址；例如 leaq -12(%rbp), %rax
 * 括号+寄存器=间接寻址；例如 movl $11, (%rax)
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $13, -12(%rbp)      // int a = 13;

        leaq    -12(%rbp), %rax     // 先用lea取得变量a的地址，赋值给rax
        movq    %rax, -8(%rbp)      // a_p = &a;

        movq    -8(%rbp), %rax      // 下面使用括号解引用，即把11赋值给rax所指向的地址
        movl    $11, (%rax)         // *a_p = 11;

        movl    $0, %eax
        popq    %rbp
        ret
*/