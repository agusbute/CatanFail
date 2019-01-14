#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace :: std;

class BoardComponent	//clase padre de las piezas de mar y los hexagonos
{
	public:
		BoardComponent(char position_in_map);	//settea la posición que tiene en el mapa
		void setPositionInMap(void);	//setter para lo mismo que el constructor
		char getPositionInMap(void);	//devuelve la posición de la pieza en el mapa

	private:
		char position_in_map;	//posición de la pieza en el mapa


};
