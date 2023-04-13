#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
void main(){
	//hamming code for sender
	int data[7], i;
	char datatosend[7] = "0000000";
	
	int serversocket,client_socket,bindstatus,a,b,sum=0;
	struct sockaddr_in serveraddress;
	
    printf("\nEnter 4-bit data :-\n");
    scanf("%d",&data[0]);
    scanf("%d",&data[1]);
    scanf("%d",&data[2]);
    scanf("%d",&data[4]);
    
    //Calculation of even parity
    data[6]=data[0]^data[2]^data[4];
	data[5]=data[0]^data[1]^data[4];
	data[3]=data[0]^data[1]^data[2];
    
    printf("\nEncoded Data :- ");
    for(i=0;i<7;i++){
    	printf("%d", data[i]);
	}
	//data encoded send to receiver
	
	for(i=0;i<7;i++){
		if(data[i]==0){
			datatosend[i]='0';
		}else{
			datatosend[i]='1';
		}
	}
	
	//socket connection
	serversocket=socket(AF_INET,SOCK_STREAM,0);
	serveraddress.sin_family=AF_INET;
	serveraddress.sin_port=htons(1234);
	serveraddress.sin_addr.s_addr= INADDR_ANY;

	bindstatus=bind(serversocket,(struct sockaddr *)&serveraddress, sizeof(serveraddress));
	if(bindstatus<0)
		printf("\nbinding failed\n");
	else
		printf("\nbinding is successful\n");

	listen(serversocket,3);
	printf("Sending data...\n");

	client_socket=accept(serversocket,NULL,NULL);
	if(client_socket<0)
		printf("connection rejected\n");
	else
		printf("Connected...\n");
	printf("\n");
	
	//send data
	send(client_socket , datatosend , 7 , 0 );
	printf("\nData sent.\n");

	close(serversocket);
}
