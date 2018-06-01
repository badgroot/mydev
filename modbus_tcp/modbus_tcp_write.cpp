//// g++ modbus_tcp_write.cpp -o modbus_tcp_write -lmodbus

#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <modbus/modbus.h>
#define RETRY 3

enum argumemts{
APP=0,
IP,
PORT,
SLAVEID,
REG,
VALUE
}Arguments;
void usage(char *p){
printf("USAGE: %s IP PORT SLAVEID REG VALUE \n",p);
}
int main(int argc,char *argv[])
{
if(argc<4)
{usage(argv[APP]);
	return 0;
}
char *appname=argv[APP];
char *ip=argv[IP];
int port=std::atoi(argv[PORT]);
int reg =std::atoi(argv[REG]);
int value=std::atoi(argv[VALUE]);
int slave =std::atoi(argv[SLAVEID]);
modbus_t *ctx;
ctx =modbus_new_tcp(ip,port);

if(ctx==NULL)
{
	fprintf(stderr, "unable to allocate libmodbus context \n" );
	return -1;
}
if(modbus_set_slave(ctx, slave)==-1)
{
fprintf(stderr,"modbus setslave failed : %s\n",modbus_strerror(errno));
}
if(modbus_connect(ctx)==-1)
{
fprintf(stderr,"connection failed : %s\n",modbus_strerror(errno));
modbus_free(ctx);
return -1;
}

if(modbus_write_register(ctx, reg, value)==-1){
	fprintf(stderr,"write failed : %s\n",modbus_strerror(errno));
	modbus_free(ctx);
	return -1;
}




}
