#pragma once
#include "Server.h"
#include "SocketControl.h"
#include "Client.h"

using namespace std;

NetworkSocket :: NetworkSocket()
{

}


bool NetworkSocket :: Connect()
{
	
		
	if (modo == CLIENT)
	{
		
		int n = rand() % 3000 + 2000;
		bool ret = false;
		chrono::steady_clock::time_point tend = std::chrono::steady_clock::now() + std::chrono::milliseconds(n);
		while ((chrono::steady_clock::now() < tend) || ret != true )
		{
			ret = startConnection(TargetIP.c_str());
		}

		if (ret)
		{
			this->NTurno = RECEIVING;	//poner que si hubo conex estoy en recibir info	
			return ret;
		}
		else
		{
			cout << "No se pudo conectar al server" << endl;
			modo = SERVER;
			return false;

		}
	}
	else if (modo == SERVER)
	{
		
		while (connected == false)
		{
			connected = startListening();
		}
		
		NTurno = SENDING;	//si hay conex entonces mando info
		return true;
	}
	else
	{
		std::cout << "WTF ERROR EN EL MODO DE NETWORK SOCKET" << std::endl;
		return false;
	}
}

char* NetworkSocket::receive_message()
{
	boost::system::error_code error;
	char buf[1500];
	size_t len = 0;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);
		if (!error)
		{
			buf[len] = '\0';
		}
	} while (error.value() == WSAEWOULDBLOCK);
	if (!error)
	{
		return &buf[0];
	}
	else
	{
		cout << "Error while trying to connect to server " << error.message() << std::endl;
		return NULL;
	}

}



bool NetworkSocket::startConnection(const char* host)
{
	bool ret = true;
	boost::asio::ip::tcp::resolver::query query(host, PORT);
	this->endpoint = client_resolver->resolve(query);
	boost::system::error_code error;	
	boost::asio::connect(*socket_forClient, endpoint, error);

	if (error)
	{
		cout << "Error connecting to: " << host << " Error Message: " << error.message() << endl;
		if (error.value() == boost::asio::error::connection_refused)
		{
			cout << host << " is not listening." << endl;
			ret = false;
		}

	}
	socket_forClient->non_blocking(true);
	return ret;
}

bool NetworkSocket::startListening()
{
	bool ret = true;
	server_acceptor->non_blocking(true);
	boost::system::error_code error;
	do
	{
		server_acceptor->accept(*socket_forServer, error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
	{
		std::cout << "Error while trying to listen to " << PORT << "Port " << error.message() << std::endl;
		ret = false;
	}
	socket_forServer->non_blocking(true);
	return ret;
}

bool NetworkSocket::send_message(string str)
{
	bool ret = true;
	char* buf = new char[str.size() + 1];
	strcpy(buf, str.c_str());

	size_t len = 0;
	boost::system::error_code error;

	do
	{
		len += socket_forClient->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK) && len < strlen(buf));				//lo mando y me fijo que sea todo entero
	if (error)
	{
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		ret = false;
	}

	return ret;
}
