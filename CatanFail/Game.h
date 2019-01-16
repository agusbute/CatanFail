#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stack>

#include "Board.h"
#include "Player.h"
#include "DevelopmentCard.h"
#include "Input.h"
#include "Graphics.h"

#define TOTAL_D_CARDS 25
#define TOTAL_KNIGHT_CARDS 14
#define TOTAL_V_POINT_CARDS 5
#define TOTAL_MONO_CARDS 2
#define TOTAL_YEAR_OF_P_CARDS 2
#define TOTAL_R_BUILDING_CARDS 2

class Game
{
	public:
		Game();
		~Game();
		void createDevelopmentCards(void);
		void play(void);	//fsm global
		bool checkRoad(char x, char y); //justo antes de player->buildRoad(x,y)
		bool checkLongestRoad(char x, char y); //justo despues de player->buildRoad(x,y)
		unsigned int longestRecursive(char x, char y); //recursiva para chequear 
	private:
		Player * player;
		Board * board;
		stack <DevelopmentCard> development_cards;

};