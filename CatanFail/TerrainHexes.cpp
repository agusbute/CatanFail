#pragma once

#include "TerrainHexes.h"

TerrainHexes::
TerrainHexes(char position_in_map, Resources resource, int token) : BoardComponent(position_in_map)
{
	this->resource = resource;
	this->token = token;
}

void TerrainHexes::
setToken(char my_token)
{
	this->token = my_token;
}

char TerrainHexes::
getToken(void)
{
	return token;
}

void TerrainHexes::
setResource(Resources my_resource)
{
	this->resource = my_resource;
}

Resources TerrainHexes::
getResource(void)
{
	return resource;
}