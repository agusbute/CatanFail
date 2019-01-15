#pragma once

#include "SeaFrameTiles.h"

SeaFrameTiles ::
SeaFrameTiles(char position_in_map) : BoardComponent(position_in_map)
{
	//no se como poner los puertosssssssssss
};

bool SeaFrameTiles::
setPorts(char ports)		//devuelve true si no hubo errores
{
	bool ret = true; //asumo que el parametro ports es valido
	
	switch (ports) 
	{
		case 'N': case 'n':
		{
			myPorts.port1 = ANY;
		}break;
		
		case 'T': case 't':
		{
			myPorts.port1 = ANY;
			myPorts.port2 = WHEAT;
		}break;

		case 'O': case 'o':
		{
			myPorts.port1 = ANY;
			myPorts.port2 = SHEEP;
		}break;
			
		case 'L': case 'l':
		{
			myPorts.port1 = ANY;
			myPorts.port2 = BRICK;
		}break;
		
		case 'P': case 'p':
		{
			myPorts.port1 = STONE;
		}break;
		
		case 'M': case 'm':
		{
			myPorts.port1 = WOOD;
		}break;

		default: ret = false; break;  //se introdujo un caracter incorrectos
	}
	return ret;
}