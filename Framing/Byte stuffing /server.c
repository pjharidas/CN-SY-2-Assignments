
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
int main()
{
    int client_socket, server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(9000);
    int bind_status = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (bind_status < 0)
        printf("\nbinding failed");
    listen(server_socket, 5);
    int clength = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &clength);
    char byte[50] = {0}, data[50] = {0}, distuff[50] = {0};
    int i = 0;
    char esc[10] = {0};
    strcpy(esc, "00011011");
    read(client_socket, byte, 50);
    read(client_socket, data, 50);
    printf("data recieved from client is : %s\n", byte);
    printf("after destuffing original data is : %s\n", data);
    close(server_socket);
    return 0;
}