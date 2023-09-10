#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person{
    char* name;
    int age;
} S_Person;

S_Person* Person_create(char* name, int age){
    S_Person* person = malloc(sizeof(S_Person)) ;
    assert(person != NULL);
    person->name = strdup(name);
    person->age = age;
    return person;
}

void Person_destroy(S_Person* person){
    assert(person != NULL);
    free(person->name);
    free(person);
}

void Person_print(S_Person* person){
    printf("pointer:%p, name:%s, age:%d\n", person, person->name, person->age);
}

int main() {
    struct Person zxc = {};
    // zxc.name = "zxy";
    // zxc.age = 36;
    Person_print(&zxc);

    S_Person whg = {"whg", 37};
    // whg.name = "whg";
    // whg.age = 37;
    Person_print(&whg);

    S_Person* joe = Person_create("Joe", 32);
    Person_print(joe);
    S_Person* frank = Person_create("Frank", 20);
    Person_print(frank);

    joe->age += 20;
    Person_print(joe);
    frank->age += 20;
    Person_print(frank);

    Person_destroy(joe);
    Person_destroy(frank);
    return 0;
}