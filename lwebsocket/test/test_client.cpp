/*
g++ main.cpp -lboost_system -lboost_random -lboost_chrono -I./../../websocketpp/ -o client


*/
#include <iostream>
#include "../websocketpp/config/asio_no_tls_client.hpp"
#include "../websocketpp/client.hpp"
typedef websocketpp::client<websocketpp::config::asio_client> client;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

///handlers
void on_open(client *c,websocketpp::connection_hdl _hdl)
{
	std::string msg="Hello Server from client";
	c->send(_hdl, msg,websocketpp::frame::opcode::text);
	c->get_alog().write(websocketpp::log::alevel::app,"sent msg: "+msg);

}
void on_fail(client *c, websocketpp::connection_hdl _hdl){
	c->get_alog().write(websocketpp::log::alevel::app, "connection failed");
}

void on_message(client *c ,websocketpp::connection_hdl _hdl,message_ptr  msg){
	c->get_alog().write(websocketpp::log::alevel::app, "recieved msg ::" + msg->get_payload());
	c->close(_hdl, websocketpp::close::status::normal, "");


}
void on_close(client* c, websocketpp::connection_hdl hdl) {
    c->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}
int main(int argc,char *argv[])
{

client c;
std::string uri="ws://localhost:9002";

if(argc==2)
{
	uri=argv[1];
}
try{

c.clear_access_channels(websocketpp::log::alevel::frame_header);
c.clear_access_channels(websocketpp::log::alevel::frame_payload);
//c.set_error_channels(websocketpp::log::elevel::none);
c.init_asio();
c.set_open_handler(bind(&on_open,&c,::_1));
c.set_fail_handler(bind(&on_fail,&c,::_1));
c.set_message_handler(bind(&on_message,&c,::_1,::_2));
c.set_close_handler(bind(&on_close,&c,::_1));

websocketpp::lib::error_code ec;
client::connection_ptr con=c.get_connection(uri,ec);
c.connect(con);
c.run();


}
catch(std::exception &e){
std::cout<<"standard execption caught  "<<e.what()<<std::endl;
}
catch(websocketpp::lib::error_code &e){
std::cout<<"websocket error caught caught  "<<e.message()<<std::endl;
}
catch(...)
{
	std::cout<<"unknown execption"<<std::endl;
}


}