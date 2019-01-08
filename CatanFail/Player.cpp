#include "Player.h"

Player::
Player(string name_, int v_points, Player* player)
{
	setName(name_, player);
}

void Player::
setName(string name, Player* player)
{
	player->name = name;
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

