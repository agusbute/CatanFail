#pragma once

#include "boost/asio.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Server.h"
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

#define BUFFER_SIZE	1024

enum Mode : int { CLIENT, SERVER };		//modos a funcionar
enum NStatus : int { RECEIVING, SENDING };

class NetworkSocket
{
	public:
		NetworkSocket();				
		bool Connect();
		virtual char* receive_message();
		virtual bool send_message(string message);
		bool startConnection(const char* host);
		virtual bool startListening();
		Mode getMode();
		

	protected:

		Mode modo;
		bool connected;
		string TargetIP;
							//esto intica si recibo o envio data.
		boost::asio::io_service* IO_handler;
		boost::asio::ip::tcp::socket* socket_forClient;
		boost::asio::ip::tcp::resolver* client_resolver;
		boost::asio::ip::tcp::resolver::iterator endpoint;
		boost::asio::ip::tcp::socket* socket_forServer;
		boost::asio::ip::tcp::acceptor* server_acceptor;
};