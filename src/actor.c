//
// Created by tanya on 28.05.17.
//

#include "actor.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#define NAME_LEN 100

struct Actor {
    char name[NAME_LEN];
    int id;
    char country[40];
    char nationality[40];
    bool oscar;
};

Actor*  Actor_new(void) {
    Actor* self = (Actor*)malloc(sizeof(Actor));
    strcpy(self->name,"");
    self->id = -1;
    strcpy(self->country, "");
    strcpy(self->nationality, "");
    self->oscar = false;
    return self;
}

Actor* Actor_NewSet(char* name, int id, char* country, char* nationality, bool oscar) {
    Actor* self = (Actor*)malloc(sizeof(Actor));
    strcpy(self->name,name);
    self->id = id;
    strcpy(self->country, country);
    strcpy(self->nationality, nationality);
    self->oscar = oscar;
    return self;
}

void Actor_free(Actor** selfPtr) {
    Actor* self = *selfPtr;
    free(self);
    *selfPtr = NULL;
}

char* Actor_getName(Actor * self) {
    return self->name;
}

int Actor_getId(Actor * self) {
    return self->id;
}

char* Actor_getCountry(Actor * self) {
    return self->country;
}

char* Actor_getNationality(Actor * self) {
    return self->nationality;
}

bool Actor_getOscar(Actor * self) {
    return self->oscar;
}

void Actor_setName(Actor * self, char* name) {
    strcpy(self->name, name);
}

void Actor_setId(Actor * self,int id) {
    self->id = id;
}

void Actor_setCountry(Actor * self, char* country) {
    strcpy(self->country, country);
}

void Actor_setNationality(Actor * self, char* nationality) {
    strcpy(self->nationality, nationality);
}

void Actor_setOscar(Actor * self, bool oscar) {
    self->oscar = oscar;
}

char* Actor_toJson(Actor * self) {
    json_t * jobj = json_object();
    json_object_set(jobj, "name", json_string(self->name));
    json_object_set(jobj, "id", json_integer(self->id));
    json_object_set(jobj, "born", json_string(self->country));
    json_object_set(jobj, "nationality", json_string(self->nationality));
    json_object_set(jobj, "oscar", json_boolean(self->oscar));

    char *jStr = json_dumps(jobj, JSON_COMPACT);
    json_decref(jobj);
    return jStr;
}

