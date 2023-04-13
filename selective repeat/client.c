#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
int main()
{
    ;
    printf("\nEnter the Data size:");
    int n;
    scanf("%d", &n);
    printf("\nEnter the Frame size:");
    int f;
    scanf("%d", &f);
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9000);
    int con = connect(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (con < 0)
        printf("\n Falied to connect");
    write(client_socket, &n, sizeof(n));
    write(client_socket, &f, sizeof(f));
    int j = 0, ack = 0, pre = -1, count = 1, c = 1;
    for (int i = 0; i < n + f; i++)
    {
        if (i < f)
        {
            write(client_socket, &i, sizeof(j));
            printf("\nBit sent:%d", i);
        }
        else
        {
            read(client_socket, &ack, sizeof(j));
            c = 1;
            if (ack != pre + 1 && count != 2)
            {
                count = 2;
                c = 2;
                ack += 1;
                printf("\n acknowlegement not received for the bit =%d", ack);
                write(client_socket, &ack, sizeof(ack));
                printf("\nbit sent=%d", ack);
                read(client_socket, &ack, sizeof(j));
                printf("\nacknowlegement received :%d", ack);
            }
            if (c != 2 && ack <= n)
                printf("\n acknowlegement received:%d", ack);
            if (i < n)
            {
                write(client_socket, &i, sizeof(ack));
                printf("\nbit sent:%d", i);
            }
            pre++;
        }
    }
}