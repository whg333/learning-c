int main() {
    int i = 3;
    switch (i) {
        case 1:
        case 5:
            return 1;
        case 2:
        case 6:
            return 2;
        case 3:
            return 3;
        default:
            return 0;
    }
}

/**
 * 可以看到以下汇编代码：switch case真的就是一段一段的去判断和做跳转，和if else不同
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $3, -4(%rbp)
        movl    -4(%rbp), %eax
        cmpl    $2, %eax
        je      .L3
        cmpl    $3, %eax
        je      .L4
        cmpl    $1, %eax
        jne     .L7
        movl    $1, %eax
        jmp     .L6
.L3:
        movl    $2, %eax
        jmp     .L6
.L4:
        movl    $3, %eax
        jmp     .L6
.L7:
        movl    $0, %eax
.L6:
        popq    %rbp
        ret
*/