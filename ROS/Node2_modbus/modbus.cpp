/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   modbus.cpp
 * Author: user
 * 
 * Created on 22 May, 2018, 4:10 PM
 */

#include "modbus.h"

modbus::modbus() {
    ctx=NULL;
    set_config_from_file();
    print_conf();
    
}

modbus::modbus(const modbus& orig) {
}

modbus::~modbus() {
     modbus_free(ctx);

}

int modbus::write(int address, int value){
    if(ctx)
    {modbus_set_slave(ctx,slaveId);
    if(modbus_connect(ctx)==0)
    {
        for(int i=0;i<retryCount;i++)
        {
        //int modbus_write_register(modbus_t *ctx, int addr, int value);
            if(modbus_write_register(ctx,address,value)!=-1)
            {std::cout<<address+i<<":"<<value<<std::endl;
               break;
            
            }
            else{
             std::cout << "modbus_read_registers:" << modbus_strerror(errno) << std::endl;
            
            }
         usleep(1000 * 500);
          
        }
    
    }
    
    modbus_close(ctx);
    
    }
    else{
     std::cout << "modbus_new_rtu:" << modbus_strerror(errno) << std::endl;
    }
}
int modbus::read(int address, int nb){
    uint16_t regs[nb];
     if(ctx)
    {modbus_set_slave(ctx,slaveId);
    if(modbus_connect(ctx)==0)
    {
        for(int i=0;i<retryCount;i++)
        {
        //int modbus_read_registers(modbus_t *ctx, int addr, int nb, uint16_t *dest);
            if(modbus_read_registers(ctx,address,nb,regs)!=-1)
            {std::cout<<address+i<<":"<<regs[i]<<std::endl;
               break;
            
            }
            else{
             std::cout << "modbus_read_registers:" << modbus_strerror(errno) << std::endl;
            
            }
         usleep(1000 * 500);
          
        }
    
    }
    
    modbus_close(ctx);
    
    }
    else{
     std::cout << "modbus_new_rtu:" << modbus_strerror(errno) << std::endl;
    }
}
void modbus::set_config(){
baudRate=9600;
        slaveId=1;
        dataBits=8;
        stopBits=1;
        deviceName="ttyUSB0";
        ctx = modbus_new_rtu(deviceName.c_str(),baudRate,'N',dataBits,stopBits);
        retryCount=3;
}
void modbus::set_config_from_header(){
        baudRate=BAUD;
        slaveId=SLAVEID;
        dataBits=DATABITS;
        stopBits=STOPBITS;
        deviceName=DEVICE;
        retryCount=RETRYCOUNT;
        
        ctx = modbus_new_rtu(deviceName.c_str(),baudRate,'N',dataBits,stopBits);
        if(ctx==NULL)
        {
            std::cout << "modbus_new_rtu:" << modbus_strerror(errno) << std::endl;
            std::cout<<"exit";
                    std::exit(EXIT_FAILURE);
        }
}
void modbus::set_config_from_file(){
Json::Reader reader;
Json::StyledStreamWriter writer;
Json::Value root;

    char buffer[MAXLINE];
    
    std::ifstream infile;
    infile.open(CONFIG_FILE);
    if(!infile.is_open()){
        std::cout<<"could not open "<<CONFIG_FILE<<std::endl;
        std::exit(EXIT_FAILURE);
    }
       /*
     deviceid=ttyUSB0,
baudrate=115200,
slaveid=1,
databit=8,
stopbit=1,
retrycount=3,

     */
    
//     while (infile)
//   {
//       infile.getline(buffer, MAXLINE);
//       std::cout << buffer <<std::endl;
//   }
    if(!reader.parse(infile,root,false))
    {
        std::cout << reader.getFormattedErrorMessages()<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    if(root.empty()){
        std::cout<<"Empty file"<<std::endl;
         std::exit(EXIT_FAILURE);
    }
    if(root.isMember("devicename")&&root.isMember("baudrate")&&root.isMember("slaveid")&&root.isMember("databit")&&root.isMember("stopbit") &&root.isMember("controlreg") &&root.isMember("statusreg")&&root.isMember("retrycount") )
    {   }
    else {
        std::cout<<"something missing in json file\n";
    }
    if(root["devicename"].isString())
    {deviceName=root["devicename"].asString();
    }
    else {json_format_print();
        
    }
    if(root["baudrate"].isInt())
    {
       baudRate= root["baudrate"].asInt();
    }
    else{json_format_print();
    }
    if(root["slaveid"].isInt())
    {
         slaveId=root["slaveid"].asInt();
    }
    else{json_format_print();
    }
    
    if(root["databit"].isInt())
    {
        
        dataBits=root["databit"].asInt();
    }
    else{json_format_print();
    }
    
    if(root["stopbit"].isInt())
    {
        stopBits=root["stopbit"].asInt();
    }
    else{json_format_print();
    }
    
    if(root["retrycount"].isInt())
    {
        
        retryCount=RETRYCOUNT;
        
    }
    else{
json_format_print();
    }
    
    if(root["statusreg"].isInt())
    {   status_reg=root["stopbit"].asInt();
    }
    else{
        json_format_print();
    }
     if(root["controlreg"].isInt())
    {   control_reg=root["controlreg"].asInt();
    }
    else{json_format_print();
    }
    //std::cout<<root.toStyledString()<<std::endl;
    
       
        
    
    infile.close();
    
}
void modbus::json_format_print(){
    char format_string[]="{\"baudrate\" : 115200,\"controlreg\" : 1100,   \"databit\" : 8, \"devicenam\" : \"ttyUSB\",   \"retrycount\" : 3,  \"slaveid\" : 1, \"statusreg\" : 1200,   \"stopbit\" : 1}";
    Json::Reader reader;
Json::Value root;
std::cout<<"varify with this schema"<<std::endl;
    if(reader.parse(format_string,root,false))
        
            std::cout<<root.toStyledString()<<std::endl;


}
void modbus::print_conf(){
    std::cout<<"Current configuration\n";
    std::cout<<"deviceName  "<<deviceName<<std::endl;
std::cout<<"Baud rate  "<<baudRate<<std::endl;
std::cout<<"slaveId  "<<slaveId<<std::endl;
        std::cout<<"dataBits "<<dataBits<<std::endl;
        std::cout<<"stopBits  "<<stopBits<<std::endl;
        std::cout<<"status_reg  "<<status_reg<<std::endl;
        std::cout<<"control_reg "<<control_reg<<std::endl;
       
}