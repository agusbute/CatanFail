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
checkLongestRoad(char x, char y, char z) //chequear si la calle es mas larga
{
	vector <road_t> roads;
	bool ret;
	if (longestRecursive({ x, y, z }, roads) >= 5)
	{
		//if(player->getLongest() > oponent-getLongest())
		ret = true;
	}
	return ret;
}

unsigned int Game::
longestRecursive(road_t road, vector <road_t> &previous_roads, unsigned int length)
{
	unsigned int lengths[] = { 0, 0, 0, 0 };
	unsigned int longest;
	if (road.x != 0 && road.y != 0)		//solo se fija si las calles no son todo cero
	{	
		if (player->searchRoad(road))	//solo sigue si hay una calle construida ahi
		{
			lengths[0]++;
			lengths[1]++;
			lengths[2]++;
			lengths[3]++;
			if (!(inPreviousRoads(road, previous_roads)))		//solo sigue si no paso por esa calle todavia
			{
				previous_roads.push_back(road);
				road_t adjacent_roads[] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
				getAdjacentRoads({ road.x, road.y, road.z }, adjacent_roads);

				for (int i = 0; i < 4; i++)
				{
					lengths[i] += longestRecursive(adjacent_roads[i], previous_roads, lengths[i]);
				}
			}
		}
	}
	longest = max(max(lengths[0], lengths[1]), max(lengths[2], lengths[3]));
	return longest;
}

bool Game::
inPreviousRoads(road_t road, vector <road_t> &previous_roads) //devuelve true is road esta en previous_road
{
	bool ret = false;
	for (int i = 0; i < previous_roads.size(); i++)
	{
		if (road == previous_roads[i])
		{
			ret = true;
			break;
		}
	}
	return ret;
}

Game::
~Game()
{
	delete board;
}

void Game::
getAdjacentRoads(road_t main_road, road_t * adjacent_roads)
{
	//NOTA: si es un borde entre hexagono y mar, x siempre es mar (regla: x < y SIEMPRE)
	//primero pongo todos los elementos de adjacent_roads en {0,0,0}
	for (int i = 0; i < 4; i++)
	{
		*(adjacent_roads + i) = { 0, 0, 0 };
	}
	//ahora si, a buscar las calles adyacentes
	TerrainHexes * X, * Y;		//si x es un hexagono, este apunta a el
	SeaFrameTiles * X_sea;		//si y es un borde, este apunta a el
	BoardComponent * Xsearch = board->getPiece(main_road.x);
	BoardComponent * Ysearch = board->getPiece(main_road.y);
	char X_side, Y_side;							//X_side: de que lado para x esta y - Y_side:de que lado para y esta x
	char coin1, coin2;								//las dos piezas con las que coinciden x e y
	if (main_road.x >= 'A' && main_road.x <= 'S')				//si x es un hexagono, me fijo los adyacentes a el
	{															//hasta encontrar de que lado esta y
		X = (TerrainHexes *)Xsearch;
		Y = (TerrainHexes *)Ysearch;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (X->getAdjacentPiece(i) == main_road.y)
			{
				X_side = i;
				break;
			}
		}
		Y_side = ADJACENT_HEX - (X_side + (ADJACENT_HEX / 2));	//despues guardo de que lado esta x para y (en los hexagonos es el opuesto)
		
		//tengo que fijarme con que otros hexagonos/mar coinciden x e y
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (i != X_side)		//ya se que de x_side esta y
			{
				coin1 = X->getAdjacentPiece(i);
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (j != Y_side)	//ya se que de Y_side esta x
					{
						if (coin1 == Y->getAdjacentPiece(j))
						{
							break;		//una vez que encontre un par, salgo
						}
					}
				}
			}
		}
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			if (i != X_side)		//ya se que de x_side esta y
			{
				coin2 = X->getAdjacentPiece(i);
				if(coin2 != coin1)			//ya me fije coin1
				{
					for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
					{
						if (j != Y_side)	//ya se que de Y_side esta x
						{
							if (coin2 == Y->getAdjacentPiece(j))
							{
								break;		//una vez que encontre un par, salgo
							}
						}
					}
				}
			}
		}

		//ahora tengo que buscar las calles en esos lugares
		//si es un eje valido, agrego esa calle adyacente
		road_t road;
		road = { min(min(coin1,coin2), main_road.x), max(min(coin1,coin2), main_road.x), 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads) = road;
		}
		else
		{	//solo pasa si la coincidencia menor es mar
			road = { min(coin1,coin2), main_road.x, main_road.y };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR
		}
		road = { min(min(coin1,coin2), main_road.y), max(min(coin1,coin2), main_road.y), 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads + 1) = road;
		}
		else
		{	//solo pasa si la coincidencia menor es mar
			road = { min(coin1,coin2), main_road.y, main_road.x };
			if (board->inEdges(road))
			{
				*(adjacent_roads + 1) = road;
			}
			//else ERROR
		}
		road = { min(max(coin1,coin2), main_road.x), max(max(coin1,coin2), main_road.x), 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads + 2) = road;
		}
		road = { min(max(coin1,coin2), main_road.y), max(max(coin1,coin2), main_road.y), 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads + 3) = road;
		}
	}
	else if (main_road.x >= '0' && main_road.x <= '5')		//si x es mar, me fijo los adyacentes a el
	{															//hasta encontrar de que lado esta y
		X_sea = (SeaFrameTiles *)Xsearch;
		Y = (TerrainHexes *)Ysearch;
		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			if (X_sea->getAdjacentPiece(i) == main_road.y)
			{
				X_side = i;
				break;
			}
		}
		//despues guardo de que lado esta x para y 
		//(con las piezas de mar es esta cosa de aca(son todos los casos posibles, es lo mas general que se me ocurrio a las 3:00AM))
		switch (main_road.z)
		{
		case '0': case 'C': case 'B': Y_side = TOP_RIGHT; break;
		case '1': case 'G': case 'L': Y_side = RIGHT; break;
		case '2': case 'P': case 'S': Y_side = BOTTOM_RIGHT; break;
		case '3': case 'Q': case 'R': Y_side = BOTTOM_LEFT; break;
		case '4': case 'H': case 'M': Y_side = LEFT; break;
		case '5': case 'A': case 'D': Y_side = TOP_LEFT; break;

		case 0:
		{
			switch (main_road.x)
			{
			case '0': Y_side = TOP_LEFT; break;
			case '1': Y_side = TOP_RIGHT; break;
			case '2': Y_side = RIGHT; break;
			case '3': Y_side = BOTTOM_RIGHT; break;
			case '4': Y_side = BOTTOM_LEFT; break;
			case '5': Y_side = LEFT; break;
			}
		}
		}
		
		//busco las coincidencias entre x e y
		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			if (i != X_side)		//ya se que de x_side esta y
			{
				coin1 = X_sea->getAdjacentPiece(i);
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (j != Y_side)	//ya se que de Y_side esta x
					{
						if (coin1 == Y->getAdjacentPiece(j))
						{
							break;		//una vez que encontre un par, salgo
						}
					}
				}
			}
		}
		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			if (i != X_side)		//ya se que de x_side esta y
			{
				coin2 = X_sea->getAdjacentPiece(i);
				if (coin2 != coin1)			//ya me fije coin1
				{
					for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
					{
						if (j != Y_side)	//ya se que de Y_side esta x
						{
							if (coin2 == Y->getAdjacentPiece(j))
							{
								break;		//una vez que encontre un par, salgo
							}
						}
					}
				}
			}
		}
		
		if (coin1 > coin2)
		{
			swap(coin1, coin2);		//por simplicidad pongo coin1 como el menor de ellos
		}
		//las calles entre pieza de mar y hexagono tienen 2 o 3 calles adyacentes
		//algunas coordenadas no tienen z, otras tienen la coincidencia mas chica como z, otras la coincidencia mas grande
		//dependiendo cual es, las calles adyacentes siguen distintas reglas
		road_t road;
		if (main_road.z = 0)
		{
			//road 1
			road = { coin1, main_road.y, main_road.x };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 2
			road = { min(main_road.y, coin2), max(main_road.y, coin2), 0 };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 3
			road = { main_road.x, coin2, main_road.y };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR
		}
		else if (main_road.z == coin1)
		{
			//road 1
			road = { main_road.x, main_road.y, coin2};
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 2
			road = { main_road.x, coin1, 0 };	//puede que no exista esta calle, por ejemplo, si main_road es {'3','S','2'}
			if (board->inEdges(road))			//en ese caso, road seria {'3','2'}, que no existe
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 3
			road = { min(main_road.y, coin1), max(main_road.y, coin1), 0 };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR
		}
		else							//si z == coin2
		{
			//road 1
			road = { main_road.x, main_road.y, coin1 };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 2
			road = { main_road.y, coin2, 0 };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 3
			road = { main_road.x, coin2, main_road.y };
			if (board->inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			else
			{
				road = { main_road.x, coin2, 0 };
				if (board->inEdges(road))
				{
					*(adjacent_roads) = road;
				}
				//else ERROR
			}
		}
	}

}