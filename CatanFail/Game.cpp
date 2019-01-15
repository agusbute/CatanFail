#include "Game.h"

void Game::
createDevelopmentCards(void)
{
	char knight_counter = 0, progress_counter = 0, victory_counter = 0;

	srand(time(NULL));
	char type = rand() % 3 + 1; // 1 = knight, 2 = progress, 3 = victory

	char i = 0; //contador
	while (i < TOTAL_D_CARDS)
	{
		if (type == 1 && knight_counter < 14)
		{
			development_cards.push(DevelopmentCard(KNIGHT));
			knight_counter++;
			type = rand() % 3 + 1;
		}
		else if (type == 2 && progress_counter < 6)
		{
			development_cards.push(DevelopmentCard(PROG));
			progress_counter++;
			type = rand() % 3 + 1;
		}
		else if (type == 3 && victory_counter < 5)
		{
			development_cards.push(DevelopmentCard(V_POINT));
			victory_counter++;
			type = rand() % 3 + 1;
		}
	}
}