#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
// Test data : 01111110
int main()
{
char data[50]={0},byte[50]={0};
char flag[10]={0};
char esc[10]={0};
int i,count=0;
strcpy(flag,"01111110");
strcpy(esc,"00011011");
printf("Enter tha data :");
scanf("%s",data);
printf("\n\n");
while(strlen(data)<=8){
if(strlen(data)==8){
break;
}
strcat(data,'0');
}
if(strcmp(flag,data)==0){
strcat(byte,flag);
strcat(byte,esc);
strcat(byte,data);
strcat(byte,flag);
}
else{
strcat(byte,flag);
strcat(byte,data);
strcat(byte,flag);
}
printf("Data after Byte Stuffing is : %s\n",byte);
int client_socket;
client_socket=socket(AF_INET,SOCK_STREAM,0);
if(client_socket<0)
printf("\nFalied in socket creation");
struct sockaddr_in client_address;
client_address.sin_family=AF_INET;
client_address.sin_addr.s_addr=INADDR_ANY;
client_address.sin_port=htons(9000);
int con_status=connect(client_socket,(struct sockaddr*)&client_address,sizeof(client_address));
if(con_status)
printf("\nFailed in connection");
write(client_socket,byte,50);
write(client_socket,data,50);
close(client_socket);
return 0;
}