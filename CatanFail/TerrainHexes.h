#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BoardComponent.h"

#define TOTAL_RESOURCES 5

#define TERRAIN_HEXES 19	//cantidad total de hexagonos

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define RIGHT 2
#define BOTTOM_RIGHT 3
#define BOTTOM_LEFT 4
#define LEFT 5


enum PieceType {ROAD, SETTLEMENT, CITY};	//tipos de piezas para construir

using namespace std;

/*
typedef struct
{
	PieceType type;
	string player;
}piece_t;	//no se que onda esto, después vemos
*/

class TerrainHexes : public BoardComponent
{
	public:
		TerrainHexes(char position_in_map = 0, Resources resource = NOTHING, int token = 0);	//inicializa todo en cero
		void setToken(char my_token);
		int getToken(void);
		void setResource(Resources my_resource);
		Resources getResource(void);
		bool hasRobber();			//devuelve el estado del Robber bool
		void setRobber(bool value);
		virtual bool setAdjacentPieces(void);
		virtual char getAdjacentPiece(char position);	//le mando la position con los defines y devuelve que pieza tiene al lado

	private:
		void defineAdjacentPieces(char top_left, char top_right, char right, char bottom_right, char bottom_left, char left);

		Resources resource;	
		int token;
		char adjacentPieces[ADJACENT_HEX];
		bool robber_here;	//si tiene el robber esto es true
};