/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ros_listner.cpp
 * Author: user
 * 
 * Created on 22 May, 2018, 4:08 PM
 */

#include "ros_listner.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
 // ROS_INFO("I heard: [%s]", msg->data.c_str());
  if(!strcmp(msg->data.c_str(),TURN_ON_COMMAND))
  {
      std::cout <<"TURN ON COMMAND FOUND"<<std::endl;
  }
  if(!strcmp(msg->data.c_str(),TURN_OFF_COMMAND))
  {
      std::cout <<"TURN OFF COMMAND FOUND"<<std::endl;
  }
  if(!strcmp(msg->data.c_str(),GET_STATUS_COMMAND))
  {
      std::cout <<"GET STATUS COMMAND "<<std::endl;
  }

  
  
  else{
 /// std::cout<<"I heard["<<msg->data.c_str()<<"]"<<std::endl;
  }}

ros_listner::ros_listner() {
  ros::init(argc_, argv_, "listener");
 
static  ros::NodeHandle n;
ros::Subscriber sub;
  //sub = n.subscribe("chatter", 1000,chatterCallback);
  sub = n.subscribe("chatter",1000,chatterCallback);
nodePtr=&n;
SubscriberPtr=&sub;
  ros::spin();

}

ros_listner::ros_listner(const ros_listner& orig) {
}

ros_listner::~ros_listner() {
}


//void ros_listner::chatterCallback(const std_msgs::String::ConstPtr& msg){
// ROS_INFO("I heard: [%s]", msg->data.c_str());
//
//std::cout<<"I heard["<<msg->data.c_str()<<"]"<<std::endl;
//}