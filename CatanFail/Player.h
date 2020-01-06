#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "TerrainHexes.h"
#include "SeaFrameTiles.h"
#include "DevelopmentCard.h"
#include "Board.h"

using namespace std;

enum Actions {ADD, SUBTRACT};
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


class Player
{
	public:
		Player();	//settea todo en cero para comenzar

		void setName(string name);	//settea el nombre del jugador
		string getName(void);	//devuelve el nombre del jugador
		void setType(string type); //type: player u opponent
		string getType(void); // devuelve el tipo de jugador
		unsigned int getVictoryPoints(void);	//devuelve los victory points
		bool setVictoryPoints(unsigned int v_points, Actions action);	//suma o resta victory points, devuelve true si se pudo hacer sino el error es NEG_VP
		unsigned int getRoadsBuilt(void);	//devuleve la cantidad de caminos que construí
		unsigned int getSettlementsBuilt(void);	//devuelve la cantidad de asentamientos que construí 
		unsigned int getCitiesBuilt(void);	//devuelve la cantidad de ciudades que construí
		bool useDevelopmentCard(DevelopmentCards d_card);	//"usa" la development card que quiero usar, devuelve true si se pudo hacer sino el error es NO_DCARD
		unsigned int getDiceNumber(void);	//devuelve el número que salío al tirar los dados

		unsigned int getResourceCards();

		void setBoard(Board * board_);	//IMPORTANTE!!!!

		void setLongest(unsigned int value); //setter de myLongest
		unsigned int getLongest();			//getter de myLongest

		//(los siguientes tres métodos) devuelven true si puedo contruir un camino, 
		//un asentamiento o una ciudad respectivamente en base a mis cartas
		bool buildRoad(char x, char y, char z = 0);	//falta chequear el road anterior
		bool buildSettlement(char x, char y, char z = 0);	//falta chequear la distancia
		bool buildCity(char x, char y, char z = 0);

		//devuelven true si hay algo construido en los lugares especificados
		bool searchRoad(char x, char y, char z = 0);
		bool searchRoad(road_t road);
		bool searchBuilding(char x, char y, char z = 0);
		bool searchBuilding(coord_t coords);

		//si hay un settlement/city en el hexagono especificado, levanta las cartas que tenga que levantar
		void checkHexBuilding(char hex);
		void checkHexBuilding(TerrainHexes &hex);
		
		bool askForTrade(vector<char> r_cards_offered, vector<char> r_cards_wanted);	//necesito network acá
		bool domesticTrade(vector<char> r_cards_offered, vector<char> r_cards_wanted); // with opponent -- puedo hacer trades de mas de una carta!!!!!
		

		bool maritimeTrade(Resources my_r_card, Resources the_r_card_i_want, MaritimeTradeType trade); //se fija si tengo las cartas para el intercambio, devuelve true si lo hizo
		bool bankTrade(Resources my_r_card, Resources the_r_card_wanted); //se fija si tengo las cartas necesarias para el intercambio, devuelve true si lo hizo

		bool BuyDevelopmentCard();	//solamente se fija si tengo las cartas de recurso necesarias y las resta, devuelve true si las tengo
		void addDevelopmentCard(DevelopmentCard my_new_card);//agrega la carta que toco

		void throwTheDices(void);	//toma dos números al azar, los suma y los guarda en dice_number

		bool gameWon(void); //se fija si tengo los victory points necesarios para ganar, devuelve true si gané

		~Player();

	private:

		void grabResourceCard(Resources resource, PieceType piece);

		string name;
		string type;

		Board * board;

		unsigned int total_roads;
		unsigned int total_settlements;
		unsigned int total_cities;

		unsigned int victory_points;

		unsigned int myLongest;		//contador de longest road

		vector <road_t> roads_built;
		vector <settlement_t> settlements_built;
		vector <city_t> cities_built;

		myResourseCards_t my_r_cards;
		vector <DevelopmentCard> my_d_cards;

		unsigned int dice_number;

		Player_Error error;	//está re basico, podría mejorarse

};