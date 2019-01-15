#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stack>
#include "DevelopmentCard.h"

#define TOTAL_D_CARDS 25

class Game
{
	public:
		void createDevelopmentCards(void);
		void play(void);	//fsm global
	
	private:
		stack <DevelopmentCard> development_cards;
};