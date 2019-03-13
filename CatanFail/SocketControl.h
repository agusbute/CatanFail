#pragma once

#include "boost/asio.hpp"
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

#define BUFFER_SIZE	1024

enum Mode : int { CLIENT, SERVER };		//modos a funcionar
enum NStatus : int { RECIEVING, SENDING };

class NetworkSocket : server
{
	public:
		NetworkSocket();				//constructor inicializa en modo client
		bool Connect();
		bool SendString(string Message);
		char * RecieveNoots(string Message);
		bool startConnection(const char* host);
		

	protected:
		Mode modo;
		bool connected;
		string TargetIP;
		NStatus NTurno;					//esto intica si recibo o envio data.
		boost::asio::io_service* IO_handler;
		boost::asio::ip::tcp::socket* socket_forClient;
		boost::asio::ip::tcp::resolver* client_resolver;
		boost::asio::ip::tcp::resolver::iterator endpoint;
		boost::asio::io_service*  IO_handler;
		boost::asio::ip::tcp::socket* socket_forServer;
		boost::asio::ip::tcp::acceptor* server_acceptor;
};