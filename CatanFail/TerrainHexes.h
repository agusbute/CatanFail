#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BoardComponent.h"
#include "Player.h"		//esto lo pongo solamente por los enum, hay que sacarlo

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define RIGHT 2
#define BOTTOM_RIGHT 3
#define BOTTOM_LEFT 4
#define LEFT 5


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
		void setToken(char my_token);
		char getToken(void);
		void setResource(Resources my_resource);
		Resources getResource(void);
		virtual bool setAdjacentPieces(void);
		void defineAdjacentPieces(char top_left, char top_right, char right, char bottom_right, char bottom_left, char left);
		virtual char getAdjacentPiece(char position);	//le mando la position con los defines y devuelve que pieza tiene al lado

	private:
		Resources resource;	
		int token;
		char adjacentPieces[ADJACENT_HEX];

};