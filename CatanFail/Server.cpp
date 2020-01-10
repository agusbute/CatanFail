#include "Server.h"
/*
bool server::startListening()
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
		std::cout << "Error while trying to listen to " << PORT << " Port " << error.message() << std::endl;
		ret = false;
	}
	socket_forServer->non_blocking(true);
	return ret;
}

void server:: send_message(char* message)
	{

		string str = message;

		char* buf = new char[str.size() + 1];
		strcpy(buf, str.c_str());

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

char* server::receive_message()
	{
		boost::system::error_code error;
		char buf[1500];
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
			cout << "Error while trying to connect to server " << error.message() << std::endl;
			return NULL;
		}
	}
	*/
	server::server()
	{
		IO_handler = new boost::asio::io_service();
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), PORT);
		socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
		server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler, ep);
		modo = SERVER;
	}

	server::~server()
	{
		server_acceptor->close();
		socket_forServer->close();
		delete server_acceptor;
		delete socket_forServer;
		delete IO_handler;
	}
