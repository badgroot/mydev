#include <iostream>
#include <stdio.h>
#include <jsoncpp/json/json.h>
#include <syslog.h>
#include <fstream>
#include <string> 
#include <syslog.h>
#include <sstream>
#include <time.h>
#include "publisher.h"







Json::Value root;
Json::Reader reader;
Json::StyledStreamWriter writer;
const char *msg1 = "{ \"data\":\"Hello\" }";

//////////mqqt variable/////
std::string username;
std::string password;
std::string server;
int port;
bool debug;
std::string topic;
///////////////////////
void readConfig(const char *path);
void pretask(int argc,char **argv){
openlog("guiapp",LOG_PID|LOG_CONS, LOG_USER);
syslog(LOG_INFO, "logger start ");
readConfig("../conf/conf.json");
}
void endtask(){
syslog(LOG_INFO, "logger end ");
	closelog();
}
void readConfig(const char *path)
{int success;
std::fstream file;
file.open(path);
if(!file){
	std::cerr<<path<<"could not open file"<<std::endl;
	std::exit(EXIT_FAILURE);
}	
success=reader.parse(file, root);
if(file){
	file.close();
}
if(!success){
	std::cerr<<"not parsed.."<<reader.getFormatedErrorMessages()<<std::endl;
	std::exit(EXIT_FAILURE);
}
if(root.empty()){
	std::cerr<<"No member found in jsonc-conf"<<std::endl;
	std::exit(EXIT_FAILURE);
}
if(root["user"].isString()){
username=root["user"].asString();

}
else{
	syslog(LOG_INFO,"username not fount in conf.json");
}

if(root["topic"].isString()){
topic=root["topic"].asString();

}
else{
	syslog(LOG_INFO,"topic not fount in conf.json");
}

if(root["server"].isString()){
server=root["server"].asString();

}
else{
	syslog(LOG_INFO,"server not fount in conf.json");
	server="127.0.0.1";

}

if(root["password"].isString()){
password=root["password"].asString();

}
else{
	syslog(LOG_INFO,"password not fount in conf.json");
	password="";
}
if(root["port"].isInt()){
port=root["port"].asInt();

}
else{
	syslog(LOG_INFO,"port not fount in conf.json");
	port=1883;
}
if(root["debugging"].isBool()){
	debug=root["debugging"].asBool();
}
else{
	syslog(LOG_INFO,"debug flags not found in conf.json");
	debug=true;
}
 std::cout<<"jsonvalue\n"
 		<<"USERNAME  :"<< username<<"\n"
 		<<server<<"\n"
 		<<port<<"\n"
 		<<password<<"\n"
 		<<debug<<"\n"<<std::endl;
}
void run(){
	time_t rawtime;

std::stringstream ss;
std::string str;
int status=1;
publisher pub(username, password,server, port,topic);
pub.pretask();
	std::cout<<"\nEnter new string\n";
while(1){
	if(status==1){
std::getline(std::cin,str);
}
status=0;
//str(ss);
time (&rawtime);
status = pub.publish(ctime (&rawtime));
std::cout<<"\n"<<ctime (&rawtime)<<"\n"<<std::endl;
if(status==0){
for(int i=0;i<5;i++){
std::cout<<"reconnecting .."<<std::endl;
status=	pub.reconnect();
if(status==1){
	ss<<i;

	pub.publish("reconnecting ....."+ss.str());
		ss.clear();
	std::cout<<"connected"<<std::endl;
	break;
}

}
}
std::cout<<"status ="<<status<<"\n";
}

pub.close();

}

int main(int argc,char *argv[]){
pretask(argc,argv);
run();
endtask();
}