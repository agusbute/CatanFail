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
#define TOTAL_KNIGHT_CARDS 14
#define TOTAL_V_POINT_CARDS 5
#define TOTAL_MONO_CARDS 2
#define TOTAL_YEAR_OF_P_CARDS 2
#define TOTAL_R_BUILDING_CARDS 2

class Game
{
	public:
		void createDevelopmentCards(void);
		void play(void);	//fsm global
	
	private:
		stack <DevelopmentCard> development_cards;
};