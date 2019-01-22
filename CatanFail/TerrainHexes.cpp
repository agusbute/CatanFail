#pragma once

#include "TerrainHexes.h"

TerrainHexes::
TerrainHexes(char position_in_map, Resources resource, int token) : BoardComponent(position_in_map)
{
	this->resource = resource;
	this->token = token;
	if (resource != DESERT)
	{
		this->robber_here = false;
	}
	else
	{
		this->robber_here = true;
	}
}

void TerrainHexes::
setRobber(bool value)
{
	this->robber_here = value;
}

bool TerrainHexes::
hasRobber()
{
	return this->robber_here;
}

void TerrainHexes::
setToken(char my_token)
{
	this->token = my_token;
}

char TerrainHexes::
getToken(void)
{
	return token;
}

void TerrainHexes::
setResource(Resources my_resource)
{
	this->resource = my_resource;
	if (resource != DESERT)
	{
		this->robber_here = false;
	}
	else
	{
		this->robber_here = true;
	}
}

Resources TerrainHexes::
getResource(void)
{
	return resource;
}

void TerrainHexes::
defineAdjacentPieces(char top_left, char top_right, char right, char bottom_right, char bottom_left, char left)
{
	adjacentPieces[TOP_LEFT] = top_left;
	adjacentPieces[TOP_RIGHT] = top_right;
	adjacentPieces[RIGHT] = right;
	adjacentPieces[BOTTOM_RIGHT] = bottom_right;
	adjacentPieces[BOTTOM_LEFT] = bottom_left;
	adjacentPieces[LEFT] = left;
}

bool TerrainHexes::
setAdjacentPieces()
{
	bool ret = true;
	switch (getPositionInMap())
	{
		case 'A': defineAdjacentPieces('0', '0', 'B', 'E', 'D', '5'); break;

		case 'B': defineAdjacentPieces('0', '0', 'C', 'F', 'E', 'A'); break;

		case 'C': defineAdjacentPieces('0', '1', '1', 'G', 'F', 'B'); break;

		case 'D': defineAdjacentPieces('5', 'A', 'E', 'I', 'H', '5'); break;

		case 'E': defineAdjacentPieces('A', 'B', 'F', 'J', 'I', 'D'); break;

		case 'F': defineAdjacentPieces('B', 'C', 'G', 'K', 'J', 'E'); break;

		case 'G': defineAdjacentPieces('C', '1', '1', 'L', 'K', 'F'); break;

		case 'H': defineAdjacentPieces('5', 'D', 'I', 'M', '4', '5'); break;

		case 'I': defineAdjacentPieces('D', 'E', 'J', 'N', 'M', 'H'); break;

		case 'J': defineAdjacentPieces('E', 'F', 'K', 'O', 'N', 'I'); break;

		case 'K': defineAdjacentPieces('F', 'G', 'L', 'P', 'O', 'J'); break;

		case 'L': defineAdjacentPieces('G', '1', '2', '2', 'P', 'K'); break;

		case 'M': defineAdjacentPieces('H', 'I', 'N', 'Q', '4', '4'); break;

		case 'N': defineAdjacentPieces('I', 'J', 'O', 'R', 'Q', 'M'); break;

		case 'O': defineAdjacentPieces('J', 'K', 'P', 'S', 'R', 'N'); break;

		case 'P': defineAdjacentPieces('K', 'L', '2', '2', 'S', 'O'); break;

		case 'Q': defineAdjacentPieces('M', 'N', 'R', '3', '4', '4'); break;

		case 'R': defineAdjacentPieces('N', 'O', 'S', '3', '3', 'Q'); break;

		case 'S': defineAdjacentPieces('O', 'P', '2', '3', '3', 'R'); break;

		default: ret = false;
	}
	return ret;
}

char TerrainHexes::
getAdjacentPiece(char position)	//le mando la position con los defines y devuelve que pieza tiene al lado
{
	char ret_position;

	switch (position)
	{
		case TOP_LEFT:
			ret_position = adjacentPieces[TOP_LEFT];
			break;

		case TOP_RIGHT:
			ret_position = adjacentPieces[TOP_RIGHT];
			break;

		case RIGHT:
			ret_position = adjacentPieces[RIGHT];
			break;

		case BOTTOM_RIGHT:
			ret_position = adjacentPieces[BOTTOM_RIGHT];
			break;

		case BOTTOM_LEFT:
			ret_position = adjacentPieces[BOTTOM_LEFT];
			break;

		case LEFT:
			ret_position = adjacentPieces[LEFT];

		default:
			ret_position = ERROR;
			break;
	}

	return ret_position;
}