#include "Game.h"

Game::
Game()
{
	board = new Board;
	board->initToStartGame();
}

void Game::
createDevelopmentCards(void)
{
	char knight_counter = 0, road_b_counter = 0, victory_counter = 0, monopoly_counter = 0, year_of_p_counter = 0;

	srand(time(NULL));
	char type = rand() % 5 + 1; // 1 = knight, 2 = monopoly, 3 = victory, 4 = road building, 5 = year of plenty

	char i = 0; //contador
	while (i < TOTAL_D_CARDS)
	{
		if (type == 1 && knight_counter < TOTAL_KNIGHT_CARDS)
		{
			development_cards.push(DevelopmentCard(KNIGHT));
			knight_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 2 && monopoly_counter < TOTAL_MONO_CARDS)
		{
			development_cards.push(DevelopmentCard(MONO));
			monopoly_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 3 && victory_counter < TOTAL_V_POINT_CARDS)
		{
			development_cards.push(DevelopmentCard(V_POINT));
			victory_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 4 && road_b_counter < TOTAL_R_BUILDING_CARDS)
		{
			development_cards.push(DevelopmentCard(R_BUILDING));
			road_b_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 5 && year_of_p_counter < TOTAL_YEAR_OF_P_CARDS)
		{
			development_cards.push(DevelopmentCard(YEAR_OF_P));
			year_of_p_counter++;
			type = rand() % 5 + 1;
		}
	}
}

bool Game::
checkRoad(road_t road)
{
	return checkRoad(road.x, road.y, road.z);
}

bool Game::
checkRoad(char x, char y, char z)
{
	bool ret = false;
	if (!(oponent->searchRoad(x, y, z))) //si el contrincante ya construyo ahi, no se puede hacer nada, devuelve false
	{
		//buscar calles adyacentes
		road_t adjacent_roads[] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
		getAdjacentRoads({ x, y, z }, adjacent_roads);
		for (int i = 0; i < 4; i++)
		{
			ret = (ret || player->searchRoad(adjacent_roads[i]));
		}
	}

	return ret;
}

bool Game::
checkLongestRoad(char x, char y, char z) //agregar tener en cuenta la longest del constrincante
{
	bool ret;
	if (longestRecursive(x, y) >= 5)
	{
		//if(player->myLongest > player2.longest)
		ret = true;
	}
	return ret;
}

unsigned int Game::
longestRecursive(char x, char y, char z)
{
	unsigned int length = 0;

	//algoritmo busqueda de calles adyacentes
	return length;
	//recursiva
}

Game::
~Game()
{
	delete board;
}

void Game::
getAdjacentRoads(road_t main_road, road_t adjacent_roads[4])
{
	TerrainHexes * X;		//si x es un hexagono, este apunta a el
	SeaFrameTiles * X_sea;		//si y es un borde, este apunta a el
	BoardComponent * Xsearch = board->getPiece(main_road.x);
	char X_pos_in_map = Xsearch->getPositionInMap();
	char side;
	if (X_pos_in_map >= 'A' && X_pos_in_map <= 'S')				//si x es un hexagono, me fijo los adyacentes a el
	{															//hasta encontrar de que lado esta y
		X = (TerrainHexes *)Xsearch;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (X->getAdjacentPiece(i) == main_road.y)
			{
				side = i;
				break;
			}
		}
	}
	else if (X_pos_in_map >= '0' && X_pos_in_map <= '5')		//si x es mar, me fijo los adyacentes a el
	{															//hasta encontrar de que lado esta y
		X_sea = (SeaFrameTiles *)Xsearch;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (X_sea->getAdjacentPiece(i) == main_road.y)
			{
				side = i;
				break;
			}
		}
	}

	/*
	void * search2 = board->searchPiece(y);
	char side2, prev2, next2;
	if (search2 != NULL)
	{
		TerrainHexes * temp2 = (TerrainHexes *)search2;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (temp2->getAdjacentPiece(i) == x)
			{
				side2 = i;
				break;
			}
		}
		/*
		switch (side2)
		{
		case LEFT:
		{
			next2 = temp2->getAdjacentPiece(TOP_LEFT);
			prev2 = temp2->getAdjacentPiece(BOTTOM_LEFT);
		} break;
		case TOP_LEFT:
		{
			next2 = temp2->getAdjacentPiece(TOP_RIGHT);
			prev2 = temp2->getAdjacentPiece(LEFT);
		} break;
		default:
		{
			next2 = temp2->getAdjacentPiece(side + 1);
			prev2 = temp2->getAdjacentPiece(side - 1);
		} break;
		}
	}
	*/
}