/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ros_talker.cpp
 * Author: user
 * 
 * Created on 22 May, 2018, 11:17 AM
 */

#include "ros_talker.h"

ros_talker::ros_talker(int argc_,char **argv_) {
   ros::init(argc_,argv_,"Talker");
    Nodeptr= nullptr;
    static ros::NodeHandle Node_obj;
    static ros::Publisher chatter_pub_obj=Node_obj.advertise<std_msgs::String>("chatter",1000);
// chatter_pub=Nodeptr->advertise<std_msgs::String>("chatter",1000);//advertise<std_msgs::String>("chatter",1000);
chatter_pub=&chatter_pub_obj;
Nodeptr=&Node_obj;
    loopRatePtr= new ros::Rate(1);
count=0;
    

}

ros_talker::ros_talker(const ros_talker& orig) {
}

ros_talker::~ros_talker() {
}

void ros_talker::publish_data(std::string ab){
    while(ros::ok())
{std_msgs::String msg;
if(get_publish_data_flag() ){
if(chatter_pub->getNumSubscribers())
{
	//std::stringstream ss;
	
        
	msg.data=ss.str();
        
        ROS_INFO("%s",msg.data.c_str());
	chatter_pub->publish(msg);
	ros::spinOnce();
        
        if(chatter_pub->isLatched())
        {ROS_INFO("%s","Data latched");
            
        }
        loopRatePtr->sleep();
        ss.str("");
        clear_publish_data_flag();
        
        
   
++count;

}

}}

}
void ros_talker::set_publish_data_flag(){
    publish_data_flag=true;
}
    void ros_talker::clear_publish_data_flag(){
    publish_data_flag=false;
    }
    bool ros_talker::get_publish_data_flag(){
      return  publish_data_flag;
    }
    void ros_talker::setString(std::string str){
        ss<<str;
    }