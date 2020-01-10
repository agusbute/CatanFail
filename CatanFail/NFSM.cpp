#include "NFSM.h"


void networkFSM()
{
	ConnectionStatus status = DISCONNECTED;
	client NewClient;
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
							//send name
						}
		}
	}

	

	
	if (NewClient.getMode() == SERVER)
	{
		NewClient.send_message(PacketMaker(NAME));
	}
	else if (NewClient.getMode() == CLIENT)
	{

	}


}