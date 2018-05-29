#include <iostream>
#include <modbus/modbus.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
/*
DeviceName
baudRate
Startbit
stopbit
register
value


*/
typedef enum Arguments {
  APP_NAME = 0,
  DEV_NAME,
  BAUD_RATE,
  SLAVE_ID,
  DATA_BITS,
  STOP_BITS,
  ADDRESS,
 	VALUE
} Arguments;
int main(int argc,char *argv[])
{
char *deviceName;
int baudRate;
int dataBit;
int stopBit;
int register_address;
int value;
int slaveid;

if(argc <6)
{

printf("USAGE: ./modbus_write_rtu deviceName baudRate SLAVEID dataBit stopbBit register_address value\n");
return 0;
}
modbus_t *ctx = NULL;
deviceName=argv[DEV_NAME];
baudRate=std::atoi(argv[BAUD_RATE]);
slaveid=std::atoi(argv[SLAVE_ID]);
dataBit=std::atoi(argv[DATA_BITS]);
stopBit=std::atoi(argv[STOP_BITS]);
register_address=std::atoi(argv[ADDRESS]);
value=std::atoi(argv[VALUE]);


std::cout<<"device name "<<deviceName<<std::endl   	
			<<"baud rate  "<< baudRate<<std::endl
			<<"slaveId  "<<slaveid<<std::endl
			
			<<"dataBit  "<<dataBit<<std::endl 
			<<"StopBit   "<<stopBit<<std::endl
			<<"address   "<<register_address<<std::endl
			<<"value     "<<value<<std::endl;
		//return 0;

//modbus_t *modbus_new_rtu(const char *device, int baud, char parity, int data_bit, int stop_bit);

ctx=modbus_new_rtu(deviceName,baudRate,'N',dataBit,stopBit);
if(ctx){
				if(modbus_set_slave(ctx, slaveid)==0)
				{		if(modbus_connect(ctx)==0)
						{
								for(int i=0;i<3;i++){

											if(modbus_write_register(ctx, register_address,value)!=-1){
											std::cout<<	register_address+i <<": written successsfully"<<std::endl;
											break;
											}
											else{
											std::cout<<modbus_strerror(errno)<<std::endl;
											}
								usleep(1000 * 500);
										}

						}

				}
				else {
	
					std::cout<<"unabel to set slave id"<<std::endl;
					 fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));

				}

}
else{
std::cout<<"unable to create new rtu"<<std::endl;
}
modbus_close(ctx);
modbus_free( ctx);
return 0;
}
