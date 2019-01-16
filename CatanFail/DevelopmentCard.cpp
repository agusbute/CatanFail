#pragma once

#include "DevelopmentCard.h"

DevelopmentCard::
DevelopmentCard()
{

}

DevelopmentCard::
DevelopmentCard(DevelopmentCards d_type)
{
	this->ready_to_use = false;
	this->d_type = d_type;
}

DevelopmentCards DevelopmentCard::
getType()
{
	return d_type;
}

bool DevelopmentCard::
canUseThisCard()
{
	return ready_to_use;
}

void DevelopmentCard::
setToUse()
{
	this->ready_to_use = true;
}

DevelopmentCard::
~DevelopmentCard()
{

}