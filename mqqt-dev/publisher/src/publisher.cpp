#include "publisher.h"

publisher::publisher(){

}
publisher::publisher(std::string &username,std::string &pass,std::string server,int port,std::string pubname){
_username=username;
_password=pass;
_server=server;
_port=port;
pub_id=pubname;
}
void publisher::pretask(){
	_status=0;
	mosquitto_lib_init();///mqqt init
	mosq=NULL;
	mosq=mosquitto_new(pub_id.c_str(), true, NULL);
if(!mosq){
	INSERT_POS_LOG;
	showerror();
}
mosquitto_connect_callback_set(mosq,&publisher::connect_callback);
//mosquitto_message_callback_set(mosq, &publisher::message_callback);
///mosquitto_publish_callback_set()
mosquitto_disconnect_callback_set(mosq,&publisher::disconnect_callback);
_status=mosquitto_username_pw_set(mosq, _username.c_str(), _password.c_str());
if(!checkstatus()){
	INSERT_POS_LOG;
}
_status=mosquitto_connect(mosq,_server.c_str(),_port, 10);	
if(!checkstatus()){
	INSERT_POS_LOG;
}


}
bool publisher::publish(const char *msg){
_status=mosquitto_publish(mosq,NULL, pub_id.c_str(), strlen(msg),msg, 0,false);
std::cout<<"_status"<<_status<<std::endl;
if(!checkstatus()){
	syslog(LOG_INFO," %s not published message ",msg);
	INSERT_POS_LOG;
	return false;
}
syslog(LOG_INFO,"message [%s] published at topic [%s]  ",msg,pub_id.c_str());
return true;
}
bool publisher::isReady(){

	return true;
}
bool publisher::reconnect(){
_status=0;
_status=mosquitto_reconnect(mosq);
if(!checkstatus()){
INSERT_POS_LOG;
return false;
}
	return true;
}







bool publisher::checkstatus(){
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
bool publisher::close(){
//postTask();
	return false;
}

void publisher::postTask(){

}
publisher::~publisher(){
	postTask();
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

}
void publisher::on_publish(struct mosquitto *mosq, void *userdata, int mid)
{
 //   mosquitto_disconnect(mosq);

std::cout<<"published   ...."<<std::endl;
}
void publisher::connect_callback(struct mosquitto *most,void *obj,int result){
std::cout<<"connected callback function callled"<<std::endl;
}
void publisher::disconnect_callback(struct mosquitto* most,void *obj,int rc){
	std::cout<<"disconnnect callback function called\n";
}
void publisher::message_callback(struct mosquitto *most,void *obj,int result){

}