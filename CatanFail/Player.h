#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace :: std;

enum Actions {ADD, SUBTRACT};
enum DevelopmentCards {KNIGHT, V_POINT, L_ROAD, L_ARMY, PROG};	//Development Cards: Knight, Victory Point, Longest Road, Largest Army, Progress
enum Resources {LUMBER, BRICK, ORE, GRAIN, WOOL, DESERT, NOTHING}; //Resource Cards: Lumber, Brick, Ore, Grain, Wool, Desert and Nothing se usan para los hexágonos
enum MaritimeTradeType {THREE_X_ONE, TWO_X_ONE};	
enum Player_Error { NEG_VP, NO_DCARD};	//NEG_VP = Victory Points negativos, NO_DCARD = no tengo esa carta de resurso

typedef struct 
{
	unsigned int lumber;
	unsigned int brick;
	unsigned int ore;
	unsigned int grain;
	unsigned int wool;
} myResourseCards_t;	//son todas las resource cards que tengo


typedef struct
{
	unsigned int knight;
	unsigned int victory_point;
	unsigned int longest_road;	//no se si van acá esta y la siguiente pero en la consigna están así
	unsigned int largest_army;
	unsigned int progress;
} myDevelopmentCards_t;	//son todas las development cards que tengo si es que juego con ellas

class Player
{
public:
	Player(string name);	//settea el nombre del jugador y todo en cero para comenzar
	void setName(string name);	//settea el nombre del jugador
	string getName(void);	//devuelve el nombre del jugador
	unsigned int getVictoryPoints(void);	//devuelve los victory points
	bool setVictoryPoints(unsigned int v_points, Actions action);	//suma o resta victory points, devuelve true si se pudo hacer sino el error es NEG_VP
	unsigned int getRoadsBuilt(void);	//devuleve la cantidad de caminos que construí
	unsigned int getSettlementsBuilt(void);	//devuelve la cantidad de asentamientos que construí 
	unsigned int getCitiesBuilt(void);	//devuelve la cantidad de ciudades que construí
	bool getDevelopmentCard(DevelopmentCards d_card);	//"usa" la development card que quiero usar, devuelve true si se pudo hacer sino el error es NO_DCARD
	unsigned int getDiceNumber(void);	//devuelve el número que salío al tirar los dados

	//(los siguientes tres métodos) devuelven true si tengo las cartas de recurso necesarias 
	//para construir un camino, un asentamiento o una ciudad respectivamente
	bool buildRoad(void); 
	bool buildSettlement(void);
	bool buildCity(void);

	/******************************************************FALTAN ESTAS********************************************/
	void moveRobber();
	
	void domesticTrade(Resources my_r_card, Resources the_r_card_wanted); // with opponent // puedo hacer trades de mas de una carta!!!!!
	/*************************************************************************************************************/
	
	bool maritimeTrade(Resources my_r_card, Resources the_r_card_i_want, MaritimeTradeType trade); //se fija si tengo las cartas para el intercambio, devuelve true si lo hizo
	bool bankTrade(Resources my_r_card, Resources the_r_card_wanted); //se fija si tengo las cartas necesarias para el intercambio, devuelve true si lo hizo
	
	bool BuyDevelopmentCard(void);	//solamente se fija si tengo las cartas de recurso necesarias y las resta, devuelve true si las tengo
	//debería haber uno que me agregue la que me tocó, ahora tengo sueño para hacerlo (tipo el setter de las r card)
	//vendría la d cart desde el tablero

	void throwTheDices(void);	//toma dos números al azar, los suma y los guarda en dice_number
	
	bool gameWon(void); //se fija si tengo los victory points necesarios para ganar, devuelve true si gané

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

	Player_Error error;	//está re basico, podría mejorarse

		/********************************/
		//char* resource_cards;   \ deberían ser
		//char* developmen_cards; /    listas		//estas son opcionales
};