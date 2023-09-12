//
// Created by whg on 2023/9/12.
//

#ifndef WHG_C_OBJECT_H
#define WHG_C_OBJECT_H

typedef enum {
    NORTH, SOUTH, EAST, WEST,
} Direction;

// (void *)代表任意指针类型
typedef struct {
    char *desc;
    int (*init)(void *self);
    void (*destroy)(void *self);

    void (*describe)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);

void *Object_new(int size, Object proto, char *desc);

// 将NEW(Room, "Hello") 变为 Object_new(sizeof(Room), RoomProto, "Hello")
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)

// 将obj->_(blah) 变为 obj->proto.blah
#define _(N) proto.N

#endif //WHG_C_OBJECT_H
