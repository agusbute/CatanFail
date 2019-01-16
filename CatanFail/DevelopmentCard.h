#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum DevelopmentCards { KNIGHT, V_POINT, YEAR_OF_P, MONO, R_BUILDING };	//Development Cards: Knight, Victory Point, Year Of Plenty, Monopoly, Road Building

class DevelopmentCard
{
	public:
		DevelopmentCard();
		DevelopmentCard(DevelopmentCards d_type);	//inicializa ready_to_use = false
		DevelopmentCards getType();	//devuelve el tipo desarrollo
		bool canUseThisCard();	//devuelve ready_to_use
		void setToUse();	//settea ready_to_use = true
		
		~DevelopmentCard();

	private:
		DevelopmentCards d_type;	//tiene el tipo de development card que es
		bool ready_to_use;	//true si puedo usarla, false si recién la compré 
};