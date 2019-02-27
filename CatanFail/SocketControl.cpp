#pragma once
#include "Server.h"
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
		//intentar conexao con el sv con la ip que nos dieron
		bool ret = startConnection();
		if (ret)
		{
			this->NTurno = RECIEVING;	//poner que si hubo conex estoy en recibir info	
			return ret;
		}
		std:cout << "error en la conexion " << std:endl;
		return false;
	}
	else if (modo == SERVER)
	{
		//hacer cosas de server

		
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
												//la idea es que esto le mande mensaje al otro
}

bool Network :: RecieveNoots(string Message)
{
												//esto recibe mensajes del que manda
}