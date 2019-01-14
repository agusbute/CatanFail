#include "Board.h"

Board::
Board()
{
	all_the_hexes = new TerrainHexes [TERRAIN_HEXES];	//inicializa todo en 0 (constructor)
	all_the_sea_frames = new SeaFrameTiles[SEA_FRAME_TILES];

}

void Board::
initToStartGame()
{
	for (int i = 0; i < TERRAIN_HEXES; i++)	//va setteando cada uno de los hexagonos
	{
		all_the_hexes[i].setPositionInMap();	//con la posición en el tablero
		//all_the_hexes[i].setToken();	//el token que tiene
		//all_the_hexes[i].setResource();	//y lo que produce
	}

	for (int j = 0; j < SEA_FRAME_TILES; j++)	//lo mismo con las piezas de mar
	{
		all_the_sea_frames[j].setPositionInMap();	//con la posición en el tablero
		//all_the_sea_frames[i].setHarbors();	//y el/los puerto/s que tiene
	}
}

Board::
~Board()
{
	delete[] all_the_hexes;
	delete[] all_the_sea_frames;
}