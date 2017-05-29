//
// Created by tanya on 27.05.17.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <progbase/net.h>
#include <progbase/list.h>
#include "actor.h"
#include "request.h"
#include "file.h"
#include <time.h>

#define BUFFER_LEN 10240

int main(int argc, char * argv[]) {
//    if (argc < 2) {
//        puts("Please, specify server port in command line arguments");
//        return 1;
//    }
    srand(time(0));
    const int port = 3000 /*atoi(argv[1])*/;

    TcpListener * server = TcpListener_init(&(TcpListener){});
    IpAddress * address = IpAddress_initAny(&(IpAddress){}, port);
    if(!TcpListener_bind(server, address)) {
        perror("tcp bind");
        return 1;
    }
    if (!TcpListener_start(server)) {
        perror("tcp server start");
        return 1;
    }
    printf("TCP Server is listening on port %d\n",
           IpAddress_port(TcpListener_address(server)));

    NetMessage * message = NetMessage_init(
            &(NetMessage){},
            (char[BUFFER_LEN]){},
            BUFFER_LEN);

    TcpClient client;

    List* actors = File_readAsJson("/home/tanya/projects/progbase2/labs/lab8/data/source.json");
    puts(">> Waiting for connection...");
    TcpListener_accept(server, &client);
    while (1) {

        if(!TcpClient_receive(&client, message)) {
            perror("recv");
            return 1;
        }
        IpAddress * clientAddress = TcpClient_address(&client);
        printf(">> Received message from %s:%d (%d bytes): `%s`\n",
               IpAddress_address(clientAddress),
               IpAddress_port(clientAddress),
               NetMessage_dataLength(message),
               NetMessage_data(message));

        Request req = Request_parse(NetMessage_data(message));
        Response res;
        Response_initialize(&res);
        Request_process(&req,&res, actors);
        Response_toMessage(&res, message);

        if(!TcpClient_send(&client, message)) {
            perror("send");
            return 1;
        }
        printf(">> String sent to client:\r\n%s\r\n", NetMessage_data(message));
    }
    TcpClient_close(&client);
    TcpListener_close(server);
    List_free(&actors);
    return 0;
}