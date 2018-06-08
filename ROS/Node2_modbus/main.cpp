#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include "ros_listner.h"
#include "modbus.h"
int argc_;
char **argv_;
modbus *modbusptr;

int main(int argc, char **argv)
{
    argc_=argc;
    argv_=argv;
    modbus modbusObj;
    modbusptr=&modbusObj;
    
    
    ros_listner ab;
    
   // while(1);
//  ros::init(argc, argv, "listener");
//std::cout<<"I heard[HIMANSHU]"<<std::endl;
// 
//  ros::NodeHandle n;
//
// 
//  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
//
//  ros::spin();

    

  return 0;
}