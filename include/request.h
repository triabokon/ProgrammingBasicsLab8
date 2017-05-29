//
// Created by tanya on 28.05.17.
//

/** @file
    @brief module for HTTP communication / Request and Response
*/

#pragma once

#include <progbase/net.h>
#include <progbase/list.h>

#define COMMAND_LENGTH 200
#define BUFFER_SIZE 1024

/**
    @struct Response
    @brief defines new type called Response for HTTP communication to store data
*/
typedef struct {
    int status;
    char data[BUFFER_SIZE];
    char description[COMMAND_LENGTH];
} Response;

/**
    @struct Request
    @brief defines new type called Request for HTTP communication to store data
*/
typedef struct {
    char command[COMMAND_LENGTH];
} Request;

/**
    @brief parses HTTP request message
    @param str - request message
    @returns structure Request
*/
Request Request_parse(const char * str);

/**
    @brief processes Request and forms Response
    @param request - Request element to be processed
    @param response - new Response structure
    @param actors - list of Actors
*/
void Request_process(Request* request, Response* response, List* actors);

/**
    @brief forms Response structure
*/
void Response_initialize(Response* self);

/**
    @brief forms Response structure with 404 Not found status
*/
void Response_notFound(Response* response);

/**
    @brief forms Response structure with 400 Bad request status
*/
void Response_badRequest(Response* response);

/**
    @brief response message to a client
    @param response - Response structure with information
    @param message - message to be sent to client
*/
void Response_toMessage(Response* response, NetMessage * message);

/**
    @brief forms Response structure with 200 OK status
    @param data - string that sets to Response
*/
void Response_success(Response* response, char* data);

/**
    @brief string with information about server
    @returns json string with information about server
*/
char* Response_getServerInfo(void);
