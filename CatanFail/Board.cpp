#include "Board.h"

int Board::
throw_the_dices(void)
{
	int first_dice = 0, second_dice = 0;
	srand(time(NULL));	//inicializo la semilla
	first_dice = rand() % 6 + 1;	//tiro el primer dado
	second_dice = rand() % 6 + 1;	//tiro el segundo dado
	return (first_dice + second_dice);	//devuelvo el número que obtuve
}