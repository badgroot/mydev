// g++ modbus_tcp_read.cpp -o modbus_tcp_read -lmodbus

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <modbus/modbus.h>
#include <string.h>
#include <cstdlib>
enum{
APP=0,
IP,
PORT,
SLAVEID,
REG,
COUNT

};
void USEINFO(char *p){
printf("USAGE: %s IP PORT  SLAVEID REG COUNT \n",p);
}
int main(int argc,char *argv[])
{char *appname=argv[APP];

	if(argc<5)
	{
	USEINFO(appname);
	return 0;		
	}
char *ip=argv[IP];
int port =std::atoi(argv[PORT]);
int reg = std::atoi(argv[REG]);	
int count =std::atoi(argv[COUNT]);
int slave =std::atoi(argv[SLAVEID]);
std::cout<<"IP "<<ip<<"port "<<port<<"reg"<< reg <<"count" <<count<<std::endl;

//return 0;
//// MOdbus 
modbus_t *ctx;
ctx=modbus_new_tcp(ip,port);
if(ctx){
if(modbus_set_slave(ctx, slave)!=0)
{
	fprintf(stderr,"set_slave_failed : %s",modbus_strerror(errno));
}

if( modbus_connect(ctx)!=-1)
{printf("modbus_connection established \n");
int rc;
uint16_t dest[64];
memset(dest,0,64);
rc=modbus_read_registers(ctx,reg,count,dest);

if(rc==-1)
{

fprintf(stderr,"MODBUS READ FIALED: %s\n",modbus_strerror(errno));	

}
else{
	printf("Modbus read succesfully  \n");
	for (int i=0; i < rc; i++) {
    printf("reg[%d]=%d (0x%X)\n", i+reg, dest[i], dest[i]);
}
}


}

else{

fprintf(stderr,"MODBUS CONNECT FIALED : %s\n",modbus_strerror(errno));	

}





}
else{

	fprintf(stderr," MODBUS NEW TCP FAILED :%s\n",modbus_strerror(errno));
}
if(ctx){
	modbus_close(ctx);

modbus_free(ctx);
}



}