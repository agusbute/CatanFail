#include "Board.h"

Board::
Board()
{
	all_the_hexes = new TerrainHexes[TERRAIN_HEXES];	//inicializa todo en 0 (constructor)
	all_the_sea_frames = new SeaFrameTiles[SEA_FRAME_TILES];
}

void Board::
initToStartGame()
{
	char* random_tokens = new char[TERRAIN_HEXES];	//arreglo temporal en el que guardo los tokens
	fill_n(random_tokens, TERRAIN_HEXES, 0);	//completa todo en 0
	createRandomTokens(random_tokens);	//cargo los tokens al azahar 

	char letter = 'A';	//para las posiciones de los hex
	Resources resources[] = { LUMBER, LUMBER, LUMBER, LUMBER, 
							BRICK, BRICK, BRICK, 
							ORE, ORE, ORE, 
							GRAIN, GRAIN, GRAIN, GRAIN, 
							WOOL, WOOL, WOOL, WOOL, 
							DESERT };
	int randvalue;		//valor aleatorio para repartir las cosas
	for (int i = 0; i < TERRAIN_HEXES; i++, letter++)	//va setteando cada uno de los hexagonos
	{
		all_the_hexes[i].setPositionInMap(letter);	//con la posición en el tablero
		all_the_hexes[i].setAdjacentPieces();		//y las piezas adyacentes 
		all_the_hexes[i].setToken(random_tokens[i]);	//el token que tiene
		do
		{
			randvalue = rand() % TERRAIN_HEXES;		//un valor aleatorio
			if (resources[randvalue] != 0)
			{
				if (all_the_hexes[i].getToken() == 7)	//si tiene token 7, es el desierto
				{
					randvalue = 18;
				}
				all_the_hexes[i].setResource(resources[randvalue]);	//agrega aleatoriamente los recursos, sin que haya dos iguales	
			}
		} while (resources[randvalue] == NOTHING);
		resources[randvalue] = NOTHING;	
	}
	delete[] random_tokens;	//porque ya los tiene cada hex

	char number = '0';	//para las posiciones de los sea frames
	char types[] = { 'N', 'T', 'O', 'L', 'P', 'M' };
	for (int j = 0; j < SEA_FRAME_TILES; j++, number++)	//lo mismo con las piezas de mar
	{
		all_the_sea_frames[j].setPositionInMap(number);	//con la posición en el tablero
		all_the_sea_frames[j].setAdjacentPieces();		//y las piezas adyacentes								
		do
		{
			randvalue = rand() % SEA_FRAME_TILES;		//un valor aleatorio de 0-5
			if (types[randvalue] != 0)
			{
				all_the_sea_frames[j].setPorts(types[randvalue]);	//agrega aleatoriamente los puertos, sin que haya dos iguales
			}	
		} while (types[randvalue] == 0);
		types[randvalue] = 0;
	}

}

void Board::
searchResource(char dice_number, char * hex)
{
	//hay maximo dos hexagonos con el mismo token
	//para empezar, los pongo en null
	hex[0] = NULL;
	hex[1] = NULL;

	int i;
	for (i = 0; i < TERRAIN_HEXES; i++)
	{
		if (all_the_hexes[i].getToken() == dice_number)
		{
			hex[0] = all_the_hexes[i].getPositionInMap();
			break;
		}
	}
	for (int j = i; i < TERRAIN_HEXES; j++)
	{
		if (all_the_hexes[j].getPositionInMap() != hex[0])	//ya se que uno es el queq seleccionamos antes
		{
			if (all_the_hexes[j].getToken() == dice_number)
			{
				hex[1] = all_the_hexes[j].getPositionInMap();
				break;
			}
		}
	}
}

void Board ::
createRandomTokens(char* random_tokens)
{
	srand(time(NULL));
	char token = rand() % 12 + 1;	//el siete lo voy a usar para definir el que va a ser el desierto
	int i = 0; //contador

	while (i < TERRAIN_HEXES)	//quizás se puede hacer mejor con un for pero no me salió
	{
		if (!tokenExists(random_tokens, token))	//si ese token todavía puede usarse
		{
			random_tokens[i] = token;	//lo guardo
			i++;
		}
	}
}

bool Board ::
tokenExists(char* random_tokens, char token)	//devuelve true si ya no lo puedo usar
{
	bool token_is_used = true;
	char repeated_token = 0;	//las veces que está el token usado

	for (int i = 0; i < TERRAIN_HEXES; i++)
	{
		if (random_tokens[i] == token)	//me fijo si ya lo usé
		{
			repeated_token += 1;	//y cuento las veces que está
		}
	}
	
	if (((token == 7 || token == 2 || token == 12) && repeated_token < 1) || ((token != 7 && token != 2 && token != 12) && repeated_token < 2))	//el dos, doce y siete solo pueden estar una vez (el siete va a ser el del desierto) y el resto dos veces
	{
		token_is_used = false;
	}

	return token_is_used;
}

TerrainHexes * Board::
searchHexPiece(char info) //devuelve NULL si lo introducido no es un hexagono
{
	TerrainHexes * ret = NULL;
	if (info >= 'A' && info <= 'S')
	{
		ret = &all_the_hexes[info];
	}
	return ret;
}

SeaFrameTiles * Board::
searchSeaPiece(char info)
{
	SeaFrameTiles * ret = NULL;
	if (info >= '0' && info <= '5')
	{
		ret = &all_the_sea_frames[info];
	}
	return ret;
}

BoardComponent * Board::
getPiece(char info)
{
	BoardComponent * ret;
	ret = searchHexPiece(info);
	if (ret == NULL)
	{
		ret = searchSeaPiece(info);
	}
	return ret;
}

bool Board::
inEdges(coord_t coord)
{
	bool ret = false;
	for (int i = 0; i < Edges.size(); i++)
	{
		ret = (ret || (coord.x == Edges[i].x && coord.y == Edges[i].y && coord.z == Edges[i].z));
	}
	return ret;
}

bool Board::
inNodes(coord_t coord)
{
	bool ret = false;
	for (int i = 0; i < Nodes.size(); i++)
	{
		ret = (ret || (coord.x == Nodes[i].x && coord.y == Nodes[i].y && coord.z == Nodes[i].z));
	}
	return ret;
}

void Board::
getAdjacentRoads(road_t main_road, road_t * adjacent_roads)
{
	//NOTA: si es un borde entre hexagono y mar, x siempre es mar (regla: x < y SIEMPRE)
	//primero pongo todos los elementos de adjacent_roads en {0,0,0}
	for (int i = 0; i < 4; i++)
	{
		*(adjacent_roads + i) = { 0, 0, 0 };
	}
	//ahora si, a buscar las calles adyacentes
	TerrainHexes * X, *Y;		//si x es un hexagono, este apunta a el
	SeaFrameTiles * X_sea;		//si y es un borde, este apunta a el
	BoardComponent * Xsearch = getPiece(main_road.x);
	BoardComponent * Ysearch = getPiece(main_road.y);
	char X_side = 0, Y_side = 0;							//X_side: de que lado para x esta y - Y_side:de que lado para y esta x
	char coin1 = 0, coin2 = 0;								//las dos piezas con las que coinciden x e y
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

		//ahora tengo que buscar las calles en esos lugares
		//si es un eje valido, agrego esa calle adyacente
		road_t road;
		road = { min(min(coin1,coin2), main_road.x), max(min(coin1,coin2), main_road.x), 0 };
		if (inEdges(road))
		{
			*(adjacent_roads) = road;
		}
		else
		{	//solo pasa si la coincidencia menor es mar
			road = { min(coin1,coin2), main_road.x, main_road.y };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR
		}
		road = { min(min(coin1,coin2), main_road.y), max(min(coin1,coin2), main_road.y), 0 };
		if (inEdges(road))
		{
			*(adjacent_roads + 1) = road;
		}
		else
		{	//solo pasa si la coincidencia menor es mar
			road = { min(coin1,coin2), main_road.y, main_road.x };
			if (inEdges(road))
			{
				*(adjacent_roads + 1) = road;
			}
			//else ERROR
		}
		road = { min(max(coin1,coin2), main_road.x), max(max(coin1,coin2), main_road.x), 0 };
		if (inEdges(road))
		{
			*(adjacent_roads + 2) = road;
		}
		road = { min(max(coin1,coin2), main_road.y), max(max(coin1,coin2), main_road.y), 0 };
		if (inEdges(road))
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
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 2
			road = { min(main_road.y, coin2), max(main_road.y, coin2), 0 };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 3
			road = { main_road.x, coin2, main_road.y };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR
		}
		else if (main_road.z == coin1)
		{
			//road 1
			road = { main_road.x, main_road.y, coin2 };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 2
			road = { main_road.x, coin1, 0 };	//puede que no exista esta calle, por ejemplo, si main_road es {'3','S','2'}
			if (inEdges(road))			//en ese caso, road seria {'3','2'}, que no existe
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 3
			road = { min(main_road.y, coin1), max(main_road.y, coin1), 0 };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR
		}
		else							//si z == coin2
		{
			//road 1
			road = { main_road.x, main_road.y, coin1 };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 2
			road = { main_road.y, coin2, 0 };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			//else ERROR

			//road 3
			road = { main_road.x, coin2, main_road.y };
			if (inEdges(road))
			{
				*(adjacent_roads) = road;
			}
			else
			{
				road = { main_road.x, coin2, 0 };
				if (inEdges(road))
				{
					*(adjacent_roads) = road;
				}
				//else ERROR
			}
		}
	}

}

void Board::
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
		if (inEdges(road))
		{
			*(adjacent_roads) = road;
		}
		//road 2
		road = { settlement.x, settlement.z, 0 };
		if (inEdges(road))
		{
			*(adjacent_roads + 1) = road;
		}
		//road 3
		road = { settlement.y, settlement.z, 0 };
		if (inEdges(road))
		{
			*(adjacent_roads + 2) = road;
		}
	}
	//el problema es con el mar
	else if (settlement.z == 0)			//no tiene coordenada z (esta entre un mar y un hexagono)
	{
		BoardComponent *X, *Y; //punteros a las piezas del tablero (antes no las neceseitaba porque era mas simple)
		X = getPiece(settlement.x);
		Y = getPiece(settlement.y);

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
		if (inEdges(road1))
		{
			adjacent_roads[0] = road1;
		}
		//else ERROR
		if (inEdges(road2))
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

void Board::
getAdjacentNodes(settlement_t settlement, coord_t * adjacent_nodes)
{
	//NOTA: x < y < z SIEMPRE => x: arriba, y: izquierda, z: derecha || x: izquierda, y: derecha, z: abajo

	BoardComponent *X, *Y, *Z;		//punteros a las piezas del tablero
	X = getPiece(settlement.x);
	Y = getPiece(settlement.y);
	Z = getPiece(settlement.z);

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
		if (inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR
		if (inNodes(node3))
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
		if (inNodes(node1))
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
			if (inNodes(node1))
			{
				adjacent_nodes[0] = node1;
			}
			//else ERROR
		}

		node2 = { settlement.x, settlement.z, 0 };
		if (inNodes(node2))
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
			if (inNodes(node1))
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
		if (inNodes(node3))
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
		if (inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		node2 = { min(settlement.x, c2), min(max(settlement.x, c2), settlement.y), max(max(settlement.x, c2), settlement.y) };
		if (inNodes(node2))
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

void Board::
getRoadAdjacentNodes(road_t road, coord_t * adjacent_nodes)
{
	BoardComponent *X, *Y, *Z;		//punteros a las piezas del tablero
	X = getPiece(road.x);
	Y = getPiece(road.y);
	Z = getPiece(road.z);

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
		if (inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (inNodes(node2))
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

		if (inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (inNodes(node2))
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

		if (inNodes(node1))
		{
			adjacent_nodes[0] = node1;
		}
		//else ERROR
		if (inNodes(node2))
		{
			adjacent_nodes[1] = node2;
		}
		//else ERROR
	}

}

Board::
~Board()
{
	delete[] all_the_hexes;
	delete[] all_the_sea_frames;
}