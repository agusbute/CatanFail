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
	char* random_tokens = new char[TERRAIN_HEXES];	//arreglo temporal en el que guardo los tokens
	fill_n(random_tokens, TERRAIN_HEXES, 0);	//completa todo en 0
	createRandomTokens(random_tokens);	//cargo los tokens al azahar 

	char letter = 'A';	//para las posiciones de los hex
	for (int i = 0; i < TERRAIN_HEXES; i++, letter++)	//va setteando cada uno de los hexagonos
	{
		all_the_hexes[i].setPositionInMap(letter);	//con la posición en el tablero
		all_the_hexes[i].setToken(random_tokens[i]);	//el token que tiene
		//all_the_hexes[i].setResource();	//y lo que produce
	}
	delete[] random_tokens;	//porque ya los tiene cada hex

	char number = '0';	//para las posiciones de los sea frames
	for (int j = 0; j < SEA_FRAME_TILES; j++, number++)	//lo mismo con las piezas de mar
	{
		all_the_sea_frames[j].setPositionInMap(number);	//con la posición en el tablero
		//all_the_sea_frames[i].setHarbors();	//y el/los puerto/s que tiene
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
	
	if ((token == 7 && repeated_token < 1) || (token != 7 && repeated_token < 2))	//el siete solo puede estar una vez (va a ser el del desierto) y el resto dos veces
	{
		token_is_used = false;
	}

	return token_is_used;
}

Board::
~Board()
{
	delete[] all_the_hexes;
	delete[] all_the_sea_frames;
}