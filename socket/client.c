#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8081


int main(int argc,char *argv[]){


	struct sockaddr_in address;
	int sock=0,valread;
	struct sockaddr_in serv_addr;
	char *hello = "hello from client";
	char buffer[1024];
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(buffer,0,sizeof(buffer));
	memset(&serv_addr,'0',sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);
	if(inet_pton(AF_INET,"72.142.168.226",&serv_addr.sin_addr)<=0){
		printf("\n invalid address /  Address not support\n");
		return -1;
	}

if(connect(sock, (const struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
{
printf("connection failed\n");
return -1;	
}
send(sock,hello,strlen(hello),0);
printf("hello message sent\n");
valread=read(sock,buffer,1024);
printf("%s\n",buffer );
return 0;
}
