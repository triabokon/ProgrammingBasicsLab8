//
// Created by tanya on 28.05.17.
//

#include <string.h>
#include <jansson.h>
#include "list.h"
#include "actor.h"

int List_containsById(List* self, int id) {
    for(int i = 0; i < List_count(self); i++) {
        Actor * node = List_get(self, i);
        if(Actor_getId(node) == id) {
            return i;
        }
    }
    return -1;
}

List* List_filterByField(List* self, char* field, char* data) {
    if(strcmp(field, "name") == 0) {
        return List_filterByName(self, data);
    } else if(strcmp(field, "id") == 0) {
        return List_filterById(self, atoi(data));
    } else if(strcmp(field, "born") == 0) {
        return List_filterByCountry(self, data);
    } else if(strcmp(field, "nationality") == 0) {
        return List_filterByNationality(self, data);
    } else if(strcmp(field, "Oscar") == 0) {
        bool bdata = false;
        if (strcmp(data, "true") == 0)
            bdata = true;
        return List_filterHasAnOscar(self, bdata);
    } else {
        return NULL;
    }
}

List* List_filterByName(List* self, char* name) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Actor * act = List_get(self, i);
        if(strcmp(Actor_getName(act), name) == 0) {
            List_add(list, act);
        }
    }
    return list;
}

List* List_filterById(List* self, int id) {
    List* list = List_new();
    List_add(list, List_get(self, List_containsById(self, id)));
    return list;
}

List* List_filterByCountry(List* self, char* country) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Actor * act = List_get(self, i);
        if(strcmp(Actor_getCountry(act), country) == 0) {
            List_add(list, act);
        }
    }
    return list;
}

List* List_filterByNationality(List* self, char* nationality) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Actor * act = List_get(self, i);
        if(strcmp(Actor_getNationality(act), nationality) == 0) {
            List_add(list, act);
        }
    }
    return list;
}

List* List_filterHasAnOscar(List* self, bool oscar) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Actor * act  = List_get(self, i);
        if(Actor_getOscar(act) == oscar) {
            List_add(list, act);
        }
    }
    return list;
}

char * List_toJson(List* self) {
    json_t* jarr = json_array();
    json_t * jobj = NULL;

    for(int i = 0; i < List_count(self); i++) {
        Actor * act = List_get(self, i);

        jobj = json_object();

        json_object_set_new(jobj, "name", json_string(Actor_getName(act)));
        json_object_set_new(jobj, "id", json_integer(Actor_getId(act)));
        json_object_set_new(jobj, "born", json_string(Actor_getCountry(act)));
        json_object_set_new(jobj, "nationality", json_string(Actor_getNationality(act)));
        json_object_set_new(jobj, "Oscar", json_boolean(Actor_getOscar(act)));

        json_array_append(jarr, jobj);
    }

    char *jsonResStr = json_dumps(jarr, JSON_COMPACT);

    for(int i = 0; i < List_count(self); i++) {
        json_decref(json_array_get(jarr, i));
    }
    json_decref(jarr);
    return jsonResStr;
}