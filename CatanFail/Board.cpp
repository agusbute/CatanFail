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
				if (all_the_hexes[i].getToken() == 7)	//si tiene toke 7, es el desierto
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
inVertices(coord_t coord)
{
	bool ret = false;
	for (int i = 0; i < Vertices.size(); i++)
	{
		ret = (ret || (coord.x == Vertices[i].x && coord.y == Vertices[i].y && coord.z == Vertices[i].z));
	}
	return ret;
}

Board::
~Board()
{
	delete[] all_the_hexes;
	delete[] all_the_sea_frames;
}