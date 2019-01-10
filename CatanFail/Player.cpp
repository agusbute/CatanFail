#include "Player.h"

Player::
Player(string name)
{
	setName(name);

	// setting all resource cards = 0
	my_r_cards.brick = 0;
	my_r_cards.grain = 0;
	my_r_cards.lumber = 0;
	my_r_cards.ore = 0;
	my_r_cards.wool = 0;

	// setting all development cards = 0
	my_d_cards.knight = 0;
	my_d_cards.largest_army = 0;
	my_d_cards.longest_road = 0;
	my_d_cards.progress = 0;
	my_d_cards.victory_point = 0;

	// setting my board components
	total_roads = 15;
	total_settlements = 5;
	total_cities = 4;
}

void Player::
setName(string name)
{
	this->name = name;
}

unsigned int Player::
getVictoryPoints(void)
{
	return this->victory_points;
}

bool Player::
setVictoryPoints(unsigned int v_points, Actions action)
{
	switch (action)
	{
		case ADD:
			this->victory_points += v_points;
			break;

		case SUBTRACT:
			if (this->victory_points > 0)
			{
				this->victory_points -= v_points; // supongo que no puedo tener victory points negativos
			}
			else
			{
				this->error = NEG_VP;
				return 1;
			}
			break;

		default: 
			return 1;	
			break;
	}

	return 0;
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
	switch (d_card)
	{
		case KNIGHT:
			if (my_d_cards.knight >= 1)
			{
				my_d_cards.knight -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;
		
		case V_POINT:
			if (my_d_cards.victory_point >= 1)
			{
				my_d_cards.victory_point -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		case L_ROAD:
			if (my_d_cards.longest_road >= 1)
			{
				my_d_cards.longest_road-= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		case L_ARMY:
			if (my_d_cards.largest_army >= 1)
			{
				my_d_cards.largest_army -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		case PROG:
			if (my_d_cards.progress >= 1)
			{
				my_d_cards.progress -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		default:
			return 0;
			break;
	}

	return 1;
}

/*
unsigned int Player::
getResourceCard(ResourceCards r_card)
{

}
*/

bool Player::
buildRoad(void)
{
	if (roads_built < 2 && total_roads > 13)	//se fija si está en el primer o segundo turno
	{
		roads_built += 1;
		total_roads -= 1;
	}
	else if (total_roads > 0 && my_r_cards.brick >= 1 && my_r_cards.lumber >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias
	{
		my_r_cards.brick -= 1;
		my_r_cards.lumber -= 1;
		total_roads -= 1;
		roads_built += 1;
	}
	else
	{
		return 0;	//no puede construir 
	}

	return 1;
}

bool Player::
buildSettlement(void)
{
	if (settlements_built < 2 && total_settlements > 3)	//se fija si está en el primer o segundo turno
	{
		total_settlements -= 1;
		settlements_built += 1;
	}
	else if (total_settlements > 0 && my_r_cards.brick >= 1 && my_r_cards.grain >= 1 && my_r_cards.lumber >= 1 && my_r_cards.wool >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias
	{
		my_r_cards.brick -= 1;
		my_r_cards.grain -= 1;
		my_r_cards.lumber -= 1;
		my_r_cards.wool -= 1;
		total_settlements -= 1;
		settlements_built += 1;
	}
	else
	{
		return 0;	//no puede construir
	}

	return 1;
}

bool Player::
buildCity(void)
{
	if (total_cities > 0 && settlements_built >= 1 && my_r_cards.ore >= 3 && my_r_cards.grain >= 2)	//se fija si hay al menos un settlement y si tiene las cartas de recurso necesarias
	{
		my_r_cards.ore -= 3;
		my_r_cards.grain -= 2;
		settlements_built -= 1;
		total_cities -= 1;
		cities_built += 1;
	}
	else
	{
		return 0;	//no puede construir
	}

	return 1;
}

/****************************************** FALTAN ESTOS **********************************************/
void moveRobber();
void domesticTrade(ResourceCards my_r_card, ResourceCards the_r_card_i_want);
void maritimeTrade();

bool Player::
buyDevelopmentCard(void)
{
	if (my_r_cards.ore >= 1 && my_r_cards.wool >= 1 && my_r_cards.grain >= 1)	//se fija si tengo las cartas de recurso necesarias para comprar una development card
	{
		my_r_cards.ore -= 1;
		my_r_cards.wool -= 1;
		my_r_cards.grain -= 1;
	}
	else
	{
		return 0;	//no puede comprar
	}

	return 1;
}

void Player::
throw_the_dices(void)
{
	unsigned int first_dice = 0, second_dice = 0;
	srand(time(NULL));	//inicializo la semilla
	first_dice = rand() % 6 + 1;	//tiro el primer dado
	second_dice = rand() % 6 + 1;	//tiro el segundo dado
	dice_number = first_dice + second_dice;
}

bool Player::
GameWon(void)
{
	if (getVictoryPoints() >= 8)
	{
		return 1;	// i won
	}
	else
	{
		return 0; // not yet
	}
}

//~Player();

