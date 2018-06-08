/*
g++ listner.cpp -o listener -I /opt/ros/kinetic/include/ -L /opt/ros/kinetic/lib/  -lrosconsole -lroscpp -lroscpp_serialization


 */


#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());

std::cout<<"I heard["<<msg->data.c_str()<<"]"<<std::endl;
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");
std::cout<<"I heard[HIMANSHU]"<<std::endl;
 
  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  ros::spin();


  return 0;
}
// %EndTag(FULLTEXT)%