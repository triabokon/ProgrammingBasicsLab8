//
// Created by tanya on 28.05.17.
//
/** @file
    @brief Some search functions for Actors list
*/

#ifndef LIST_H
#define LIST_H

#include <progbase/list.h>

/**
    @brief get Actor from list by id
    @param id -  Actor's id
    @returns index of Actor in list or -1 if no such Actor in list
*/
int List_containsById(List* self, int id);

/**
    @brief filters list of Actors by some field
    @param key - specified field
    @param value - value of field
    @returns new filtered list of Actors
*/
List* List_filterByField(List* self, char* field, char* data);

/**
    @brief filters list of Actors by name
    @param name - value of field name of Actor
    @returns new filtered by name list of Actors
*/
List* List_filterByName(List* self, char* name);

/**
    @brief filters list of Actors by id
    @param id - value of field id of Actor
    @returns new filtered by id list of Actors
*/
List* List_filterById(List* self, int id);

/**
    @brief filters list of Actors by their Motherland
    @param country - value of field country of Actor
    @returns new filtered by their Motherland list of Actors
*/
List* List_filterByCountry(List* self, char* country);

/**
    @brief filters list of Actors by Nationality
    @param nationality - value of field nationality of Actor
    @returns new filtered by nationality list of Actors
*/
List* List_filterByNationality(List* self, char* nationality);

/**
    @brief filters list of Actors by Oscar
    @param oscar - value of field Oscar of Actor
    @returns new filtered by Oscar list of Actors
*/
List* List_filterHasAnOscar(List* self, bool oscar);


/**
    @brief representation of list of Actors as json string
    @returns json string with list of Actors
*/
char* List_toJson(List* self);

#endif //LIST_H
