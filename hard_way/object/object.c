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
    if(!proto.init) proto.init = Object_init;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.move) proto.move = Object_move;
    if(!proto.attack) proto.attack = Object_attack;

    Object *obj = calloc(1, size); // calloc返回void *任意类型的指针
    *obj = proto; // 指针骚操作，直接指向提前创建好的名为XxxProto的Object，每个对象结构体的第一个字段名为proto且为Object类型

    obj->desc = strdup(desc);

    if(!obj->init(obj)){
        obj->destroy(obj);
        return NULL;
    }else{
        return obj;
    }
}
