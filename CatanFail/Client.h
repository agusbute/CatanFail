#pragma once
#include "boost/asio.hpp"
#include <iostream>
#define PORT "13225"
using namespace std;


class client
{
public:
	client();
	bool tryConnection(const char * ip);
	char * receive_message();
	bool send_message(char*);
	~client();

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::deadline_timer deadline;
};