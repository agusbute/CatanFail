// aparentemente esto es literalmente la interfaz gráfica, tiene que crear pantalla principal de input, tablero, botones, etc.

#include "Graphics.h"

Graphics::
Graphics(Board * board_, Player * player_, Player * opponent_ , Button * buttons_) // probablemente despues se modifique buttons
{
	this->board = board_;
	this->player = player_;
	this->opponent = opponent_;
	this->buttons = buttons_;

	if (al_init_primitives_addon)
	{
		setGraphics(board, player, opponent, buttons);
	}
	else
	{
		al_shutdown_primitives_addon;
	}
}

void Graphics::
setGraphics(Board * board_, Player * player_, Player * opponent_, Button * buttons_)
{
	drawBoard(board_);
	drawTiles(board_);
	drawPlayer(player_);
	drawPlayer(opponent_);
	drawButtons(buttons_);
}

void Graphics:: 
drawBoard(Board * board_)
{
	const float points[12] = { WIDTH*0.3, HEIGHT*0.1, WIDTH*0.8, HEIGHT*0.1, WIDTH*0.3, HEIGHT*0.9, WIDTH*0.8, HEIGHT*0.9, WIDTH*0.25, HEIGHT*0.5, WIDTH*0.25, HEIGHT*0.5};
	al_draw_polygon(points, 6, ALLEGRO_LINE_JOIN_MITER, al_map_rgb(255,255,255), 1, 1);
}

void Graphics::
drawTiles(Board * board_)
{

}

void Graphics::
drawPlayer(Player * player_) // debería chequear si es el oponente y en base a eso muestra en el display
{

}

void Graphics::
drawButtons(Button * buttons_)
{

}

Graphics::
~Graphics()
{
	al_shutdown_primitives_addon;
}
