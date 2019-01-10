#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace :: std;

enum Actions { ADD, SUBTRACT};
enum DevelopmentCards {KNIGHT, V_POINT, L_ROAD, L_ARMY, PROG};	// Development Cards: Knight, Victory Point, Longest Road, Largest Army, Progress
enum ResourceCards {LUMBER, BRICK, ORE, GRAIN, WOOL}; //Resource Cards: Lumber, Brick, Ore, Grain, Wool
enum Player_Error { NEG_VP, NO_DCARD};	// Victory Points Negativos

typedef struct 
{
	unsigned int lumber;
	unsigned int brick;
	unsigned int ore;
	unsigned int grain;
	unsigned int wool;
} myResourseCards_t;


typedef struct
{
	unsigned int knight;
	unsigned int victory_point;
	unsigned int longest_road;	//no se si van acá esta y la siguiente pero en la consigna están así
	unsigned int largest_army;
	unsigned int progress;
} myDevelopmentCards_t;

class Player
{
public:
	Player(string name);
	void setName(string name);
	unsigned int getVictoryPoints(void);
	bool setVictoryPoints(unsigned int v_points, Actions action);
	unsigned int getRoadsBuilt(void);
	unsigned int getSettlementsBuilt(void);
	unsigned int getCitiesBuilt(void);
	bool getDevelopmentCard(DevelopmentCards d_card);	//estas son opcionales	//devuelve 0 si hubo error
	// unsigned int getResourceCard(ResourceCards r_card);

	// devuelven uno si tiene las cartas de recurso necesarias para construir cada cosa
	bool buildRoad(void); 
	bool buildSettlement(void);
	bool buildCity(void);

	void moveRobber();
	void domesticTrade(ResourceCards r_card, ResourceCards the_r_card_i_want); // with opponent // puedo hacer trades de mas de una carta!!!!!
	void maritimeTrade();
	
	bool buyDevelopmentCard(void);	//solamente se fija si tengo las cartas de desarrollo necesarias


	void throw_the_dices(void);

	bool GameWon(void); // returns 1 if i won

	//~Player();

private:
	string name;
	unsigned int total_roads;
	unsigned int total_settlements;
	unsigned int total_cities;
	unsigned int victory_points;
	unsigned int roads_built;
	unsigned int settlements_built;
	unsigned int cities_built;
	myResourseCards_t my_r_cards;
	myDevelopmentCards_t my_d_cards;
	unsigned int dice_number;

	Player_Error error;

		/********************************/
		//char* resource_cards;   \ deberían ser
		//char* developmen_cards; /    listas		//estas son opcionales
};