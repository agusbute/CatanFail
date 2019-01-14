#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BoardComponent.h"
#include "Player.h"		//esto lo pongo solamente por los enum, hay que sacarlo

enum PieceType {ROAD, SETTLEMENT, CITY};	//tipos de piezas para construir

using namespace :: std;

typedef struct
{
	PieceType type;
	string player;
}piece_t;	//no se que onda esto, después vemos

class TerrainHexes : public BoardComponent
{
	public:
		TerrainHexes(char position_in_map = 0, Resources resource = NOTHING, int token = 0);	//inicializa todo en cero

	private:
		Resources resource;	
		int token;

};