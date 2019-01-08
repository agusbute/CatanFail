#include "Player.h"

Player::
Player(string name, int v_points)
{
	setName(name);
	setVictoryPoints(v_points, EQUAL);
}

void Player::
setName(string name)
{
	this->name = name;
}

int Player::
getVictoryPoints(void)
{
	return this->victory_points;
}

bool Player::
setVictoryPoints(int v_points, Actions action)
{
	switch (action)
	{
		case ADD:
			this->victory_points += v_points;
			break;

		case SUBTRACT:
			this->victory_points -= v_points;	// ¿puedo tener victory points negativos?
			break;

		case EQUAL:
			this->victory_points = v_points;
			break;

		default: 
			return 1;
			break;
	}

	return 0;
}

int Player:: 
getRoadsBuilt(void)
{
	return this->roads_built;
}

int Player::
getSettlementsBuilt(void)
{
	return this->settlements_built;
}

int Player::
getCitiesBuilt(void)
{
	return this->cities_built;
}

// y para esto me faltan hacer las listas ugh 
int Player::
getDevelopmentCard( DevelopmentCards d_card)
{

}

int Player::
getResourceCard(ResourceCards r_card)
{

}

// todas estas necesitan los métodos de validación bool canBuild...Here( coords )
bool buildRoad();
bool buildSettlement();
bool buildCity();

// tambien las validaciones
void moveRobber();
void domesticTrade(ResourceCards my_r_card, ResourceCards the_r_card_i_want);
void maritimeTrade();

bool Player::
GameWon(void)
{
	if (getVictoryPoints() >= 8)
	{
		return 0;	// i won
	}
	else
	{
		return 1; // not yet
	}
}

void Player::
throw_the_dices(void)
{
	int first_dice = 0, second_dice = 0;
	srand(time(NULL));	//inicializo la semilla
	first_dice = rand() % 6 + 1;	//tiro el primer dado
	second_dice = rand() % 6 + 1;	//tiro el segundo dado
	dice_number = first_dice + second_dice;
}

//~Player();

