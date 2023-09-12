//
// Created by whg on 2023/9/12.
//

#ifndef WHG_C_EX_OBJECT_H
#define WHG_C_EX_OBJECT_H

#include "object.h"

typedef struct {
    Object proto;
    int hit_points;
} Monster;

int Monster_init(void *self);
int Monster_attack(void *self, int damage);

typedef struct Room{
    Object proto;

    Monster *bad_guy;

    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
} Room;

int Room_init(void *self);
void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);

typedef struct {
    Object proto;
    Room *start;
    Room *location;
} Map;

int Map_init(void *self);
void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);

#endif //WHG_C_EX_OBJECT_H
