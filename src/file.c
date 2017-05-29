//
// Created by tanya on 28.05.17.
//

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <jansson.h>
#include <progbase/list.h>
#include "actor.h"

char* File_fileToJson(const char* filePath) {
    FILE* fin = fopen(filePath, "r");
    if (fin == NULL) {
        puts("Can't open the file'");
        return NULL;
    }
    fseek(fin, 0, SEEK_END);
    int size = ftell(fin);
    fclose(fin);
    char data[200];
    File_readAllText(filePath, data);

    json_t * jobj = json_object();
    json_object_set(jobj, "name", json_string(filePath));
    json_object_set(jobj, "size", json_integer(size));
    json_object_set(jobj, "data", json_string(data));

    char *jStr = json_dumps(jobj, JSON_COMPACT);
    json_decref(jobj);
    return jStr;
}

List* File_readAsJson(const char* filePath) {
    char jsonStr[1000] = "";
    File_readAllText(filePath, jsonStr);

    List* list = List_new();

    json_error_t err;
    json_t * jsonArr = json_loads(jsonStr, 0, &err);
    int index = 0;
    json_t * value = NULL;
    json_array_foreach(jsonArr, index, value) {
        Actor* node = Actor_new();
        Actor_setName(node, (char *)json_string_value(json_object_get(value, "name")));
        Actor_setId(node, json_integer_value(json_object_get(value, "id")));
        Actor_setCountry(node, (char *)json_string_value(json_object_get(value, "born")));
        Actor_setNationality(node, (char *)json_string_value(json_object_get(value, "nationality")));
        Actor_setOscar(node, json_boolean_value(json_object_get(value, "Oscar")));
        List_add(list, node);
    }
    json_decref(jsonArr);
    return list;
}

char* File_fileContent(const char* filepath) {
    char buffer[200];
    File_readAllText(filepath, buffer);

    json_t * jarr = json_array();

    char * ptr = buffer;
    int sum = 0;
    int count = 0;

    do{
        if(isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
            sum = (int) strtol(ptr, &ptr, 10);
            if (count % 2 == 0)
                json_array_append_new(jarr, json_integer(sum));
            count++;
        } else {
            ptr++;
        }
    } while(*ptr != 0);

    char *jStr = json_dumps(jarr, JSON_COMPACT);
    json_decref(jarr);
    return jStr;
}

bool File_readAllText(const char * filePath, char * text) {
    char line[100];
    FILE* fin = fopen(filePath, "r");
    if (fin == NULL) return false;
    if(fgets(line, 100, fin))
        strcpy(text, line);
    while(fgets(line, 100, fin)) {
        strcat(text, line);
    }
    text[strlen(text)+1] = '\0';
    fclose(fin);
    return true;
}

