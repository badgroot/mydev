/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ros_talker.h
 * Author: user
 *
 * Created on 22 May, 2018, 11:17 AM
 */

#ifndef ROS_TALKER_H
#define ROS_TALKER_H
#include <ros/ros.h>
#include <std_msgs/String.h>


#include<sstream>
#include<iostream>
class ros_talker {
public:
    ros_talker(int argc,char **argv);
    ros_talker(const ros_talker& orig);
    virtual ~ros_talker();
    void publish_data(std::string);
    void set_publish_data_flag();
    void clear_publish_data_flag();
    bool get_publish_data_flag();
    void setString(std::string);
    
private:
    std::string NodeName;
   ros::NodeHandle *Nodeptr;
    ros::Publisher *chatter_pub;
    int count=0;
    std::stringstream ss;
   ros::Rate *loopRatePtr;
   bool publish_data_flag;
};

#endif /* ROS_TALKER_H */

