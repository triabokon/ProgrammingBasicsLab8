//
// Created by tanya on 28.05.17.
//

/** @file
    @brief Actor module
*/

#ifndef ACTOR_H
#define ACTOR_H

#include <progbase/list.h>
#include <stdbool.h>

/**
    @struct Actor
    @brief defines an Actor data type
*/
typedef struct Actor Actor;

/**
    @brief Actor constructor
*/
Actor* Actor_new(void);

/**
    @brief Actor constructor setter
    @param name - Actor's name
    @param id - id of Actor
    @param nationality - nationality of Actor
    @param oscar - whether actor has an Oscar
*/
Actor* Actor_NewSet(char* name, int id, char* country, char* nationality, bool oscar);

/**
    @brief Actor destructor
*/
void Actor_free(Actor** self);

/**
    @brief get Actor's name
    @returns name of Actor
*/
char* Actor_getName(Actor * self);

/**
    @brief get Actor's id
    @returns id of Actor
*/
int Actor_getId(Actor * self);

/**
    @brief get Actor's motherland
    @returns motherland of Actor
*/
char* Actor_getCountry(Actor * self);

/**
    @brief get Actor's nationality
    @returns nationality of Actor
*/
char* Actor_getNationality(Actor * self);

/**
    @brief get whether Actor has an Oscar
    @returns boolean value
*/
bool Actor_getOscar(Actor * self);

/**
    @brief set Actor's name
    @param name - Actor's name
*/
void Actor_setName(Actor * self, char* name);

/**
    @brief set Actor's id
    @param id - id of Actor
*/
void Actor_setId(Actor * self,int id);

/**
    @brief set Actor's motherland
    @param country - motherland of Actor
*/
void Actor_setCountry(Actor * self, char* country);

/**
    @brief set Actor's nationality
    @param nationality - nationality of Actor
*/
void Actor_setNationality(Actor * self, char* nationality);

/**
    @brief set whether Actor has an Oscar
    @param oscar - oscar of Actor
*/
void Actor_setOscar(Actor * self, bool oscar);


/**
    @brief Actor representation in json string
    @returns json representation of Actor
*/
char* Actor_toJson(Actor * self);

#endif
