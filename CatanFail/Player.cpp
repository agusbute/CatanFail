#include "Player.h"

Player::
Player(string name)
{
	setName(name);

	// setting all resource cards = 0
	r_cards.brick = 0;
	r_cards.grain = 0;
	r_cards.lumber = 0;
	r_cards.ore = 0;
	r_cards.wool = 0;

	// setting all development cards = 0
	d_cards.knight = 0;
	d_cards.largest_army = 0;
	d_cards.longest_road = 0;
	d_cards.progress = 0;
	d_cards.victory_point = 0;
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
			if (d_cards.knight >= 1)
			{
				d_cards.knight -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;
		
		case V_POINT:
			if (d_cards.victory_point >= 1)
			{
				d_cards.victory_point -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		case L_ROAD:
			if (d_cards.longest_road >= 1)
			{
				d_cards.longest_road-= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		case L_ARMY:
			if (d_cards.largest_army >= 1)
			{
				d_cards.largest_army -= 1;
			}
			else
			{
				error = NO_DCARD;
				return 0;
			}
			break;

		case PROG:
			if (d_cards.progress >= 1)
			{
				d_cards.progress -= 1;
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
	if (roads_built < 2)	//se fija si está en el primer o segundo turno
	{
		roads_built += 1;
	}
	else if (r_cards.brick >= 1 && r_cards.lumber >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias
	{
		r_cards.brick -= 1;
		r_cards.lumber -= 1;
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
	if (settlements_built < 2)	//se fija si está en el primer o segundo turno
	{
		settlements_built += 1;
	}
	else if (r_cards.brick >= 1 && r_cards.grain >= 1 && r_cards.lumber >= 1 && r_cards.wool >= 1)	//si está más avanzado el juego, se fija que tenga las cartas necesarias
	{
		r_cards.brick -= 1;
		r_cards.grain -= 1;
		r_cards.lumber -= 1;
		r_cards.wool -= 1;
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
	if (settlements_built >= 1 && r_cards.ore >= 3 && r_cards.grain >= 2)	//se fija si hay al menos un settlement y si tiene las cartas de recurso necesarias
	{
		r_cards.ore -= 3;
		r_cards.grain -= 2;
		settlements_built -= 1;
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
	if (r_cards.ore >= 1 && r_cards.wool >= 1 && r_cards.grain >= 1)	//se fija si tengo las cartas de recurso necesarias para comprar una development card
	{
		r_cards.ore -= 1;
		r_cards.wool -= 1;
		r_cards.grain -= 1;
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

