/*
gcc server.c -o server
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main(int argc,char *argv[]){
int socket_fd,new_socket,valread;
struct  sockaddr_in address;
int opt=1;
int addrlen=sizeof(address);
char buffer[1024]={0};
char *hello="Hello from server";
if((socket_fd=socket(AF_INET,SOCK_STREAM,0) )==0)
{
	perror("socket failed\n");
	exit(EXIT_FAILURE);
}

if(setsockopt(socket_fd, SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt, sizeof(opt))){
	perror("setsockopt failure");
	exit(EXIT_FAILURE);
}
address.sin_family=AF_INET;
address.sin_port=htons(PORT);
if(bind(socket_fd,(struct sockaddr *) &address, addrlen)){
	perror("bind failure");
	exit(EXIT_FAILURE);
}
if(listen(socket_fd, 3)<0)
{
perror("listned failure()");
exit(EXIT_FAILURE);

}
 if ((new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){

perror("accept failed");
exit(EXIT_FAILURE);
}
valread=read(new_socket,buffer,1024);
printf("%s\n",buffer );
send(new_socket,hello,strlen(hello),0);
printf("Hello Message Sent to client\n");
return 0;
}

