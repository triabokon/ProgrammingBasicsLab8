//
// Created by tanya on 27.05.17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <progbase.h>
#include <progbase/net.h>
#include <progbase/console.h>

#define BUFFER_LEN 1024

void displayMenu(void);
void createHttpRequest(int num, char *request);

int main() {

    int port = 3000;

    TcpClient * client = TcpClient_init(&(TcpClient){});
    IpAddress * serverAddress = IpAddress_init(&(IpAddress){}, "127.0.0.1", port);

    NetMessage * message = NetMessage_init(
            &(NetMessage){},
            (char[BUFFER_LEN]){},
            BUFFER_LEN);
    if (!TcpClient_connect(client, serverAddress)) {
        perror("tcp connect");
        return 1;
    }

    while(1) {
        int choice = 0;
        char req[100] = "";

        displayMenu();
        scanf("%i", &choice);
        getchar();
        createHttpRequest(choice, req);

        if(strcmp(req, "ext") == 0)
            return  0;

        NetMessage_setDataString(message, req);

        printf("Send `%s` to server %s:%d\n",
               message->buffer,
               IpAddress_address(serverAddress),
               IpAddress_port(serverAddress));
        if (!TcpClient_send(client, message)) {
            perror("send");
            return 1;
        }
        //
        // receive response from server
        if (!TcpClient_receive(client, message)) {
            perror("recv");
            return 1;
        }
        printf("Response received from server (%d bytes): \n%s\r\n",
               message->dataLength,
               message->buffer);

        getchar();
    }
    TcpClient_close(client);
    return 0;
}

void createHttpRequest(int num, char *request) {
    char field[20];
    char value[20];
    switch(num) {
        case 1:
            strcpy(request,"GET / HTTP/1.0");
            break;
        case 2:
            strcpy(request,"GET /favourites HTTP/1.0");
            break;
        case 3:
            printf("Please, enter name of field and data:\n");
            scanf(" %s %[^\n]", field, value);
            getchar();
            sprintf(request, "GET /favourites?%s=%s HTTP/1.0", field, value);
            break;
        case 4:
            printf("Please, enter id of actor:\n");
            scanf(" %s", value);
            getchar();
            sprintf(request, "GET /favourites/%s HTTP/1.0", value);
            break;
        case 5:
            strcpy(request,"GET /file HTTP/1.0");
            break;
        case 6:
            strcpy(request,"GET /file/data HTTP/1.0");
            break;
        case 7:
            strcpy(request, "ext");;
            break;
        default:
            request[0] = '\0';
            break;
    }
}

void displayMenu(void) {
    conClear();
    char menu[][100] = {
            " 1. Display information about server",
            " 2. Display favourite actors",
            " 3. Find actor by value of field",
            " 4. Find actor by id",
            " 5. Display file information and content",
            " 6. To get all numbers on even positions",
            " 7. Exit",
            " Select:"
    };
    for(int i = 0; i < sizeof(menu)/sizeof(menu[0]);i++) {
        puts(menu[i]);
    }
}

