//
// Created by whg on 2023/9/12.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

int Object_init(void *self){
    printf("Object init.\n");
    return 1;
}

void Object_destroy(void *self){
    Object *obj = self;
    if(obj){
        if(obj->desc){
            free(obj->desc);
        }
        free(obj);
    }
}

void Object_describe(void *self){
    Object *obj = self;
    printf("%s.\n", obj->desc);
}

void *Object_move(void *self, Direction direction){
    printf("You can't go that direction.\n");
    return NULL;
}

int Object_attack(void *self, int damage){
    printf("You can't attack that.\n");
    return 0;
}

void *Object_new(int size, Object proto, char *desc){
    assert(desc != NULL);

    if(!proto.init) proto.init = Object_init;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.move) proto.move = Object_move;
    if(!proto.attack) proto.attack = Object_attack;

    Object *obj = calloc(1, size); // calloc返回void *任意类型的指针
    assert(obj != NULL);
    *obj = proto; // 指针骚操作，直接指向提前创建好的名为XxxProto的Object，每个对象结构体的第一个字段名为proto且为Object类型

    obj->desc = strdup(desc);

    if(!obj->init(obj)){
        obj->destroy(obj);
        return NULL;
    }else{
        return obj;
    }
}

/**
* malloc 和 calloc 都是C语言中用于动态分配内存的函数，但它们之间有一些重要的区别：

分配内存的方式:

malloc（memory allocation）函数用于分配一块指定大小的内存块，但它不会初始化内存中的内容。分配的内存中的值是未定义的，可能包含任意数据。
calloc（contiguous allocation）函数用于分配一块指定大小的内存块，并将内存中的每个字节都初始化为零。这意味着使用 calloc 分配的内存是初始化过的，而不会包含随机值。
参数:

malloc 接受一个参数，即要分配的字节数，如 void* malloc(size_t size);。
calloc 接受两个参数，第一个参数是要分配的块数，第二个参数是每个块的大小，如 void* calloc(size_t num_blocks, size_t block_size);。总的分配字节数等于 num_blocks * block_size。
返回值:

malloc 返回一个指向分配内存起始地址的指针，或者在分配失败时返回 NULL。
calloc 也返回一个指向分配内存起始地址的指针，或者在分配失败时返回 NULL。与 malloc 不同，calloc 在分配内存时会执行初始化，因此内存中的每个字节都被设置为零。
用途:

malloc 适合在不需要初始化内存内容的情况下使用。它通常用于分配内存后，程序员会手动初始化所需的值。
calloc 适用于需要初始化内存内容为零的情况，例如在分配数组或结构体时，确保所有成员都初始化为零。
选择使用 malloc 还是 calloc 取决于你的需求。如果你需要初始化内存为零，或者你分配了一个数组并希望所有元素都初始化为零，那么 calloc 是更安全的选择。如果你需要分配内存但不关心初始值，那么 malloc 更适合。
*/