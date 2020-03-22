#include "NFSM.h"
#include "Input.h"


void networkFSM()
{
	ConnectionStatus status = DISCONNECTED;
	client NewClient;
	bool error = false;

	while (status != READY)
	{
		switch (status)
		{
		case DISCONNECTED: {
			
			if (!NewClient.Connect())
			{
				if (!NewClient.Connect())
				{
					cout << "no se pudo conectar" << endl;
					return;
				}

				status = INITIATION;
			}
			else
			{
				status = INITIATION;
			}
		}
						 break;
		case INITIATION:
						{
							if (NewClient.getMode() == SERVER)
							{
								NewClient.send_message(PacketMaker(NAME));
								NewClient.receive_message();					// aca recibo el nombre del otro participante, guardar en algun lado.
								NewClient.send_message(PacketMaker(ACK));
								if (NewClient.receive_message() != getHeader(ACK))
								{
									cout << "ERROR ME MANDARON CUALQUIER COSA" << endl;
								}												//revisar que sea un ACK
								NewClient.send_message(PacketMaker(NAME_IS, NOMBRE DEL QUE ESTA USANDO EL SERVER));
								if (NewClient.receive_message() != getHeader(ACK))
								{
									cout << "ERROR ME MANDARON CUALQUIER COSA" << endl;
								}
								NewClient.estado = SENDING;
							}
							else if (NewClient.getMode() == CLIENT)							{
								
								if (NewClient.receive_message() != getHeader(NAME))
								{
									cout << "ERROR ME MANDARON CUALQUIER COSA" << endl;
								}
								NewClient.send_message(PacketMaker(NAME_IS, ACA VA EL NOMBRE QUE NO ME LO DIERON TODAVIA));	//PONER EL NOMBRE
								if (NewClient.receive_message() != getHeader(ACK))
								{
									cout << "ERROR ME MANDARON CUALQUIER COSA" << endl;
								}
								NewClient.estado = RECEIVING;

							}
							status = READY;

						}
		}

		if (error == true)
		{
			return;
		}

	}

	

	
	

}




bool verifyPacket(PacketHeader header, PacketHeader data)
{
	bool ret = false;
	if (header == data)
	{
		ret = true;

	}
	return ret;
}

bool verifyPacket(PacketHeader, unsigned char* data)
{
	return false;
}
