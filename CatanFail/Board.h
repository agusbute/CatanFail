#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "TerrainHexes.h"
#include "SeaFrameTiles.h"

using namespace ::std;

#define TERRAIN_HEXES 19	//cantidad total de hexagonos
#define SEA_FRAME_TILES 6	//cantidad total de piezas de mar



class Board
{
	public:
		Board();	//new con los hexagonos y las piezas de mar, todo en 0
		void initToStartGame();	//inicializa cada componente del tablero
		
		void searchResource(int dice_number);
		
		/************* FALTA UNO COMO EL DE ABAJO PARA LOS RECURSOS Y LOS PUERTOS (?) ***************/	//lo uso en el init
		void createRandomTokens(char* random_tokens);	//crea una lista con los tokens al azahar 
		bool tokenExists(char* random_tokens, char token);	//devuelve false si todavía puedo usar ese token
		TerrainHexes searchPiece(char info);
		~Board();


	private:
		TerrainHexes* all_the_hexes;	//puntero al arreglo de hexagonos
		SeaFrameTiles* all_the_sea_frames;	//puntero al arreglo de piezas de mar
		// cartas de desarrollo
		//cartas de recurso ¡son ilimitadas!
		
	
};


