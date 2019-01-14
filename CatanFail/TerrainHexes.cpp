#pragma once

#include "TerrainHexes.h"

TerrainHexes ::
TerrainHexes(char position_in_map, Resources resource, int token) : BoardComponent(position_in_map)
{
	this->resource = resource;
	this->token = token;
}