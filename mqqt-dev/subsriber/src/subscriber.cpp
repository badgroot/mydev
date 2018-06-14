#include "subscriber.h"
subscriber::subscriber(Json::Value &root){
_root=root;
}
subscriber::~subscriber(){
	mosquitto_destroy(mosq	);

mosquitto_lib_cleanup(	);

}
bool subscriber::isvalidating(){
bool status=true;
if(!( _root.isMember("server")&& _root["server"].isString())){
	syslog(LOG_INFO," server field missing conf.json ");
	status=false;
}
if( !( _root.isMember("user")&& _root["user"].isString()) ){
	syslog(LOG_INFO," user field missing conf.json ");
status=false;
}
if(!(_root.isMember("password")&& _root["password"].isString())){
	syslog(LOG_INFO," password field missing conf.json ");
status=false;
}
if(!(_root.isMember("topic")&& _root["topic"].isString())){
	syslog(LOG_INFO," topic field missing conf.json ");
status=false;
}
if(!(_root.isMember("port")&& _root["port"].isInt())){
	syslog(LOG_INFO," port field missing conf.json ");
status=false;
}
if(!(_root.isMember("keepalive")&& _root["keepalive"].isInt())){
	syslog(LOG_INFO," keepalive field missing conf.json ");
status=false;
}
if(!(_root.isMember("debugging")&& _root["debugging"].isBool())){
	syslog(LOG_INFO," debugging field missing conf.json ");
	status=false;
}

return status;
}





bool subscriber::isReady(){

return _isReady;
}
void subscriber::preTask(){
if(isvalidating())
{
syslog(LOG_INFO,"All json field found!!!");
}
else {
	_isReady=false;
	syslog(LOG_INFO,"something wrong in conf.jsonfile");
	INSERT_POS_LOG;
}
///mosquitto//
mosquitto_lib_init();
mosq=mosquitto_new(NULL,false,NULL);
if(!mosq){
syslog(LOG_INFO,"No memory allocated to mosq");
INSERT_POS_LOG;
}
_status=mosquitto_username_pw_set(mosq,_root["username"].asCString(),_root["password"].asCString());
checkstatus();
_status=mosquitto_connect(mosq,_root["server"].asCString(),_root["port"].asInt(),_root["keepalive"].asInt());
checkstatus();






}
	void subscriber::run(){



	}
	std::string &subscriber::getMsg(){

		return currentMsg;
	}
	void subscriber::on_connect_callback(struct mosquitto *most,void *obj,int result){
		syslog(LOG_INFO," connected ...");
}
 void subscriber::on_disconnect_callback(struct mosquitto *mosq,void *obj,int result){
syslog(LOG_INFO,"DISCONNECTED ...");
}

	void subscriber::close(){

	}
	void subscriber::reconnect(){
		_status=mosquitto_reconnect(		mosq	);
		checkstatus();

	}
	bool subscriber::checkstatus(){
	if(_status==MOSQ_ERR_SUCCESS){
		return true;
	}

	else if(_status==MOSQ_ERR_INVAL){
		syslog(LOG_INFO,"mosquito invalid params" );
			showerror();
		}
		else if (_status==MOSQ_ERR_NOMEM){
				syslog(LOG_INFO,"mosquito no memory available" );
			showerror();

		}
		else if(_status==MOSQ_ERR_ERRNO){
		syslog(LOG_INFO,"mosquito no memory available" );
			showerror();			
		}

		else if (_status==MOSQ_ERR_NO_CONN){
			syslog(LOG_INFO,"No connection" );
			showerror();	
		}
		else if (_status==MOSQ_ERR_PROTOCOL){
			syslog(LOG_INFO,"PROTOCOL ERROR" );
			showerror();	
		}
		else if(_status==MOSQ_ERR_PAYLOAD_SIZE){
				syslog(LOG_INFO,"MOSQ_ERR_PAYLOAD_SIZE" );
			showerror();	
		}
		else if (_status== MOSQ_ERR_CONN_LOST){
			syslog(LOG_INFO,"MOSQ_ERR_CONN_LOST" );
			showerror();
		}
		else{
			syslog(LOG_INFO,"unknow error");
						showerror();
								}


return false;
}