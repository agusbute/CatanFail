#pragma once
#include "Server.h"
#include "SocketControl.h"
#include "Client.h"

using namespace std;

NetworkSocket :: NetworkSocket()
{
	this->modo = CLIENT;			//siempre se iniciara como client
	server();
	client();

}


bool NetworkSocket :: Connect()
{
	
		
	if (modo == CLIENT)
	{
		
		int n = rand() % 3000 + 2000;
		chrono::steady_clock::time_point tend = std::chrono::steady_clock::now() + std::chrono::seconds(n);
		while (chrono::steady_clock::now() < tend)
		{

			Connect();

		}

		//intentar conexao con el sv con la ip que nos dieron
		bool ret = 
		if (ret)
		{
			this->NTurno = RECIEVING;	//poner que si hubo conex estoy en recibir info	
			return ret;
		}
		cout << "error en la conexion " << endl;
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

bool NetworkSocket :: RecieveNoots(string Message)
{
												//esto recibe mensajes del que manda
}

bool NetworkSocket::tryConnection(string IP) 
{


}