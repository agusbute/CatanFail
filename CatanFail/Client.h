#pragma once
#include "boost/asio.hpp"
#include <iostream>
using namespace std;


class client
{
public:
	client();
	bool tryConnection(string ip);
	char * receive_message();
	bool send_message(char*, char *);
	~client();

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};