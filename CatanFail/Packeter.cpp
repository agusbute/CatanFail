#include "Packets.h"
#include <string>

using namespace std;

string PacketMaker(PacketHeader Header, string data);
const char* getHeader(PacketHeader);

string PacketMaker(PacketHeader Header, string data)
{
    string Packet(getHeader(Header)); 
    if (Header == NAME)
    {
        Packet += data.length();
        Packet += data;
    }

    return Packet;

}

const char * getHeader(PacketHeader Header)
{
	
    switch (Header)
	{
    case OTHER: return "0x00";
        break;
    case ACK:   return "0x01";
        break;
    case NAME:  return "0x10";
        break;
    case NAME_IS:   return "0x11";
        break;
    case MAP_IS:    return "0x12";
        break;
    case CIRCULAR_TOKENS:   return "0x13";
        break;
    case PLAY_WITH_DEV: return "0x15";
        break;
    case DEV_CARDS: return "0x16";
        break;
    case YOU_START: return "0x17";
        break;
    case I_START:   return "0x18";
        break;
    case DICES_ARE: return "0x20";
        break; 
    case ROBBER_CARDS:  return "0x21";
        break;
    case CARD_IS:   return "0x22";
        break;
    case ROBBER_MOVE:   return "0x23";
        break;
    case SETTLEMENT:    return "0x24";
        break;
    case ROAD:  return "0x25";
        break;
    case CITY:  return "0x26";
        break;
    case BANK_TRADE:    return "0x27";
        break;
    case OFFER_TRADE:   return "0x28";
        break;
    case PASS:  return "0x29";
        break;
    case DEV_CARD:  return "0x30";
        break;
    case MONOPOLY: return "0x31";
        break;
    case YEARS_OF_PLENTY:   return "0x32";
        break;
    case ROAD_BUILDING: return "0x33";
        break;
    case KNIGHT:    return "0x34";
        break;
    case YES:   return "0x40";
        break;
    case NO:    return "0x41";
        break;
    case I_WON: return "0x50";
        break;
    case PLAY_AGAIN:    return "0x51";
        break;
    case GAME_OVER: return "0x52";
        break;
    case QUIT:  return "0xFF";
        break;
    default: return "Puto el que lee";
        break;
	}


}

