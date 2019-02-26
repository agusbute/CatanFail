#pragma once

#include "SocketControl.h"

NetworkSocket :: NetworkSocket()
{
	this->modo = CLIENT;			//siempre se iniciara como client
}


bool NetworkSocket :: Connect()
{
	
		
	if (modo == CLIENT)
	{
		//hacer cosas de cliente
	}
	else if (modo == SERVER)
	{
		//hacer cosas de server
	}
	else
	{
		std::cout << "WTF ERROR EN EL MODO DE NETWORK SOCKET";
		return 1;
	}
}

bool NetworkSocket::SendString(string Message)
{
												//la idea es que esto le mande mensaje al otro
}