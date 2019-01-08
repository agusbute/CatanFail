#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

class Player
{
	public:

		Player(string name, int v_points);
		void setName(string name);
		int getVictoryPoints(void);
		void setVictoryPoints(int v_points);
		int getRoadsBuilt(void);
		int getSettlementsBuilt(void);
		int getCitiesBuilt(void);
		int getDevelopmentCard(void);
		int getResourceCard(char r_card); 	//se fija si tiene la carta de recurso que se requiere

		bool buildRoad();
		bool buildSettlement();
		bool buildCity();

		void moveRobber();
		void tradeResourceCard(char r_card);

		void throw_the_dices(void);

		~Player();

	private:
		string name;
		int victory_points;
		int roads_built;
		int settlements_built;
		int cities_built;
		//char* resource_cards;   \ deberían ser
		//char* developmen_cards; /    listas
		int dice_number;
};