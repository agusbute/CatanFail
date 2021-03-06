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

enum Resources { LUMBER, BRICK, ORE, GRAIN, WOOL, DESERT, NOTHING }; //Resource Cards: Lumber, Brick, Ore, Grain, Wool; Desert and Nothing se usan para los hex�gonos

typedef struct coord_t
{
	char x;
	char y;
	char z = 0;

	bool operator== (coord_t &coord)
	{
		return (x == coord.x && y == coord.y && z == coord.z);
	}

}coord_t;

class BoardComponent	//clase padre de las piezas de mar y los hexagonos
{
	public:
		BoardComponent(char position_in_map);	//settea la posici�n que tiene en el mapa
		void setPositionInMap(char position_in_map);	//setter para lo mismo que el constructor
		char getPositionInMap(void);	//devuelve la posici�n de la pieza en el mapa
		virtual bool setAdjacentPieces(void) = 0;
		virtual char getAdjacentPiece(char position) = 0;

	private:
		char position_in_map;	//posici�n de la pieza en el mapa


};
