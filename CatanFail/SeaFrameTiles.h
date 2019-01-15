#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BoardComponent.h"

using namespace :: std;

typedef enum PORT {NONE, SHEEP, WOOD, STONE, BRICK, WHEAT, ANY};

typedef struct {
	PORT port1;
	PORT port2 = NONE;
}ports_t;

class SeaFrameTiles : public BoardComponent
{
	public:
		SeaFrameTiles(char position_in_map = 0); 
		bool setPorts(char ports); //char ports son que puertos tiene (identificado por 'N', 'T', 'O', 'L', 'P', 'M')

	private:
		ports_t myPorts;
		char adjacentPieces[5] = {0,0,0,0,0}; //Todos los Sea Frame Tiles tienen 5 piezas adyacentes(2 Sea frames, 3 hexes)
};