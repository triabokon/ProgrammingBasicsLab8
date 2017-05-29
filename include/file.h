//
// Created by tanya on 28.05.17.
//

/** @file
    @brief module that works with files
*/

#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include <progbase/list.h>
#include "actor.h"

/**
    @brief return json string of list of values from file
    @param filePath - path to file to be read
    @returns json string with values from file
*/
char* File_fileToJson(const char* filePath);

/**
    @brief create a list of Actors from json file
    @param filePath - path to file to be read
    @returns list of Actors
*/
List* File_readAsJson(const char* filePath);

/**
    @brief creates a json string with data in file
    @param filePath - path to file to be read
    @returns json string with data in file
*/
char* File_fileContent(const char* filepath);

/**
    @brief reads data from file
    @param filePath - path to file to be read
    @param text - string that contains all information from file
*/
bool File_readAllText(const char * filePath, char * text);

#endif
