/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ros_listner.h
 * Author: user
 *
 * Created on 22 May, 2018, 4:08 PM
 */

#ifndef ROS_LISTNER_H
#define ROS_LISTNER_H
#include "ros/ros.h"
#include "modbus.h"
#include "std_msgs/String.h"
#include <iostream>
#include <string.h>

#define TURN_ON_COMMAND  "Hello World10"
#define TURN_OFF_COMMAND "Hello World46"
#define GET_STATUS_COMMAND "Hello World22"


extern int argc_;
extern char **argv_;
class ros_listner {
public:
    ros_listner();
    ros_listner(const ros_listner& orig);
    virtual ~ros_listner();
   // void chatterCallback(const std_msgs::String::ConstPtr& );
private:
    
ros::NodeHandle *nodePtr;
ros::Subscriber *SubscriberPtr;
};
extern modbus modbusptr;
#endif /* ROS_LISTNER_H */

