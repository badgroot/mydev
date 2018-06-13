#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <mosquitto.h>
#define INSERT_POS_LOG syslog(LOG_INFO," filename  %s, line  %d ",__FILE__,__LINE__);
class publisher{
	public:
	publisher();
	publisher(std::string &username,std::string &pass,std::string server,int port,std::string pubname="");
	~publisher();
void	pretask();
void run();
void postTask();
bool	isReady();
bool	reconnect();
bool publish(const char *msg);
bool publish(std::string msg){
	publish(msg.c_str());
}
static void on_publish(struct mosquitto *most,void *obj,int result);
static void connect_callback(struct mosquitto *most,void *obj,int result);
static void message_callback(struct mosquitto *most,void *obj,int result);
static void disconnect_callback(struct mosquitto *most,void *obj,int result);
bool checkstatus();
bool showerror(){
syslog(LOG_INFO,"MQQT Error %s",mosquitto_strerror(_status));
return true;
}
bool close();
	private:
		struct mosquitto *mosq;
		std::string _username;
		std::string _password;
		std::string _server;
		int _port;
		std::string pub_id;
	static	bool mqqt_enable;
	int _status;


};


#endif