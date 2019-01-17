#include "Player.h"

Player::
Player(string name)
{
	setName(name);

	//setteo las resource cards = 0
	my_r_cards.brick = 0;
	my_r_cards.grain = 0;
	my_r_cards.lumber = 0;
	my_r_cards.ore = 0;
	my_r_cards.wool = 0;

	//setteo longest = 0
	myLongest = 0;

	//setteo las piezas que tengo
	total_roads = 15;
	total_settlements = 5;
	total_cities = 4;

	//setteo victory points = 0
	victory_points = 0;
}

void Player::
setName(string name)
{
	this->name = name;
}

string Player::
getName(void)
{
	return this->name;
}

unsigned int Player::
getVictoryPoints(void)
{
	return this->victory_points;
}

bool Player::
setVictoryPoints(unsigned int v_points, Actions action)
{
	bool successfully_setted = false;

	switch (action)
	{
		case ADD:	//le sumo puntos
			this->victory_points += v_points;
			successfully_setted = true;
			break;

		case SUBTRACT:	//le resto puntos
			if (this->victory_points > 0)
			{
				this->victory_points -= v_points; //(supongo que no puedo tener victory points negativos)
				successfully_setted = true;
			}
			else
			{
				this->error = NEG_VP;	//victory points negativos
			}
			break;

		default: break;
	}

	return successfully_setted;
}

void Player::
setLongest(unsigned int value)
{
	this->myLongest = value;
}

unsigned int Player::
getLongest()
{
	return this->myLongest;
}

unsigned int Player::
getRoadsBuilt(void)
{
	return this->roads_built.size();
}

unsigned int Player::
getSettlementsBuilt(void)
{
	return this->settlements_built.size();
}

unsigned int Player::
getCitiesBuilt(void)
{
	return this->cities_built.size();
}


bool Player::
getDevelopmentCard(DevelopmentCards d_card)
{
	bool successfully_used = false;

	for (int i = 0; i < my_d_cards.size(); i++)	//me fijo si tengo una carta de esas
	{
		if (my_d_cards[i].getType() == d_card)	//si está
		{
			my_d_cards.erase(my_d_cards.begin() + i);	//la "uso"
			successfully_used = true;
		}
	}
	return successfully_used;
}

	

/*
unsigned int Player::
getResourceCard(ResourceCards r_card)
{

}
*/

unsigned int Player::
getDiceNumber(void)
{
	return dice_number;
}

bool Player::
buildRoad(char x, char y, char z)
{
	bool road_is_built = false;
	road_t road = { x, y, z };
	
	if (roads_built.size() < 2 && total_roads > 13)	//se fija si está en el primer o segundo turno
	{
		for (int i = 0; i < roads_built.size(); i++)
		{
			if (roads_built[i].x != road.x || roads_built[i].y != road.y)
			{
				roads_built.push_back(road);	//agrega a la cantidad de caminos construidos
				total_roads -= 1;	//saca de los caminos restantes
				road_is_built = true;
			}
		}
	}
	else if (total_roads > 0 && my_r_cards.brick >= 1 && my_r_cards.lumber >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias y caminos para usar
	{
		for (int i = 0; i < roads_built.size(); i++)
		{
			if (roads_built[i].x != road.x || roads_built[i].y != road.y)
			{
				my_r_cards.brick -= 1;	//uso las cartas necesarias
				my_r_cards.lumber -= 1;
				total_roads -= 1;	//setteo caminos contruidos y restantes
				roads_built.push_back(road);
				road_is_built = true;
			}
		}
	}
	return road_is_built;
}
bool Player::
searchRoad(char x, char y, char z)
{
	bool ret = false;
	for (int i = 0; i < roads_built.size(); i++)
	{
		if (roads_built[i].x == x && roads_built[i].y == y && roads_built[i].z == z)
		{
			ret = true;
		}
	}
	return ret;
}
bool Player::
searchRoad(road_t road)
{
	return searchRoad(road.x, road.y, road.z);
}

bool Player::
buildSettlement(char x, char y, char z)
{
	bool settlement_is_built = false;
	settlement_t settlement = { x, y, z };
	if (settlements_built.size() < 2 && total_settlements > 3)	//se fija si está en el primer o segundo turno
	{
		for (int i = 0; i < settlements_built.size(); i++)
		{
			if (settlements_built[i].x != settlement.x || settlements_built[i].y != settlement.y || settlements_built[i].z != settlement.z)
			{
				total_settlements -= 1;	//saco de los asentamientos restantes
				settlements_built.push_back(settlement);	//agrego a los que tengo construidos
				settlement_is_built = true;
			}
		}
	}
	else if (total_settlements > 0 && my_r_cards.brick >= 1 && my_r_cards.grain >= 1 && my_r_cards.lumber >= 1 && my_r_cards.wool >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias
	{
		if (settlements_built.size() < 2 && total_settlements > 3)	//se fija si está en el primer o segundo turno
		{
			for (int i = 0; i < settlements_built.size(); i++)
			{
				if (settlements_built[i].x != settlement.x || settlements_built[i].y != settlement.y || settlements_built[i].z != settlement.z)
				{
					//if para ver si tiene los roads que necesita
					my_r_cards.brick -= 1;	//"uso" las cartas que se requieren
					my_r_cards.grain -= 1;
					my_r_cards.lumber -= 1;
					my_r_cards.wool -= 1;
					total_settlements -= 1;	//setteo los asentamientos contruidos y los restantes
					settlements_built.push_back(settlement);
					settlement_is_built = true;
				}
			}
		}
	}

	return settlement_is_built;
}

bool Player::
buildCity(char x, char y, char z)
{
	bool city_is_built = false;
	settlement_t settlement = { x, y, z };
	if (total_cities > 0 && settlements_built.size() >= 1 && my_r_cards.ore >= 3 && my_r_cards.grain >= 2)	//se fija si hay al menos un settlement y si tiene las cartas de recurso necesarias
	{
		my_r_cards.ore -= 3;	//"uso" las cartas que se necesitan
		my_r_cards.grain -= 2;
		for (int i = 0; i < settlements_built.size(); i++)
		{
			if (settlements_built[i].x == settlement.x && settlements_built[i].y == settlement.y && settlements_built[i].z == settlement.z)
			{
				settlements_built.erase(settlements_built.begin()+i); //quito el asentamiento construido
				total_settlements += 1; //recupero ese asentamiento
				total_cities -= 1;	//saco de las ciudades restantes
				city_t city = /*settlement;*/{ x, y, z };
				cities_built.push_back(city); //agrego la cuidad construida
				city_is_built = true;
			}
		}	
		
	}

	return city_is_built;
}

/****************************************** FALTAN ESTOS **********************************************/
void moveRobber();
void domesticTrade(Resources my_r_card, Resources the_r_card_i_want);
/*****************************************************************************************************/

bool Player::
maritimeTrade(Resources my_r_card, Resources the_r_card_i_want, MaritimeTradeType trade)
{
	bool resource_available = false;

	if (trade == THREE_X_ONE)	//me fijo que tipo de intercambio marítimo es ((((( se supone que llamo a este método si desde el tablero pued hacerlo )))))
	{
		//checkTrade()
		switch (my_r_card)	//y a partir de eso veo si tengo la cantidad de cartas necesarias para intercambiar
		{
			case LUMBER:
				if (my_r_cards.lumber >= 3)
				{
					my_r_cards.lumber -= 3;
					resource_available = true;
				}
				break;

			case BRICK:
				if (my_r_cards.brick >= 3)
				{
					my_r_cards.brick -= 3;
					resource_available = true;
				}
				break;

			case ORE:
				if (my_r_cards.ore >= 3)
				{
					my_r_cards.ore -= 3;
					resource_available = true;
				}
				break;

			case GRAIN:
				if (my_r_cards.grain >= 3)
				{
					my_r_cards.grain -= 3;
					resource_available = true;
				}
				break;

			case WOOL:
				if (my_r_cards.wool >= 3)
				{
					my_r_cards.wool -= 3;
					resource_available = true;
				}
				break;

			default: break;
		}

		if (resource_available == true)	//si tengo la cantidad necesaría, hice el intercambio
		{
			switch (the_r_card_i_want)	//entonces agrego a mis cartas la que recibí
			{
				case LUMBER:
					my_r_cards.lumber += 1;
					break;

				case BRICK:
					my_r_cards.brick += 1;
					break;

				case ORE:
					my_r_cards.ore += 1;
					break;

				case GRAIN:
					my_r_cards.grain += 1;
					break;

				case WOOL:
					my_r_cards.wool += 1;
					break;

				default: break;
			}
		}
	}

	else if (trade == TWO_X_ONE)	//lo mismo que el caso anterior
	{
		//checkTrade()
		switch (my_r_card)
		{
			case LUMBER:
				if (my_r_cards.lumber >= 2)
				{
					my_r_cards.lumber -= 2;
					resource_available = true;
				}
				break;

			case BRICK:
				if (my_r_cards.brick >= 2)
				{
					my_r_cards.brick -= 2;
					resource_available = true;
				}
				break;

			case ORE:
				if (my_r_cards.ore >= 2)
				{
					my_r_cards.ore -= 2;
					resource_available = true;
				}
				break;

			case GRAIN:
				if (my_r_cards.grain >= 2)
				{
					my_r_cards.grain -= 2;
					resource_available = true;
				}
				break;

			case WOOL:
				if (my_r_cards.wool >= 2)
				{
					my_r_cards.wool -= 2;
					resource_available = true;
				}
				break;

			default: break;
		}

		if (resource_available == true)
		{
			switch (the_r_card_i_want)
			{
				case LUMBER:
					my_r_cards.lumber += 1;
					break;

				case BRICK:
					my_r_cards.brick += 1;
					break;

				case ORE:
					my_r_cards.ore += 1;
					break;

				case GRAIN:
					my_r_cards.grain += 1;
					break;

				case WOOL:
					my_r_cards.wool += 1;
					break;

				default: break;
			}
		}
	}

	return resource_available;
}

bool Player::
bankTrade(Resources my_r_card, Resources the_r_card_wanted)
{
	bool resource_available = false;

	switch (my_r_card)	//veo si tengo la cantidad de cartas necesarias de las que quiero intercambiar
	{
		case LUMBER:
			if (my_r_cards.lumber >= 4)
			{
				my_r_cards.lumber -= 4;
				resource_available = true;
			}
			break;

		case BRICK:
			if (my_r_cards.brick >= 4)
			{
				my_r_cards.brick -= 4;
				resource_available = true;
			}
			break;

		case ORE:
			if (my_r_cards.ore >= 4)
			{
				my_r_cards.ore -= 4;
				resource_available = true;
			}
			break;

		case GRAIN:
			if (my_r_cards.grain >= 4)
			{
				my_r_cards.grain -= 4;
				resource_available = true;
			}
			break;

		case WOOL:
			if (my_r_cards.wool >= 4)
			{
				my_r_cards.wool -= 4;
				resource_available = true;
			}
			break;

		default: break;
	}

	if (resource_available == true)	//si las tengo, hice el intercambio
	{
		switch (the_r_card_wanted)	//y recibo la carta que quería
		{
			case LUMBER:
				my_r_cards.lumber += 1;
				break;

			case BRICK:
				my_r_cards.brick += 1;
				break;

			case ORE:
				my_r_cards.ore += 1;
				break;

			case GRAIN:
				my_r_cards.grain += 1;
				break;

			case WOOL:
				my_r_cards.wool += 1;
				break;

			default: break;
		}
	}

	return resource_available;
}

bool Player::
BuyDevelopmentCard(DevelopmentCard my_new_card)	
{
	bool new_development_card = false;

	if (my_r_cards.ore >= 1 && my_r_cards.wool >= 1 && my_r_cards.grain >= 1)	//se fija si tengo las cartas de recurso necesarias para comprar una development card
	{
		my_r_cards.ore -= 1;	//"uso" las cartas que necesito
		my_r_cards.wool -= 1;
		my_r_cards.grain -= 1;

		my_d_cards.push_back(my_new_card);	//la agrego a mis cartas de desarrollo 

		new_development_card = true;
	}

	return new_development_card;
}

void Player::
throwTheDices(void)
{
	unsigned int first_dice = 0, second_dice = 0;
	srand(time(NULL));	//inicializo la semilla
	first_dice = rand() % 6 + 1;	//tiro el primer dado
	second_dice = rand() % 6 + 1;	//tiro el segundo dado
	dice_number = first_dice + second_dice;	//guardo lo que suman ambos
}

bool Player::
gameWon(void)
{
	bool am_i_the_winner = false;
	 
	if (getVictoryPoints() >= 8)	//si tengo 8 o mas puntos, gané
	{
		am_i_the_winner = true;	
	}

	return am_i_the_winner;
}

city_t& Player::
operator= (const settlement_t &settlement_to_upgrade)
{
	city_t new_city;
	new_city.x = settlement_to_upgrade.x;
	new_city.y = settlement_to_upgrade.y;
	new_city.z = settlement_to_upgrade.z;
	return new_city;
}

Player::
~Player()
{

}

