#pragma once
#include "Client.h"
#include "Server.h"
#include "SocketControl.h"
#include "Packets.h"

enum ConnectionStatus : char { INITIATION, READY , DISCONNECTED};


bool verifyPacket(PacketHeader,unsigned char* data);

