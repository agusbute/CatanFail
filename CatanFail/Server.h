#pragma once
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define PORT "13225"

class server
{
public:
	server();
	bool startListening ();		//devuelve true si se conecto
	void send_message (char* message);
	char * receive_message ();	//devuelve el message
	~server ();

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	boost::asio::deadline_timer deadline;
};

