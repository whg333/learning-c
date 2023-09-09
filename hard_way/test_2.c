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
    int** a_pp;
    a_pp = &a_p;
    // printf("a=%d, *a_p=%d, **a_pp=%d\n",a, *a_p, **a_pp);
    **a_pp = 12;
    // printf("a=%d, *a_p=%d, **a_pp=%d\n",a, *a_p, **a_pp);

    /*
    char *s[] = {"Ali", "Bob"};
    char** s_p;
    printf("s address=%p, s_p address=%p, s_p=%p\n",&s, &s_p, s_p);
    s_p = s;
    printf("s address=%p, s_p address=%p, s_p=%p\n",&s, &s_p, s_p);
    printf("s[0]=%s, s[1=]%s, *s_p=%s\n",s[0], s[1], *s_p);
    *s_p = "whg";
    printf("s[0]=%s, s[1=]%s, *s_p=%s\n",s[0], s[1], *s_p);
    s_p++;
    *s_p = "amy";
    printf("s address=%p, s_p address=%p, s_p=%p\n",&s, &s_p, s_p);
    printf("s[0]=%s, s[1=]%s, *s_p=%s\n",s[0], s[1], *s_p);
    */
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

/**
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $13, -12(%rbp)

        leaq    -12(%rbp), %rax
        movq    %rax, -24(%rbp)

        movq    -24(%rbp), %rax
        movl    $11, (%rax)

        leaq    -24(%rbp), %rax     // 先用lea取得变量a_p的地址，赋值给rax
        movq    %rax, -8(%rbp)      // a_pp = &a_p;

        movq    -8(%rbp), %rax      // 下面使用2次括号进行2次解引用，即把12赋值给rax所指向的地址
        movq    (%rax), %rax        // 第1次解引用
        movl    $12, (%rax)         // 第2次解引用，**a_pp = 12;

        movl    $0, %eax
        popq    %rbp
        ret
 */

/**
.LC0:
        .string "Alan"
.LC1:
        .string "whg"
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movq    $.LC0, -16(%rbp)

        leaq    -16(%rbp), %rax
        movq    %rax, -8(%rbp)

        movq    -8(%rbp), %rax
        movq    $.LC1, (%rax)

        movl    $0, %eax
        popq    %rbp
        ret
*/