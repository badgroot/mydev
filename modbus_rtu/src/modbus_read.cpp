#include <iostream>
#include <modbus/modbus.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
/*
DeviceName
baudRate
Startbit
stopbit
register
count


*/
typedef enum Arguments {
  APP_NAME = 0,
  DEV_NAME,
  BAUD_RATE,
  SLAVE_ID,
  DATA_BITS,
  STOP_BITS,
  ADDRESS,
  COUNT
} Arguments;
int main(int argc,char *argv[])
{
char *deviceName;
int baudRate;
int dataBit;
int stopBit;
int register_address;
int count;
int slaveid;

if(argc <6)
{

printf("USAGE: ./modbus_read_rtu DeviceName baudRate SLAVEID dataBit stopbBit register_address count\n");
return 0;
}
deviceName=argv[DEV_NAME];
baudRate=std::atoi(argv[BAUD_RATE]);
slaveid=std::atoi(argv[SLAVE_ID]);
dataBit=std::atoi(argv[DATA_BITS]);
stopBit=std::atoi(argv[STOP_BITS]);
register_address=std::atoi(argv[ADDRESS]);
count=std::atoi(argv[COUNT]);
//modbus_t *modbus_new_rtu(const char *device, int baud, char parity, int data_bit, int stop_bit);
uint16_t destination[10];
modbus_t *ctx = NULL;
ctx=modbus_new_rtu(deviceName,baudRate,'N',dataBit,stopBit);
if(ctx){
        if(modbus_set_slave(ctx,  slaveid)==0)
        {
              if(modbus_connect(ctx)==0){
                        for(int i=0;i<3;i++){

                                if(modbus_read_registers(ctx, register_address, count, destination)!=-1){
                                std::cout<< register_address+i <<": "<<destination[i]<<std::endl;
                                break;
                                }
                            usleep(1000 * 500);
                                            }

                                      }
          else{

            std::cout<<"Unable to set slave id"<<std::endl;
              fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));

          }

          modbus_close(ctx);
          modbus_free( ctx);

      }
else{
 std::cout<<"Unable to connect to device "<<deviceName<<std::endl;
    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));

}
}
return 0;
}



