#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BoardComponent.h"

#define PREV 0
#define LOWER_LEFT 1
#define BOTTOM 2
#define LOWER_RIGHT 3
#define NEXT 4

using namespace std;

namespace ports {
	enum PORT { NONE, WOOL, LUMBER, ORE, BRICK, GRAIN, ANY };
}


typedef struct {
	ports::PORT port1;
	ports::PORT port2 = ports::NONE;
}ports_t;

class SeaFrameTiles : public BoardComponent
{
	public:
		
		SeaFrameTiles(char position_in_map = 0); 
		bool setPorts(char ports); //char ports son que puertos tiene (identificado por 'N', 'T', 'O', 'L', 'P', 'M')
		
		
		virtual bool setAdjacentPieces();
		virtual char getAdjacentPiece(char position);	//le mando la position con los defines y devuelve que pieza tiene al lado

	private:
		void defineAdjacentPieces(char left, char bottom_left, char bottom, char bottom_right, char right); //setter de las piezas adyacentes a la pieza
		ports_t myPorts;
		char adjacentPieces[ADJACENT_SEA]; //Todos los Sea Frame Tiles tienen 5 piezas adyacentes(2 Sea frames, 3 hexes)
};