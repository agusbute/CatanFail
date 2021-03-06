#pragma once
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "SocketControl.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define PORT "13225"

class server : public NetworkSocket
{
public:
	bool startListening();
	void send_message(char* message);
	char* receive_message();
	server();
	~server();
	NStatus estado;
};

