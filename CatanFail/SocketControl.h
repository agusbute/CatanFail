#pragma once

#include "boost/asio.hpp"
#include <string>
#include <iostream>

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
		bool RecieveNoots(string Message);

	protected:
		Mode modo;
		string TargetIP;
		NStatus NTurno;					//esto intica si recibo o envio data.
};