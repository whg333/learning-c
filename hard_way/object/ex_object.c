//
// Created by whg on 2023/9/12.
//

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex_object.h"

int Monster_init(void *self){
    Monster *monster = self;
    monster->hit_points = 10;
    printf("Monster(%s)[hp=%d] init.\n", monster->proto.desc, monster->hit_points);
    return 1;
}
int Monster_attack(void *self, int damage){
    Monster *monster = self;
    printf("You attack %s[hp=%d]!\n", monster->_(desc), monster->hit_points);

    // 当把Room_attack写错成Monster_attack，这里实际上就是地址Room结构体下的Monster的字段地址，因为都是第2个字段
    // Monster *m = monster->hit_points;
    // printf("You attack %s[hp=%d]!\n", m->_(desc), m->hit_points);

    monster->hit_points -= damage;
    printf("You damage it with %d!\n", damage);
    if(monster->hit_points > 0){
        printf("It is still alive[hp=%d].\n", monster->hit_points);
        return 0;
    }else{
        printf("It is dead!\n");
        return 1;
    }
}
Object MonsterProto = {
        .init = Monster_init,
        .attack = Monster_attack,
};

int Room_init(void *self){
    Room *room = self;
    printf("Room(%s) init.\n", room->proto.desc);
    return 1;
}
void *Room_move(void *self, Direction direction){
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north){
        printf("You go north, into:\n");
        next = room->north;
    }else if(direction == SOUTH && room->south){
        printf("You go south, into:\n");
        next = room->south;
    }else if(direction == EAST && room->east){
        printf("You go east, into:\n");
        next = room->east;
    }else if(direction == WEST && room->west){
        printf("You go west, into:\n");
        next = room->west;
    }else{
        printf("You can't go that direction.\n");
        next = NULL;
    }

    if(next){
        next->_(describe)(next);
    }

    return next;
}
int Room_attack(void *self, int damage){
    Room *room = self;
    Monster *monster = room->bad_guy;
    if(monster){
        monster->_(attack)(monster, damage);
        return 1;
    }else{
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

Object RoomProto = {
        .init = Room_init,
        .move = Room_move,
        .attack = Room_attack,
};

void *Map_move(void *self, Direction direction){
    Map *map = self;
    Room *location = map->location;
    Room *next = location->_(move)(location, direction);
    if(next){
        map->location = next;
    }
    return next;
}
int Map_attack(void *self, int damage){
    Map *map = self;
    Room *location = map->location;
    return location->_(attack)(location, damage);
}
int Map_init(void *self){
    Map *map = self;

    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

    hall->north = throne;

    throne->east = kitchen;
    throne->south = hall;
    throne->west = arena;

    arena->bad_guy = NEW(Monster, "The evil minotaur");
    arena->east = throne;

    kitchen->west = throne;

    map->start = hall;
    map->location = hall;

    printf("Map(%s) init.\n", map->proto.desc);
    return 1;
}

Object MapProto = {
        .init = Map_init,
        .move = Map_move,
        .attack = Map_attack,
};

int process_input(Map *game){
    printf("\n> ");

    int ch = getchar();
    getchar(); // 忽略回车键

    int damage = rand() % 4;

    printf("%c\n", ch);
    switch(ch){
        case 'q':
            printf("Quit? Giving up? You suck.\n");
            return 0;

        case 'n':
            game->_(move)(game, NORTH);
            break;
        case 's':
            game->_(move)(game, SOUTH);
            break;
        case 'e':
            game->_(move)(game, EAST);
            break;
        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':
            game->_(attack)(game, damage);
            break;

        case 'l':
            printf("You can go:\n");
            if(game->location->north) printf("NORTH\n");
            if(game->location->south) printf("SOUTH\n");
            if(game->location->east) printf("EAST\n");
            if(game->location->west) printf("WEST\n");
            break;

        default:
            printf("What? You input:%c\n", ch);
    }

    return 1;
}

int main(){
    srand(time(NULL));

    Map *game = NEW(Map, "The Hall of the Minotaur");
    printf("Game Begin: You enter the ");
    game->location->_(describe)(game->location);
    while(process_input(game)){

    }
    return 0;
}