#pragma once
#include "Server.h"
#include "SocketControl.h"
#include "Client.h"

using namespace std;

NetworkSocket :: NetworkSocket()
{
	this->modo = CLIENT;			//siempre se iniciara como client
	server();
	connected = false;

}


bool NetworkSocket :: Connect()
{
	
		
	if (modo == CLIENT)
	{
		
		int n = rand() % 3000 + 2000;
		bool ret;
		chrono::steady_clock::time_point tend = std::chrono::steady_clock::now() + std::chrono::milliseconds(n);
		while ((chrono::steady_clock::now() < tend) || ret != true )
		{
			ret = startConnection(TargetIP.c_str());
		}

		if (ret)
		{
			this->NTurno = RECIEVING;	//poner que si hubo conex estoy en recibir info	
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
		
		connected = true;
		this->NTurno = SENDING;	//si hay conex entonces mando info
		return true;
	}
	else
	{
		std::cout << "WTF ERROR EN EL MODO DE NETWORK SOCKET" << std::endl;
		getchar();
		return false;
	}
}

bool NetworkSocket::SendString(string Message)
{
	if (modo == CLIENT)
	{
		char * buf = new char[Message.size() + 1];
		strcpy(buf, Message.c_str());
		bool ret = true;
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
	else if (modo == SERVER)
	{

		char * buf = new char[Message.size() + 1];
		strcpy(buf, Message.c_str());

		size_t len = 0;
		boost::system::error_code error;

		do
		{
			len += socket_forServer->write_some(boost::asio::buffer(buf, strlen(buf)), error);
		} while ((error.value() == WSAEWOULDBLOCK) && len < strlen(buf));
		if (error)
		{
			std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		}
	}
}


char * NetworkSocket :: RecieveNoots(string Message)
{
	if (modo == CLIENT)
	{
		boost::system::error_code error;
		char buf[1024];
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
	else if (modo == SERVER)
	{
		boost::system::error_code error;
		char buf[1024];
		size_t len = 0;
		do
		{
			len = socket_forServer->read_some(boost::asio::buffer(buf), error);
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
			cout << "Error while trying to connect to client. " << error.message() << std::endl;
			return NULL;
		}
	}
}

bool NetworkSocket::startConnection(const char* host)
{
	bool ret = true;
	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, PORT));
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
