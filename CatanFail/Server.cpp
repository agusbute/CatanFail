#include "Server.h"

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