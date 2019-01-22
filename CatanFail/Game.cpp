#include "Game.h"

Game::
Game()
{
	board = new Board;
	board->initToStartGame();
}

Game::
~Game()
{
	delete board;
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
checkSettlement(settlement_t settlement)
{
	bool ret = false;
	if (board->inNodes(settlement)) //si se introdujo un nodo que no existe, devuelve false
	{
		//si el contrincante o el jugador ya construyeron ahi, no se puede hacer nada, devuelve false
		if (!(oponent->searchBuilding(settlement)) && !(player->searchBuilding(settlement)))
		{
			//busco nodos adyacentes
			coord_t adjacent_nodes[3];
			getAdjacentNodes(settlement, adjacent_nodes);

			//si el contrincante o el jugador ya construyeron en los adyacentes, no se puede hacer nada, devuelve false
			if (!(oponent->searchBuilding(adjacent_nodes[0])) && !(player->searchBuilding(adjacent_nodes[0])) &&
				!(oponent->searchBuilding(adjacent_nodes[1])) && !(player->searchBuilding(adjacent_nodes[1])) &&
				!(oponent->searchBuilding(adjacent_nodes[2])) && !(player->searchBuilding(adjacent_nodes[2])))
			{
				//busco calles adyacentes --- EN EL PRIMER TURNO ESTO NO SE TIENE QUE TENER EN CUENTA
				if (!(turnCounter < 3))
				{
					road_t adjacent_roads[3];
					getNodeAdjacentRoads(settlement, adjacent_roads);

					//si hay una calle del jugador en las aristas adyacentes(lo que teniendo en cuenta
					//que no puede haber un settlement en los nodos adyacentes significa que hay al menos dos caminos)
					//entonces se puede construir
					if (player->searchRoad(adjacent_roads[0]) ||
						player->searchRoad(adjacent_roads[1]) ||
						player->searchRoad(adjacent_roads[2]))
					{
						ret = true;
					}
				}
				else
				{
					ret = true;
				}

			}
		}
	}
	return ret;
}

bool Game::
checkSettlement(char x, char y, char z)
{
	return checkSettlement({ x, y, z });
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
	if (board->inEdges({ x, y, z })) //si se introdujo una calle que no existe, chau, false
	{
		if (!(oponent->searchRoad(x, y, z)) && !(player->searchRoad(x, y, z))) //si el contrincante o el jugador ya construyeron ahi, no se puede hacer nada, devuelve false
		{
			//primer turno
			if (turnCounter < 3)
			{
				coord_t adjacent_nodes[2];
				getRoadAdjacentNodes({ x, y, z }, adjacent_nodes);
				if (player->searchBuilding(adjacent_nodes[0]) || player->searchBuilding(adjacent_nodes[1]))
				{
					ret = true;
				}
			}
			//resto(a partir de los primeros turnos, todos los settlements tienen calles saliendo de ellos, asi que con fijarse las calles adyacentes es suficiente)
			else
			{
				//buscar calles adyacentes
				road_t adjacent_roads[] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
				getAdjacentRoads({ x, y, z }, adjacent_roads);
				for (int i = 0; i < 4; i++)
				{
					ret = (ret || player->searchRoad(adjacent_roads[i]));
				}
			}
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
		if (player->getLongest() > oponent->getLongest())
		{
			ret = true;
		}
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
inPreviousRoads(road_t road, vector <road_t> &previous_roads) //devuelve true is road esta en previous_roads
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
		if (main_road.z == 0)
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

void Game::
getNodeAdjacentRoads(settlement_t settlement, road_t * adjacent_roads)
{
	//NOTA: x < y < z SIEMPRE => x: arriba, y: izquierda, z: derecha || x: izquierda, y: derecha, z: abajo
	
	//primero pongo todos los elementos de adjacent_roads en {0,0,0}
	for (int i = 0; i < 3; i++)
	{
		*(adjacent_roads + i) = { 0, 0, 0 };
	}
	
	//si x, y, z son hexagonos, es facil
	if ((settlement.x >= 'A' && settlement.x <= 'S') && 
		(settlement.y >= 'A' && settlement.y <= 'S') && 
		(settlement.z >= 'A' && settlement.z <= 'S'))
	{
		road_t road;
		//road 1
		road = { settlement.x, settlement.y, 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads) = road;
		}
		//road 2
		road = { settlement.x, settlement.z, 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads + 1) = road;
		}
		//road 3
		road = { settlement.y, settlement.z, 0 };
		if (board->inEdges(road))
		{
			*(adjacent_roads + 2) = road;
		}
	}
	//el problema es con el mar
	else if (settlement.z == 0)			//no tiene coordenada z (esta entre un mar y un hexagono)
	{
		BoardComponent *X, *Y; //punteros a las piezas del tablero (antes no las neceseitaba porque era mas simple)
		X = board->getPiece(settlement.x);
		Y = board->getPiece(settlement.y);
		
		//solo hay dos calles adyacenetes
		road_t road1, road2;

		//x e y tienen dos piezas con las que coinciden
		char c1, c2;

		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			c1 = X->getAdjacentPiece(i);
			for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
			{
				if (c1 == Y->getAdjacentPiece(j))
				{
					break;		//una vez que encontre un par, salgo
				}
			}
		}
		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			c2 = X->getAdjacentPiece(i);
			if (c2 != c1)			//ya se que una coincidencia va a ser c1, esa no la quiero
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c2 == Y->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}
		
		//por comodidad, hago que c1 sea la coincidencia menor
		if (c1 > c2)
		{
			swap(c1, c2);
		}

		road1 = { settlement.x, settlement.y, c1 };
		road2 = { settlement.x, settlement.y, c2 };
		//deberian estar ambas calles
		if (board->inEdges(road1))
		{
			adjacent_roads[0] = road1;
		}
		//else ERROR
		if (board->inEdges(road2))
		{
			adjacent_roads[1] = road2;
		}
		//else ERROR
	}
	//Despues hay solo 6 nodos que tienen dos piezas que son mar y un hexagono
	//son poquitos, puedo hacerlo con switch case simple no? No?
	else
	{
		switch (settlement.x)
		{
		case '0':
		{
			if (settlement.y == '1')		//estamos en el (0,1,C)
			{
				adjacent_roads[0] = { '0', 'C', 0 };
				adjacent_roads[1] = { '1', 'C', '0' };
			}
			else							//estamos en el (0,5,A)
			{
				adjacent_roads[0] = { '0', 'A', '5' };
				adjacent_roads[1] = { '5', 'A', 0 };
			}
		}
		case '1':							//estamos en el (1,2,L)
		{
			adjacent_roads[0] = { '2', '1', 'L' };
			adjacent_roads[1] = { '1', 'L', 0 };
		}
		case '2':							//estamos en el (2,3,S)
		{
			adjacent_roads[0] = { '3', 'S', '2' };
			adjacent_roads[1] = { '2', 'S', 0 };
		}
		case '3':							//estamos en el (3,4,Q)
		{
			adjacent_roads[0] = { '4', 'Q', '3' };
			adjacent_roads[1] = { '3', 'Q', 0 };
		}
		case '4':							//estamos en el (4,5,H)
		{
			adjacent_roads[0] = { '5', 'H', '4' };
			adjacent_roads[1] = { '4', 'H', 0 };
		}
		}
	}
}

void Game::
getAdjacentNodes(settlement_t settlement, coord_t * adjacent_nodes)
{
	//NOTA: x < y < z SIEMPRE => x: arriba, y: izquierda, z: derecha || x: izquierda, y: derecha, z: abajo
	
	BoardComponent *X, *Y, *Z;		//punteros a las piezas del tablero
	X = board->getPiece(settlement.x);
	Y = board->getPiece(settlement.y);
	Z = board->getPiece(settlement.z);
	
	coord_t node1, node2, node3;		//nodos a guardar

	//primero pongo todos los elementos de adjacent_nodes en {0,0,0}
	for (int i = 0; i < 3; i++)
	{
		*(adjacent_nodes + i) = { 0, 0, 0 };
	}

	//si x, y, z son todos hexagonos, es mas simple
	if ((settlement.x >= 'A' && settlement.x <= 'S') &&
		(settlement.y >= 'A' && settlement.y <= 'S') &&
		(settlement.z >= 'A' && settlement.z <= 'S'))
	{
		
		//me fijo las coincidencias entre los hexagonos que ya no sepa
		char c1, c2, c3;
		
		//entre x e y
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			c1 = X->getAdjacentPiece(i);
			if (c1 != settlement.z)			//ya se que una coincidencia va a ser z, esa no la quiero
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c1 == Y->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}
		
		//entre x y z
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			c2 = X->getAdjacentPiece(i);
			if (c2 != settlement.y)			//ya se que una coincidencia va a ser y, esa no la quiero
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c2 == Z->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}

		//entre y y z
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			c3 = Y->getAdjacentPiece(i);
			if (c3 != settlement.x)			//ya se que una coincidencia va a ser x, esa no la quiero
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c3 == Z->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}

		//entonces, los nodos van a ser los siguientes;
		node1 = { min(c1, settlement.x), max(c1, settlement.x), settlement.y };
		node2 = { min(c2, settlement.x), max(c2, settlement.x), settlement.z };
		node3 = { min(c3, settlement.y), min(max(c3, settlement.y), settlement.z), max(max(c3, settlement.y), settlement.z) };
		
		//los guardo (deberian existir todos)
		if (board->inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (board->inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR
		if (board->inNodes(node3))
		{
			adjacent_nodes[2] = node3;
		}
		//else ERROR
	}
	//de vuelta, el problema es con el mar (maldito poseidon!)
	//si solo tiene un lado que es mar y los otros dos son hexagonos, tampoco es muy dificil (por suerte)
	else if ((settlement.x >= '0' && settlement.x <= '5') && 
			 (settlement.y >= 'A' && settlement.y <= 'S') && (settlement.z != 0))
	{
		node1 = { settlement.x, settlement.y, 0 };
		if (board->inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//puede que este no exista(ejemplo: nodo principal = (4,h,m) => node1 quedaria (4,h) que no existe)
		//por suerte, la solucion es facil
		else
		{
			char c; //coincidencia entre x y y que no sea z
			for (char i = PREV; i < ADJACENT_SEA; i++)
			{
				c = X->getAdjacentPiece(i);
				if (c != settlement.z)			//ya se que una coincidencia va a ser z, esa no la quiero
				{
					for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
					{
						if (c == Y->getAdjacentPiece(j))
						{
							break;		//una vez que encontre un par, salgo
						}
					}
				}
			}
			node1 = { min(settlement.x, c), max(settlement.x, c), settlement.y };
			if (board->inNodes(node1))
			{
				adjacent_nodes[0] = node1;
			}
			//else ERROR
		}
		
		node2 = { settlement.x, settlement.z, 0 };
		if (board->inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//puede que este no exista(ejemplo: nodo principal = (0,b,c) => node2 quedaria (0,c) que no existe)
		//por suerte, la solucion es facil
		else
		{			
			char c; //coincidencia entre x y z que no sea y
			for (char i = PREV; i < ADJACENT_SEA; i++)
			{
				c = X->getAdjacentPiece(i);
				if (c != settlement.y)			//ya se que una coincidencia va a ser y, esa no la quiero
				{
					for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
					{
						if (c == Z->getAdjacentPiece(j))
						{
							break;		//una vez que encontre un par, salgo
						}
					}
				}
			}
			node2 = { min(settlement.x, c), max(settlement.x, c), settlement.z };
			if (board->inNodes(node1))
			{
				adjacent_nodes[1] = node2;
			}
			//else ERROR
		}

		//para node3 necesitamos la coincidencia entre y y z que no sea x
		char c;
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			c = Y->getAdjacentPiece(i);
			if (c != settlement.x)			//ya se que una coincidencia va a ser x, esa no la quiero
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c == Z->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}
		node3 = { min(settlement.y, c), min(max(settlement.y, c),settlement.z), max(max(settlement.y, c),settlement.z) };
		if (board->inNodes(node3))
		{
			adjacent_nodes[2] = node3;
		}
		//else ERROR
	}
	//despues puede que solo un lado sea mar y el otro hexagono - aca solo tiene dos nodos adyacentes
	else if ((settlement.x >= '0' && settlement.x <= '5') && 
			 (settlement.y >= 'A' && settlement.y <= 'S') && (settlement.z == 0))
	{
		//x e y tienen dos piezas con las que coinciden
		char c1, c2;
		
		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			c1 = X->getAdjacentPiece(i);
			for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
			{
				if (c1 == Y->getAdjacentPiece(j))
				{
					break;		//una vez que encontre un par, salgo
				}
			}
		}
		for (char i = PREV; i < ADJACENT_SEA; i++)
		{
			c2 = X->getAdjacentPiece(i);
			if (c2 != c1)			//ya se que una coincidencia va a ser c1, esa no la quiero
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c2 == Y->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}
		
		//por comodidad, hago que c1 sea la coincidencia menor
		if (c1 > c2)
		{
			swap(c1, c2);
		}

		node1 = { min(settlement.x, c1), min(max(settlement.x, c1), settlement.y), max(max(settlement.x, c1), settlement.y) };
		if (board->inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		node2 = { min(settlement.x, c2), min(max(settlement.x, c2), settlement.y), max(max(settlement.x, c2), settlement.y) };
		if (board->inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR
	}
	//Despues hay solo 6 nodos que tienen dos piezas que son mar y un hexagono
	//son poquitos, puedo hacerlo con switch case simple no? No?
	else
	{
		switch (settlement.x)
		{
			case '0':
			{
				if (settlement.y == '1')		//estamos en el (0,1,C)
				{
					adjacent_nodes[0] = { '0', 'B', 'C' };
					adjacent_nodes[1] = { '1', 'C', 0 };
				}
				else							//estamos en el (0,5,A)
				{
					adjacent_nodes[0] = { '0', 'A', 0 };
					adjacent_nodes[1] = { '5', 'A', 'D' };
				}
			}
			case '1':							//estamos en el (1,2,L)
			{
				adjacent_nodes[0] = { '1', 'G', 'L' };
				adjacent_nodes[1] = { '2', 'L', 0 };
			}
			case '2':							//estamos en el (2,3,S)
			{
				adjacent_nodes[0] = { '2', 'P', 'S' };
				adjacent_nodes[1] = { '3', 'S', 0 };
			}
			case '3':							//estamos en el (3,4,Q)
			{
				adjacent_nodes[0] = { '3', 'Q', 'R' };
				adjacent_nodes[1] = { '4', 'Q', 0 };
			}
			case '4':							//estamos en el (4,5,H)
			{
				adjacent_nodes[0] = { '4', 'H', 'M' };
				adjacent_nodes[1] = { '5', 'H', 0 };
			}
		}
	}
}

void Game::
getRoadAdjacentNodes(road_t road, coord_t * adjacent_nodes)
{
	BoardComponent *X, *Y, *Z;		//punteros a las piezas del tablero
	X = board->getPiece(road.x);
	Y = board->getPiece(road.y);
	Z = board->getPiece(road.z);

	coord_t node1, node2;		//nodos a guardar

	//primero pongo todos los elementos de adjacent_nodes en {0,0,0}
	for (int i = 0; i < 2; i++)
	{
		*(adjacent_nodes + i) = { 0, 0, 0 };
	}

	//si la calles esta solo entre dos hexagonos es mas simple
	if ((road.x >= 'A' && road.x <= 'S') &&
		(road.y >= 'A' && road.y <= 'S') &&
		(road.z == 0))
	{
		//me fijo las coincidencias entre x e y
		char c1, c2;

		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			c1 = X->getAdjacentPiece(i);
			for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
			{
				if (c1 == Y->getAdjacentPiece(j))
				{
					break;		//una vez que encontre un par, salgo
				}
			}
		}
		for (char i = TOP_LEFT; i < ADJACENT_HEX; i++)
		{
			c2 = X->getAdjacentPiece(i);
			if (c2 != c1)			//ya se que una coincidencia va a ser c1
			{
				for (int j = TOP_LEFT; j < ADJACENT_HEX; j++)
				{
					if (c1 == Y->getAdjacentPiece(j))
					{
						break;		//una vez que encontre un par, salgo
					}
				}
			}
		}
		
		//por comodidad, hago que c1 sea la coincidencia menor
		if (c1 > c2)
		{
			swap(c1, c2);
		}

		//los nodos entonces son los siguientes
		node1 = { min(c1, road.x), min(max(c1, road.x), road.y), max(max(c1, road.x), road.y) };
		node2 = { min(c2, road.x), min(max(c2, road.x), road.y), max(max(c2, road.x), road.y) };
		if (board->inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (board->inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR		
	}
	//si esta entre mar y hexagono y z no es 0, tambien siguien una regla bastanate facil
	else if ((road.x >= '0' && road.x <= '5') &&
			 (road.y >= 'A' && road.y <= 'S') && 
			 (road.z != 0))
	{
		//uno de los nodos va a ser solo (x,y)
		node1 = { road.x, road.y, 0 };

		//el otro va a ser {x, y, z} ordenados de menor a mayor
		node2 = { min(min(road.x, road.y), road.z), min(max(road.x, road.y), road.z), max(max(road.x, road.y), road.z) };

		if (board->inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (board->inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR
	}
	//solo quedan 6 calles que son entre mar y hexagono con dos coordenadas (ya lo saben, sale switch case)
	else
	{
		switch (road.x)
		{
			case '0':
			{
				node1 = { '0', 'B', 'C' };
				node2 = { '0', '1', 'C' };
			}break;
			case '1':
			{
				node1 = { '1', 'G', 'L' };
				node2 = { '1', '2', 'L' };
			}break;
			case '2':
			{
				node1 = { '2', 'P', 'S' };
				node2 = { '2', '3', 'S' };
			}break;
			case '3':
			{
				node1 = { '3', 'Q', 'R' };
				node2 = { '3', '4', 'Q' };
			}break;
			case '4':
			{
				node1 = { '4', '5', 'H' };
				node2 = { '4', 'H', 'M' };
			}break;
			case '5':
			{
				node1 = { '5', 'A', 'D' };
				node2 = { '0', '5', 'A' };
			}break;
		}
		
		if (board->inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (board->inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR
	}

}

bool Game::
moveRobber(TerrainHexes &place_robber_here)
{
	bool keep_searching = true;

	bool can_i = false;
	if ((player->getDiceNumber() == 7) && (!place_robber_here.hasRobber()))	//me aseguro que haya salido el 7 y que el hex que elegí no tenga ya el robber
	{
		for (int i = 0; i < TERRAIN_HEXES, keep_searching == true; i++)
		{
			if (board->all_the_hexes[i].hasRobber())	//me fijo donde está el robber
			{
				board->all_the_hexes[i].setRobber(false);	//lo saco
				keep_searching = false;
			}
		}
		place_robber_here.setRobber(true);	//y lo ubico en la posición que quiero
	}
	return keep_searching;
}

bool Game::
moveRobber(char move_robber_here)
{
	TerrainHexes * hex = (TerrainHexes *)board->getPiece(move_robber_here); //ya se que va a ser un hexagono(el robber no puede ir en pieza de mar

	return moveRobber(*hex);
}