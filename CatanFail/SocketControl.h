#pragma once

#include "boost/asio.hpp"
#include <string>
#include <deque>
#include <iostream>

using namespace std;

#define BUFFER_SIZE	1024

enum Mode : int { CLIENT, SERVER }; //modos a funcionar

class NetworkSocket {
	public:
		NetworkSocket();				//constructor inicializa en modo client
		bool Connect();
		bool SendString(string Message);

	protected:
		Mode modo;
		string TargetIP;
};