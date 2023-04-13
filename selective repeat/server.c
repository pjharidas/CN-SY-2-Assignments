#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
int main()
{
printf("\nserver");
int n;
int client_socket,server_socket;
client_socket=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in client_addr,server_addr;
client_addr.sin_addr.s_addr=INADDR_ANY;
client_addr.sin_family=AF_INET;
client_addr.sin_port=htons(9000);
int con=bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr));
if(con<0) printf("\n Falied to bind");
listen(client_socket,5);
int clength=sizeof(server_addr);
client_socket=accept(client_socket,(struct sockaddr*)&server_addr,&clength);
int j=0,f,ack=0,count=1,c=1;
read(client_socket,&n,sizeof(n));
read(client_socket,&f,sizeof(n));
for(int i=0;i<n+f;i++)
{
if(i<f)
{
read(client_socket,&j,sizeof(j));
printf("\nbit recieved:%d",j);
}
else
{
c=1;
if(i==f+2&&count!=2)
{
printf("\n do you want to send acknowlegement for bit=%d??y/n:",ack);
char ans;
scanf("%c",&ans);
if(ans=='n'&&count!=2)
{
ack-=1;
count=2;
c=2;
write(client_socket,&ack,sizeof(ack));
ack++;
printf("\n sending acknowlegement for :%d",ack);
read(client_socket,&j,sizeof(j));
printf("\nbit received:%d",j);
}
}
write(client_socket,&ack,sizeof(ack));
if(c!=2&&ack<n)
printf("\nsending ack for:%d",ack);
if(i<n){
read(client_socket,&j,sizeof(j));
printf("\n bit received:%d",j);
}
ack++;
}
}
}