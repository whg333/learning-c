int main() {
    int i = 3;
    if(i == 1 || i == 5){
        return 1;
    }else if(i == 2 || i == 6){
        return 2;
    }else if(i == 3){
        return 3;
    }else{
        return 0;
    }
}

/**
 * if else是先做个判断，然后跳转到里面再继续接着做判断，这点和switch case的一个接一个的都去判断再做跳转不一样
main:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $3, -4(%rbp)
        cmpl    $1, -4(%rbp)
        jne     .L2
        movl    $1, %eax
        jmp     .L3
.L2:
        cmpl    $2, -4(%rbp)
        jne     .L4
        movl    $2, %eax
        jmp     .L3
.L4:
        cmpl    $3, -4(%rbp)
        jne     .L5
        movl    $3, %eax
        jmp     .L3
.L5:
        movl    $0, %eax
.L3:
        popq    %rbp
        ret
*/