#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__
#include <iostream>
#include <stdio.h>
#include <string>
#include <jsoncpp/json/json.h>
#include <syslog.h>
#include <mosquitto.h>
#define INSERT_POS_LOG syslog(LOG_INFO," filename  %s, line  %d ",__FILE__,__LINE__);
class subscriber{
public:
	subscriber(Json::Value &root);
	~subscriber();
	bool isvalidating();
	bool isReady();
	void preTask();
	void run();
	std::string & getMsg();
static	void on_connect_callback(struct mosquitto *most,void *obj,int result);
static void on_disconnect_callback(struct mosquitto *mosq,void *obj,int result);
static void on_message_callback(struct mosquitto *mosq,void *obj,const struct mosquitto_message *message){
	printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
	syslog(LOG_INFO,"got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);

}
	void close();
	void reconnect();
	void disconnect(){
		
		mosquitto_disconnect(	mosq	);
		checkstatus();

	}
	bool checkstatus();
	bool showerror(){
syslog(LOG_INFO,"MQQT Error %s",mosquitto_strerror(_status));
return true;
}
private:
	Json::Value  _root;
	int _status;
	bool _isReady;
	std::string currentMsg;
	std::string previousMsg;
	struct mosquitto *mosq;

};



#endif