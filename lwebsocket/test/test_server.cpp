/*
g++ test_server.cpp -I./../websocketpp/  -lboost_system -lboost_chrono -lboost_random -o test_sever
*/

#include <iostream>
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"


typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


typedef server::message_ptr message_ptr;

void on_message(server *s,websocketpp::connection_hdl _hdl,message_ptr msg){
	std::cout<<"on message called with handle  :"<<_hdl.lock().get()
	<<"and message "
	<<msg->get_payload()
	<<std::endl;
	if(msg->get_payload() == "stop-listening"){
		s->stop();
		return ;
	}
try{
	s->send(_hdl,msg->get_payload(), msg->get_opcode());

}
catch(const websocketpp::lib::error_code& e){
	std::cout<<"echo failed because ('"<<e.message()<<"')"<<std::endl;
}
}

int main(int argc,char *argv[]){
	server echo_server;
	try{
		echo_server.set_access_channels(websocketpp::log::alevel::all);
		echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
	echo_server.init_asio();
	echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));
	echo_server.listen(9002);
	echo_server.start_accept();
	echo_server.run();




	}
	catch( websocketpp::exception const &e){
		std::cout<<"websocketpp execption :"<<e.what()
		<<std::endl;
	}
	catch (...){
		std::cout<<"unknown exeption"<<std::endl;
	}
}
