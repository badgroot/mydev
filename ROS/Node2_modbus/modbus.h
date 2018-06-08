/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   modbus.h
 * Author: user
 *
 * Created on 22 May, 2018, 4:10 PM
 */

#ifndef MODBUS_H
#define MODBUS_H
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <modbus/modbus.h>
#include <unistd.h>
#include <cstddef>
#include <fstream>
#include <string>
#include "config.h"

enum Register{
    CONTROL=1100,
    STATUS=1200


};

class modbus {
public:
    modbus();
    modbus(const modbus& orig);
    virtual ~modbus();
   int write(int address,int value);
   int read(int address,int nb);
   void set_config_from_header();
   void set_config_from_file();
   void json_format_print();
   void print_conf();
private:
   void set_config();
    modbus_t *ctx;
    int baudRate;
    int slaveId;
    int dataBits ;
    int stopBits ;
    int retryCount;
    std::string deviceName;
    uint16_t regs[10];
    int status_reg;
    int control_reg;
    char* format_string;
 //  std::string format_string;
};

#endif /* MODBUS_H */

