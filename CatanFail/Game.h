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
		
		void play(void);	//fsm global
		
		void createDevelopmentCards(void);
		
		void incrementTurnCounter(); //CUANDO SE HAGA EL "PASS" LLAMAR A ESTA FUNCION (tambien cuando el otro jugador haya hecho pass)
		unsigned int getTurnCounter();
		
		bool checkRoad(road_t road);				//	justo antes de player->buildRoad(x,y)	
		bool checkRoad(char x, char y, char z = 0); //	
		bool checkLongestRoad(char x, char y, char z = 0); //justo despues de player->buildRoad(x,y)

		bool checkSettlement(settlement_t settlement);	//justo antes de player->buildSettlement(x,y,z);
		bool checkSettlement(char x, char y, char z = 0);

		bool moveRobber(TerrainHexes &place_robber_here);

	private:
		void getAdjacentRoads(road_t main_road, road_t * adjacent_roads); //devuelve en adjacent_roads las 4(o 3, o 2, siendo algunas {0,0,0}) calles adyacentes a road
		void getNodeAdjacentRoads(settlement_t settlement, road_t * adjacent_roads); //devuelve en adjacent_roads las 3 o 2 calles adyacentes a settlement
		void getAdjacentNodes(settlement_t settlement, coord_t * adjacent_nodes); //devuelve en adjacent_nodes los 3 o 2 nodos adyacentes a settlement
		unsigned int longestRecursive(road_t road, vector <road_t> &previous_roads, unsigned int length = 0); //recursiva para chequear longest road
		bool inPreviousRoads(road_t road, vector <road_t> &previous_roads);	//devuelve true is road esta en previous_road

		unsigned int turnCounter;
		
		Player * player;
		Player * oponent;
		Board * board;
		stack <DevelopmentCard> development_cards;
};