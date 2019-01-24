#pragma once

#include "SeaFrameTiles.h"

SeaFrameTiles ::
SeaFrameTiles(char position_in_map) : BoardComponent(position_in_map)
{
};

bool SeaFrameTiles::		//asigna los puertos respectivos
setPorts(char ports)		//devuelve true si no hubo errores
{
	bool ret = true; //asumo que el parametro ports es valido
	
	switch (ports) 
	{
		case 'N': case 'n':
		{
			myPorts.port1.port = ports::ANY;
			myPorts.port1.node1 = { this->getPositionInMap(), 
									min(this->getAdjacentPiece(LOWER_LEFT), this->getAdjacentPiece(BOTTOM)), 
									max(this->getAdjacentPiece(LOWER_LEFT), this->getAdjacentPiece(BOTTOM)) };
			myPorts.port1.node2 = { this->getPositionInMap(), this->getAdjacentPiece(BOTTOM), 0 };
		} break;
		
		case 'T': case 't':
		{
			myPorts.port1.port = ports::ANY;
			myPorts.port1.node1 = { min(this->getPositionInMap(), this->getAdjacentPiece(PREV)),
									max(this->getPositionInMap(), this->getAdjacentPiece(PREV)),
									this->getAdjacentPiece(LOWER_LEFT) };
			myPorts.port1.node2 = { this->getPositionInMap(), this->getAdjacentPiece(LOWER_LEFT) };
			
			myPorts.port2.port = ports::GRAIN;
			myPorts.port2.node1 = { this->getPositionInMap(), this->getAdjacentPiece(BOTTOM) };
			myPorts.port2.node2 = { this->getPositionInMap(), 
									min(this->getAdjacentPiece(BOTTOM), this->getAdjacentPiece(LOWER_RIGHT)), 
									max(this->getAdjacentPiece(BOTTOM), this->getAdjacentPiece(LOWER_RIGHT)) };
		} break;

		case 'O': case 'o':
		{
			myPorts.port1.port = ports::ANY;
			myPorts.port1.node1 = { min(this->getPositionInMap(), this->getAdjacentPiece(PREV)),
									max(this->getPositionInMap(), this->getAdjacentPiece(PREV)),
									this->getAdjacentPiece(LOWER_LEFT) };
			myPorts.port1.node2 = { this->getPositionInMap(), this->getAdjacentPiece(LOWER_LEFT) };
			
			myPorts.port2.port = ports::WOOL;
			myPorts.port2.node1 = { this->getPositionInMap(), this->getAdjacentPiece(BOTTOM) };
			myPorts.port2.node2 = { this->getPositionInMap(),
									min(this->getAdjacentPiece(BOTTOM), this->getAdjacentPiece(LOWER_RIGHT)),
									max(this->getAdjacentPiece(BOTTOM), this->getAdjacentPiece(LOWER_RIGHT)) };
		} break;
			
		case 'L': case 'l':
		{
			myPorts.port1.port = ports::ANY;
			myPorts.port1.node1 = { min(this->getPositionInMap(), this->getAdjacentPiece(PREV)),
									max(this->getPositionInMap(), this->getAdjacentPiece(PREV)),
									this->getAdjacentPiece(LOWER_LEFT) };
			myPorts.port1.node2 = { this->getPositionInMap(), this->getAdjacentPiece(LOWER_LEFT) };
			
			myPorts.port2.port = ports::BRICK;
			myPorts.port2.node1 = { this->getPositionInMap(), this->getAdjacentPiece(BOTTOM) };
			myPorts.port2.node2 = { this->getPositionInMap(),
									min(this->getAdjacentPiece(BOTTOM), this->getAdjacentPiece(LOWER_RIGHT)),
									max(this->getAdjacentPiece(BOTTOM), this->getAdjacentPiece(LOWER_RIGHT)) };
		} break;
		
		case 'P': case 'p':
		{
			myPorts.port1.port = ports::ORE;
			myPorts.port1.node1 = { this->getPositionInMap(),
						min(this->getAdjacentPiece(LOWER_LEFT), this->getAdjacentPiece(BOTTOM)),
						max(this->getAdjacentPiece(LOWER_LEFT), this->getAdjacentPiece(BOTTOM)) };
			myPorts.port1.node2 = { this->getPositionInMap(), this->getAdjacentPiece(BOTTOM), 0 };
		} break;
		
		case 'M': case 'm':
		{
			myPorts.port1.port = ports::LUMBER;
			myPorts.port1.node1 = { this->getPositionInMap(),
						min(this->getAdjacentPiece(LOWER_LEFT), this->getAdjacentPiece(BOTTOM)),
						max(this->getAdjacentPiece(LOWER_LEFT), this->getAdjacentPiece(BOTTOM)) };
			myPorts.port1.node2 = { this->getPositionInMap(), this->getAdjacentPiece(BOTTOM), 0 };
		} break;

		default: ret = false; break;  //se introdujo un caracter incorrecto
	}
	return ret;
}

ports_t SeaFrameTiles::
getPorts()
{
	return this->myPorts;
}

void SeaFrameTiles::
defineAdjacentPieces(char left, char bottom_left, char bottom, char bottom_right, char right)
{
	adjacentPieces[PREV] = left;
	adjacentPieces[LOWER_LEFT] = bottom_left;
	adjacentPieces[BOTTOM] = bottom;
	adjacentPieces[LOWER_RIGHT] = bottom_right;
	adjacentPieces[NEXT] = right;
}

bool SeaFrameTiles::
setAdjacentPieces()
{
	bool ret = true;
	switch (getPositionInMap())
	{
		case 0: defineAdjacentPieces('5', 'A', 'B', 'C', '1'); break;
		
		case 1: defineAdjacentPieces('0', 'C', 'G', 'L', '2'); break;
		
		case 2: defineAdjacentPieces('1', 'L', 'P', 'S', '3'); break;
		
		case 3: defineAdjacentPieces('2', 'S', 'R', 'Q', '4'); break;
		
		case 4: defineAdjacentPieces('3', 'Q', 'M', 'H', '5'); break;
		
		case 5: defineAdjacentPieces('4', 'H', 'D', 'A', '0'); break;
		
		default: ret = false;
	}
	return ret;
}

char SeaFrameTiles::
getAdjacentPiece(char position)	//le mando la position de los defines y devuelve que pieza tiene al lado
{
	char ret_position;

	switch (position)
	{
		case PREV:
			ret_position = adjacentPieces[PREV];
			break;

		case LOWER_LEFT:
			ret_position = adjacentPieces[LOWER_LEFT];
			break;

		case BOTTOM:
			ret_position = adjacentPieces[BOTTOM];
			break;

		case LOWER_RIGHT:
			ret_position = adjacentPieces[LOWER_RIGHT];
			break;

		case NEXT:
			ret_position = adjacentPieces[NEXT];
			break;

		default:
			ret_position = ERROR;
			break;
	}

	return ret_position;
}

