#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ADJACENT_SEA 5
#define ADJACENT_HEX 6
#define ERROR 99

using namespace std;

typedef struct
{
	char x;
	char y;
	char z = 0;
}coord_t;

class BoardComponent	//clase padre de las piezas de mar y los hexagonos
{
	public:
		BoardComponent(char position_in_map);	//settea la posición que tiene en el mapa
		void setPositionInMap(char position_in_map);	//setter para lo mismo que el constructor
		char getPositionInMap(void);	//devuelve la posición de la pieza en el mapa
		virtual bool setAdjacentPieces(void) = 0;
		virtual char getAdjacentPiece(char position) = 0;

	private:
		char position_in_map;	//posición de la pieza en el mapa


};
