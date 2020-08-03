#include "Game.h"

int main(void)
{
	Player player;
	Player opponent;
	Input input;
	Board board;
	Network network;

	Graphics graphics(&board, &player, &opponent, &input);

	Game game(&board, &player, &opponent, &input, &graphics, &network);

	game.play();
	
	return 0;
}