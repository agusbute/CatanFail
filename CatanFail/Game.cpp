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
checkRoad(char x, char y)
{
	bool ret = false;
	
	void * search = board->searchPiece(x);
	char side, prev, next;
	if (search != NULL)				//si x es un hexagono, me fijo los adyacentes a el
	{
		TerrainHexes * temp1 = (TerrainHexes *)search;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (temp1->getAdjacentPiece(i) == y)
			{
				side = i;
				break;
			}
		}
		/*
		switch (side)
		{
		case LEFT:
		{
			next = temp1->getAdjacentPiece(TOP_LEFT);
			prev = temp1->getAdjacentPiece(BOTTOM_LEFT);
		} break;
		case TOP_LEFT:
		{
			next = temp1->getAdjacentPiece(TOP_RIGHT);
			prev = temp1->getAdjacentPiece(LEFT);
		} break;
		default:
		{
			next = temp1->getAdjacentPiece(side + 1);
			prev = temp1->getAdjacentPiece(side - 1);
		} break;
		}
		*/
	}


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
		*/
	}
	//if de confirmacion
	/*
	if (player->searchRoad(x, prev) || player->searchRoad(x, next) || player->searchRoad(prev2, y) || player->searchRoad(next2, y))
	{
		ret = true;
	}
	*/
	return ret;
}

bool Game::
checkLongestRoad(char x, char y) //agregar tener en cuenta la longest del constrincante
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
longestRecursive(char x, char y)
{
	unsigned int length = 0;

	void * search = board->searchPiece(x);
	char side, prev, next;
	if (search != NULL)				//si x es un hexagono, me fijo los adyacentes a el
	{
		TerrainHexes * temp1 = (TerrainHexes *)search;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (temp1->getAdjacentPiece(i) == y)
			{
				side = i;
				break;
			}
		}
		/*
		switch (side)
		{
			
			case LEFT:
			{
				next = temp1->getAdjacentPiece(TOP_LEFT);
				prev = temp1->getAdjacentPiece(BOTTOM_LEFT);
			} break;
			case TOP_LEFT:
			{
				next = temp1->getAdjacentPiece(TOP_RIGHT);
				prev = temp1->getAdjacentPiece(LEFT);
			} break;
			default:
			{
				next = temp1->getAdjacentPiece(side + 1);
				prev = temp1->getAdjacentPiece(side - 1);
			} break;
			
		}
		*/
	}


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
		*/
	}
	return length;
	//recursiva
}

Game::
~Game()
{
	delete board;
}