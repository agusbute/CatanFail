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

	//setteo las development cards = 0  
	my_d_cards.knight = 0;	
	my_d_cards.largest_army = 0;
	my_d_cards.longest_road = 0;
	my_d_cards.progress = 0;
	my_d_cards.victory_point = 0;

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

unsigned int Player::
getRoadsBuilt(void)
{
	return this->roads_built;
}

unsigned int Player::
getSettlementsBuilt(void)
{
	return this->settlements_built;
}

unsigned int Player::
getCitiesBuilt(void)
{
	return this->cities_built;
}

bool Player::
getDevelopmentCard( DevelopmentCards d_card)
{
	bool successfully_used = false;

	switch (d_card)	//me fijo que tipo de carta quiero usar
	{
		case KNIGHT:
			if (my_d_cards.knight >= 1)	//si tengo al menos una, la uso
			{
				my_d_cards.knight -= 1;
				successfully_used = true;
			}
			else
			{
				error = NO_DCARD;	//no tengo esa development card
			}
			break;
		
		case V_POINT:
			if (my_d_cards.victory_point >= 1)
			{
				my_d_cards.victory_point -= 1;
				successfully_used = true;
			}
			else
			{
				error = NO_DCARD;
			}
			break;

		case L_ROAD:
			if (my_d_cards.longest_road >= 1)
			{
				my_d_cards.longest_road-= 1;
				successfully_used = true;
			}
			else
			{
				error = NO_DCARD;
			}
			break;

		case L_ARMY:
			if (my_d_cards.largest_army >= 1)
			{
				my_d_cards.largest_army -= 1;
				successfully_used = true;
			}
			else
			{
				error = NO_DCARD;
			}
			break;

		case PROG:
			if (my_d_cards.progress >= 1)
			{
				my_d_cards.progress -= 1;
				successfully_used = true;
			}
			else
			{
				error = NO_DCARD;
			}
			break;

		default: break;
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
buildRoad(void)
{
	bool road_is_built = false;

	if (roads_built < 2 && total_roads > 13)	//se fija si está en el primer o segundo turno
	{
		roads_built += 1;	//agrega a la cantidad de caminos construidos
		total_roads -= 1;	//saca de los caminos restantes
		road_is_built = true;
	}
	else if (total_roads > 0 && my_r_cards.brick >= 1 && my_r_cards.lumber >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias y caminos para usar
	{
		my_r_cards.brick -= 1;	//uso las cartas necesarias
		my_r_cards.lumber -= 1;
		total_roads -= 1;	//setteo caminos contruidos y restantes
		roads_built += 1;
		road_is_built = true;
	}

	return road_is_built;
}

bool Player::
buildSettlement(void)
{
	bool settlement_is_built = false;

	if (settlements_built < 2 && total_settlements > 3)	//se fija si está en el primer o segundo turno
	{
		total_settlements -= 1;	//saco de los asentamientos restantes
		settlements_built += 1;	//agrego a los que tengo construidos
		settlement_is_built = true;
	}
	else if (total_settlements > 0 && my_r_cards.brick >= 1 && my_r_cards.grain >= 1 && my_r_cards.lumber >= 1 && my_r_cards.wool >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias
	{
		my_r_cards.brick -= 1;	//"uso" las cartas que se requieren
		my_r_cards.grain -= 1;
		my_r_cards.lumber -= 1;
		my_r_cards.wool -= 1;
		total_settlements -= 1;	//setteo los asentamientos contruidos y los restantes
		settlements_built += 1;
		settlement_is_built = true;
	}

	return settlement_is_built;
}

bool Player::
buildCity(void)
{
	bool city_is_built = false;

	if (total_cities > 0 && settlements_built >= 1 && my_r_cards.ore >= 3 && my_r_cards.grain >= 2)	//se fija si hay al menos un settlement y si tiene las cartas de recurso necesarias
	{
		my_r_cards.ore -= 3;	//"uso" las cartas que se necesitan
		my_r_cards.grain -= 2;
		settlements_built -= 1;	//quito el asentamiento construido
		total_settlements += 1; //recupero ese asentamiento
		total_cities -= 1;	//saco de las ciudades restantes
		cities_built += 1;	//agrego a las que tengo
		city_is_built = true;
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
BuyDevelopmentCard(void)	
{
	bool new_development_card = false;

	if (my_r_cards.ore >= 1 && my_r_cards.wool >= 1 && my_r_cards.grain >= 1)	//se fija si tengo las cartas de recurso necesarias para comprar una development card
	{
		my_r_cards.ore -= 1;	//"uso" las cartas que necesito
		my_r_cards.wool -= 1;
		my_r_cards.grain -= 1;
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

//~Player();

