#pragma once

#include "SeaFrameTiles.h"

SeaFrameTiles ::
SeaFrameTiles(char position_in_map) : BoardComponent(position_in_map)
{
	//no se como poner los puertosssssssssss
};

bool SeaFrameTiles::		//asigna los puertos respectivos
setPorts(char ports)		//devuelve true si no hubo errores
{
	bool ret = true; //asumo que el parametro ports es valido
	
	switch (ports) 
	{
		case 'N': case 'n':
		{
			myPorts.port1 = ports::ANY;
		} break;
		
		case 'T': case 't':
		{
			myPorts.port1 = ports::ANY;
			myPorts.port2 = ports::GRAIN;
		} break;

		case 'O': case 'o':
		{
			myPorts.port1 = ports::ANY;
			myPorts.port2 = ports::WOOL;
		} break;
			
		case 'L': case 'l':
		{
			myPorts.port1 = ports::ANY;
			myPorts.port2 = ports::BRICK;
		} break;
		
		case 'P': case 'p':
		{
			myPorts.port1 = ports::ORE;
		} break;
		
		case 'M': case 'm':
		{
			myPorts.port1 = ports::LUMBER;
		} break;

		default: ret = false; break;  //se introdujo un caracter incorrecto
	}
	return ret;
}

void SeaFrameTiles::
setAdjacentPieces(char left, char bottom_left, char bottom, char bottom_right, char right)
{
	adjacentPieces[0] = left;
	adjacentPieces[1] = bottom_left;
	adjacentPieces[2] = bottom;
	adjacentPieces[3] = bottom_right;
	adjacentPieces[4] = right;
}

bool SeaFrameTiles::
setAdjacentPieces()
{
	bool ret = true;
	switch (getPositionInMap())
	{
		case 0: setAdjacentPieces('5', 'A', 'B', 'C', '1'); break;
		
		case 1: setAdjacentPieces('0', 'C', 'G', 'L', '2'); break;
		
		case 2: setAdjacentPieces('1', 'L', 'P', 'S', '3'); break;
		
		case 3: setAdjacentPieces('2', 'S', 'R', 'Q', '4'); break;
		
		case 4: setAdjacentPieces('3', 'Q', 'M', 'H', '5'); break;
		
		case 5: setAdjacentPieces('4', 'H', 'D', 'A', '0'); break;
		
		default: ret = false;
	}
	return ret;
}

