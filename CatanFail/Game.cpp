#include "Game.h"

void Game::
createDevelopmentCards(void)
{
	char knight_counter = 0, road_b_counter = 0, victory_counter = 0, monopoly_counter = 0, year_of_p_counter = 0;

	srand(time(NULL));
	char type = rand() % 5 + 1; // 1 = knight, 2 = monopoly, 3 = victory, 4 = road building, 5 = year of plenty

	char i = 0; //contador
	while (i < TOTAL_D_CARDS)
	{
		if (type == 1 && knight_counter < TOTAL_KNIGHT_CARDS)
		{
			development_cards.push(DevelopmentCard(KNIGHT));
			knight_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 2 && monopoly_counter < TOTAL_MONO_CARDS)
		{
			development_cards.push(DevelopmentCard(MONO));
			monopoly_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 3 && victory_counter < TOTAL_V_POINT_CARDS)
		{
			development_cards.push(DevelopmentCard(V_POINT));
			victory_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 4 && road_b_counter < TOTAL_R_BUILDING_CARDS)
		{
			development_cards.push(DevelopmentCard(R_BUILDING));
			road_b_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 5 && year_of_p_counter < TOTAL_YEAR_OF_P_CARDS)
		{
			development_cards.push(DevelopmentCard(YEAR_OF_P));
			year_of_p_counter++;
			type = rand() % 5 + 1;
		}
	}
}

void Game::
checkRoad(char x, char y)
{

}