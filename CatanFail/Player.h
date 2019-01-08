#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace :: std;

enum Actions { ADD, SUBTRACT, EQUAL};
enum DevelopmentCards {K, V, C, M, P};	// Development Cards: Knight, Victory Point, ..., ..., Progress
enum ResourceCards {M, L, P, T, O, N}; //Resource Cards: Lumber, Brick, Ore, Grain, Wood, Nothing

class Player
{
	public:
		Player(string name, int v_points);
		void setName(string name);
		int getVictoryPoints(void);
		bool setVictoryPoints(int v_points, Actions action);
		int getRoadsBuilt(void);
		int getSettlementsBuilt(void);
		int getCitiesBuilt(void);
		int getDevelopmentCard(DevelopmentCards d_card);	//estas son opcionales
		int getResourceCard(ResourceCards r_card); 	//se fija si tiene la carta de recurso que se requiere

		bool buildRoad();
		bool buildSettlement();
		bool buildCity();

		void moveRobber();
		void domesticTrade(ResourceCards r_card, ResourceCards the_r_card_i_want); // with opponent // puedo hacer trades de mas de una carta!!!!!
		void maritimeTrade(); 


		void throw_the_dices(void);

		bool GameWon(); // returns 0 if i won

		//~Player();

	private:
		string name;
		int victory_points;
		int roads_built;
		int settlements_built;
		int cities_built;
		//char* resource_cards;   \ deberían ser
		//char* developmen_cards; /    listas		//estas son opcionales
		int dice_number;
};