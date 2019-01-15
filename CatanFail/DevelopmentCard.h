#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Player.h""

class DevelopmentCard
{
	public:
		DevelopmentCard(DevelopmentCards d_type);	//inicializa ready_to_use = false
		DevelopmentCards getType();	//devuelve el tipo desarrollo
		bool canUseThisCard();	//devuelve ready_to_use
		void setToUse();	//settea ready_to_use = true
		
		~DevelopmentCard();

	private:
		DevelopmentCards d_type;	//tiene el tipo de development card que es
		bool ready_to_use;	//true si puedo usarla, false si recién la compré 
};