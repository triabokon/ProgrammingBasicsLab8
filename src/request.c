//
// Created by tanya on 28.05.17.
//

#include "list.h"
#include "actor.h"
#include <string.h>
#include <ctype.h>
#include <jansson.h>
#include "request.h"
#include "file.h"
#include <time.h>

char* Response_serverInfo(void) {
    char serverT[100];
    const char name[] = "HTTP server";
    const char surname[] = "Tanya Ryabokon";

    time_t currentTime = time(NULL);
    struct tm * lcl = localtime(&currentTime);
    strftime(serverT, 50, "%X", lcl);

    json_t * jobj = json_object();
    json_object_set(jobj, "title", json_string(name));
    json_object_set(jobj, "developer", json_string(surname));
    json_object_set(jobj, "time", json_string(serverT));

    char *jsonString = json_dumps(jobj, JSON_COMPACT);
    json_decref(jobj);
    return jsonString;
}

Request Request_parse(const char * str) {
    Request req = {
            .command = ""
    };
    if(str[0] != '\0') {
        char* protocolchr = strstr(str, " HTTP");
        strncpy(req.command, str, protocolchr - str);
    }
    return req;
}

void Request_process(Request* req, Response* resp, List* actors) {
    char* com = req->command;
    if(strncmp(com, "GET", 3) == 0) {
        char* start = strchr(com, '/') + 1;
        if(strlen(start) == 0 || *start == ' ') {
            Response_success(resp, Response_serverInfo());
        } else {
            if(strstr(start, "file") != NULL) {
                start += strlen("file");
                if(strlen(start) == 0) {
                    Response_success(resp, File_fileToJson("/home/tanya/projects/progbase2/labs/lab8/data/data.txt"));
                } else if(strstr(start, "/data") != NULL) {
                    Response_success(resp, File_fileContent("/home/tanya/projects/progbase2/labs/lab8/data/data.txt"));
                } else {
                    Response_badRequest(resp);
                }
            } else if(strstr(start,"favourites") != NULL) {
                start += strlen("favourites");
                if(*start == ' ' || strlen(start) == 0) {
                    Response_success(resp, List_toJson(actors));
                } else if(*start == '?') {
                    start++;
                    char field[20];
                    char data[20];
                    char* character = strchr(start, '=');
                    strncpy(field, start, character - start);
                    character++;
                    strcpy(data, character);

                    List* list = List_filterByField(actors,field, data);
                    if(List_count(list) == 0 || list == NULL) {
                        Response_notFound(resp);
                    } else {
                        Response_success(resp, List_toJson(list));
                    }
                } else if(*start == '/') {
                    int index = -1;
                    sscanf(start,"/%i", &index);
                    int id = List_containsById(actors, index);
                    if(id != -1) {
                        Actor * node = List_get(actors,id);
                        Response_success(resp, Actor_toJson(node));
                    } else {
                        Response_notFound(resp);
                    }
                } else {
                    Response_badRequest(resp);
                }
            }  else {
                Response_badRequest(resp);
            }
        }
    } else {
        Response_badRequest(resp);
    }
}

void Response_toMessage(Response* res, NetMessage * message) {
    char msg[BUFFER_SIZE];
    if(strlen(res->data)!=0) {
        sprintf(msg,"HTTP/1.0 %i %s\n"
                "Content-type: text/json\n"
                "Content-length: %i\n"
                "%s", res->status, res->description, (int)strlen(res->data), res->data);
    } else {
        sprintf(msg,"HTTP/1.0 %i %s",res->status,res->description);
    }
    NetMessage_setDataString(message, msg);
}

void Response_badRequest(Response* responce) {
    responce->status = 400;
    strcpy(responce->description,"Bad request");
}

void Response_notFound(Response* responce) {
    responce->status = 404;
    strcpy(responce->description,"Not found");
}

void Response_success(Response* responce, char* data) {
    responce->status = 200;
    strcpy(responce->description, "OK");
    strcpy(responce->data, data);
}

void Response_initialize(Response* self) {
    self->status = 0;
    strcpy(self->description, "");
    strcpy(self->data, "");
}