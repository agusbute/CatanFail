#pragma once
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <cstdio>
#include <cstring>


#define PORT "13225"

class server
{
public:
	server();
	bool startListening();		//devuelve true si se conecto
	void send_message(FILE*, char*);
	void send_404();
	char * recieve_message();
	~server();

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
};

