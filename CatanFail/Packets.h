#pragma once

string PacketMaker(PacketHeader Header, string data = "");

const char* getHeader(PacketHeader Header);

enum PacketHeader : unsigned char {
	OTHER = 0x00,
	ACK = 0x01,
	NAME = 0x10,
	NAME_IS,
	MAP_IS,
	CIRCULAR_TOKENS,
	PLAY_WITH_DEV = 0x15,
	DEV_CARDS,
	YOU_START,
	I_START,
	DICES_ARE = 0x20,
	ROBBER_CARDS,
	CARD_IS,
	ROBBER_MOVE,
	SETTLEMENT,
	ROAD,
	CITY,
	BANK_TRADE,
	OFFER_TRADE,
	PASS,
	DEV_CARD,
	MONOPOLY,
	YEARS_OF_PLENTY,
	ROAD_BUILDING,
	KNIGHT,
	YES = 0x40,
	NO = 0x41,
	I_WON = 0x50,
	PLAY_AGAIN,
	GAME_OVER,
	HEADER_ERROR = 0xFE,
	QUIT
};