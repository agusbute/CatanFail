#include "BoardComponent.h"

BoardComponent :: 
BoardComponent(char position_in_map)
{
	setPositionInMap(position_in_map);
}

void BoardComponent::
setPositionInMap(char position_in_map)
{
	this->position_in_map = position_in_map;
}

char BoardComponent::
getPositionInMap(void)
{
	return position_in_map;
}
