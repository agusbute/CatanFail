#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include "TerrainHexes.h"
#include "SeaFrameTiles.h"

using namespace std;

class Board
{
	public:
		Board();	//new con los hexagonos y las piezas de mar, todo en 0
		void initToStartGame();	//inicializa cada componente del tablero
		
		void searchResource(int dice_number);
		
		/************* FALTA UNO COMO EL DE ABAJO PARA LOS RECURSOS Y LOS PUERTOS (?) ***************/	//lo uso en el init
		void createRandomTokens(char* random_tokens);	//crea una lista con los tokens al azahar 
		bool tokenExists(char* random_tokens, char token);	//devuelve false si todavía puedo usar ese token
		BoardComponent * getPiece(char info);
		TerrainHexes * searchHexPiece(char info);
		SeaFrameTiles * searchSeaPiece(char info);
		bool inEdges(coord_t coord); //devuelve true si la coordenada introducida esta en Edges
		bool inNodes(coord_t coord); //devuelve true si la coordenada introducida esta en Vertices
		~Board();


	//no estan en private porque game necesita tener acceso a ellos
		TerrainHexes* all_the_hexes;	//puntero al arreglo de hexagonos
		SeaFrameTiles* all_the_sea_frames;	//puntero al arreglo de piezas de mar
	private:
		// cartas de desarrollo
		//cartas de recurso ¡son ilimitadas!
		const vector <coord_t> Edges = {
				{'0','A','5'}, {'0','A','B'}, {'0','B','A'}, {'0','B','C'}, {'0','C'}, {'1','C','0'},
									{'5','A'},{'A','B'},{'B','C'},{'1','C','G'},
			{'5','D','A'}, {'A','D'},{'A','E'}, {'B','E'}, {'B','F'}, {'C','F'}, {'C','G'}, {'1','G','C'},
							{'5','D','H'}, {'D','E'}, {'E','F'}, {'F','G'}, {'1','G','L'},
		{'5','H','D'}, {'D','H'}, {'D','I'}, {'E','I'}, {'E','J'}, {'F','J'}, {'F','K'}, {'G','K'}, {'G','L'}, {'1','L'},
						{'5','H','4'}, {'H','I'}, {'I','J'}, {'J','K'}, {'K','L'}, {'2','L','1'},
		{'4','H'}, {'H','M'}, {'I','M'}, {'I','N'}, {'J','N'}, {'J','O'}, {'K','O'}, {'K','P'}, {'L','P'}, {'2','L','P'},
							{'4','M','H'}, {'M','N'}, {'N','O'}, {'O','P'}, {'2','P','L'},
			{'4','M','Q'}, {'M','Q'}, {'N','Q'}, {'N','R'}, {'O','R'}, {'O','S'}, {'P','S'}, {'2','P','S'},
									{'4','Q','M'}, {'Q','R'}, {'R','S'}, {'2','S'},
				{'4','Q','3'}, {'3','Q'}, {'3','R','Q'}, {'3','R','S'}, {'3','S','R'}, {'3','S','2'}
		};
		const vector <coord_t> Nodes = {
									{'0','A'}, {'0','B'}, {'0','1','C'},

							  {'0','5','A'}, {'0','A','B'}, {'0','B','C'}, {'1','C'},

							{'5','A','D'}, {'A','B','E'}, {'B','C','F'}, {'1','C','G'},

						{'5','D'}, {'A','D','E'}, {'B','E','F'}, {'C','F','G'}, {'1','G'},

					{'5','D','H'}, {'D','E','I'}, {'E','F','J'}, {'F','G','K'}, {'1','G','L'},

				{'5','H'}, {'D','H','I'}, {'E','I','J'}, {'F','J','K'}, {'G','K','L'}, {'1','2','L'},

				{'4','5','H'}, {'H','I','M'}, {'I','J','N'}, {'J','K','O'}, {'K','L','P'}, {'2','L'},

					{'4','H','M'}, {'I','M','N'}, {'J','N','O'}, {'K','O','P'}, {'2','L','P'},

						{'4','M'}, {'M','N','Q'}, {'N','O','R'}, {'O','P','S'}, {'2','P'},

							{'4','M','Q'}, {'N','Q','R'}, {'O','R','S'}, {'2','P','S'},

							  {'4','Q'}, {'3','Q','R'}, {'3','R','S'}, {'2','3','S'},

									{'3','4','Q'}, {'3','R'}, {'3','S'}
		};
	
};



