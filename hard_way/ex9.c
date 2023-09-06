#include <stdio.h>

int main() {
    int i = 0;
    while(i < 25){
        printf("%d\n", i);
        i++;
    }
    return 0;
}

/**
.LC0:
        .string "%d\n"
main:
        pushq   %rbp
        movq    %rsp, %rbp

        subq    $16, %rsp
        movl    $0, -4(%rbp)    // 初始化i为0
        jmp     .L2
.L3:
        movl    -4(%rbp), %eax
        movl    %eax, %esi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf          // 前面都是构造调用printf的参数，使用到了esi和edi

        addl    $1, -4(%rbp)    // 自增i
.L2:
        cmpl    $24, -4(%rbp)
        jle     .L3
        movl    $0, %eax
        leave
        ret
*/

/**
在汇编级别查看printf函数的调用时，你可能会看到esi和edi这两个寄存器被使用。这两个寄存器通常用于传递参数和地址，以及在字符串
 处理时进行操作。以下是它们的一般作用：

esi寄存器（Source Index）：
    esi 寄存器通常用于传递指向源数据的指针或地址。在字符串操作中，它通常指向源字符串或源数据的起始位置。
    当调用 printf 时，esi 可能用于指向格式字符串，这是一个包含格式化标志的字符串，用于告诉 printf 如何解释后续参数。
    esi 还可以用于传递其他参数，具体取决于函数的调用约定。

edi寄存器（Destination Index）：
    edi 寄存器通常用于传递指向目标数据的指针或地址。在字符串操作中，它通常指向目标字符串或目标数据的起始位置。
    在 printf 的内部实现中，edi 可能用于构建最终要输出的字符串，将格式化的数据写入其中。
    edi 还可以用于传递其他参数，具体取决于函数的调用约定。

这两个寄存器的确切用途可能会根据编译器、操作系统和函数调用约定而有所不同。它们在处理字符串和数据复制时非常有用，因为它们可以提
 供源和目标地址，使得数据操作更加高效。
*/