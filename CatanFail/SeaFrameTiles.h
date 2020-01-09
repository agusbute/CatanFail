#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "BoardComponent.h"

#define PREV 0
#define LOWER_LEFT 1
#define BOTTOM 2
#define LOWER_RIGHT 3
#define NEXT 4

#define SEA_FRAME_TILES 6	//cantidad total de piezas de mar

using namespace std;

namespace ports {
	typedef enum PORT { NONE, WOOL, LUMBER, ORE, BRICK, GRAIN, ANY };
	bool operator== (PORT &port, Resources &resource)
	{
		return ((port == LUMBER && resource == LUMBER) || 
				(port == WOOL && resource == WOOL) || 
				(port == ORE && resource == ORE) || 
				(port == BRICK && resource == BRICK) || 
				(port == GRAIN && resource == GRAIN));
	}
}

typedef struct {
	coord_t node1;
	coord_t node2;
	ports::PORT port;
}portData_t;


typedef struct {
	portData_t port1;
	portData_t port2 = { { 0, 0, 0 }, { 0, 0, 0 }, ports::NONE };
}ports_t;

class SeaFrameTiles : public BoardComponent
{
	public:
		
		SeaFrameTiles(char position_in_map = 0); 
		bool setPorts(char ports); //char ports son que puertos tiene (identificado por 'N', 'T', 'O', 'L', 'P', 'M')
		
		ports_t getPorts(); //getter de los puertos
		
		virtual bool setAdjacentPieces();
		virtual char getAdjacentPiece(char position);	//le mando la position con los defines y devuelve que pieza tiene al lado

	private:
		void defineAdjacentPieces(char left, char bottom_left, char bottom, char bottom_right, char right); //setter de las piezas adyacentes a la pieza
		ports_t myPorts;
		char adjacentPieces[ADJACENT_SEA]; //Todos los Sea Frame Tiles tienen 5 piezas adyacentes(2 Sea frames, 3 hexes)
};