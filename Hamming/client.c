#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main(){
	//receiver code for hamming
    int data[10],c,c1,c2,c3,i;
    
	int clientsocket,a,b,sum;
	char serverresponse[256], datareceived[7];
	struct sockaddr_in serveraddress;

	//get data from reciever
	clientsocket=socket(AF_INET,SOCK_STREAM,0);// create socket
	//SOCKET function returns the integer
	if(clientsocket<0)
		printf("socket not created\n");
	else 
		printf("socket created succesfully\n");
	serveraddress.sin_family=AF_INET;
	serveraddress.sin_port=htons(1234);
	serveraddress.sin_addr.s_addr= INADDR_ANY;
	int constatus=connect(clientsocket,(struct sockaddr *) &serveraddress, sizeof(serveraddress));
	 
	if(constatus==-1)
		printf("Connectivity not establshed\n");
	else
		printf("connection estableshed\n");
	int len=sizeof(datareceived);
	recv(clientsocket,&datareceived,len,0);
	close(clientsocket);
	
	 
	//convert data to integer
	for(i=0;datareceived[i]!='\0';i++){
		data[i]=(int)datareceived[i];
		data[i]-=48;
	}

    c1=data[6]^data[4]^data[2]^data[0];
	c2=data[5]^data[4]^data[1]^data[0];
	c3=data[3]^data[2]^data[1]^data[0];
	c=c3*4+c2*2+c1 ;
 
	printf("\nData received : ");
	for(i=0;i<7;i++){
		printf("%d",data[i]);
	}
    if(c==0) {
		printf("\nNo error while transmission of data\n");
    }
	else {
		printf("\nError on position %d",c);
		
		printf("\nCorrect message is\n");
		//if errorneous bit is 0 we complement it else vice versa
		if(data[7-c]==0){
			data[7-c]=1;
		}
        else{
			data[7-c]=0;
		}
		for (i=0;i<7;i++) {
			printf("%d",data[i]);
		}
	}
}
