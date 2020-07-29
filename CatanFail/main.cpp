#include "Game.h"

int main(void)
{
	Player player;
	Player opponent;
	Input input;
	Board board;

	Graphics graphics(&board, &player, &opponent, &input);

	Game game(&board, &player, &opponent, &input, &graphics);
	
	game.play();
	
	return 0;
}