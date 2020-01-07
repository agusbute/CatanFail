// aparentemente esto es literalmente la interfaz gráfica, tiene que crear pantalla principal de input, tablero, botones, etc.

#include "Graphics.h"

Graphics::
Graphics(Board* board_, Player* player_, Player* opponent_, Input* input_, Button* buttons_) // probablemente despues se modifique buttons
{
	this->board = board_;
	this->player = player_;
	this->opponent = opponent_;
	this->input = input_;

	if (al_init_primitives_addon() && al_init_image_addon() && al_init_font_addon())
	{
		//setGraphics(board, player, opponent, buttons);
		al_flip_display();
	}
	else
	{
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
		al_shutdown_font_addon();
	}
}

void Graphics::
setGraphics(Board * board_, Player * player_, Player * opponent_, Button * buttons_)
{
	al_clear_to_color(al_map_rgb(255, 253, 208));
	drawBoard();
	drawTiles(board_);
	drawPlayer(player_);
	drawPlayer(opponent_);
	drawButtons(buttons_);
	al_flip_display();
}

void Graphics:: 
drawBoard(void)
{
	const float points[12] = { WIDTH * 0.35, HEIGHT * 0.15, WIDTH * 0.65, HEIGHT * 0.15, WIDTH * 0.775, HEIGHT * 0.5, WIDTH * 0.65, HEIGHT * 0.85, WIDTH * 0.35, HEIGHT * 0.85, WIDTH * 0.225, HEIGHT * 0.5 };
	al_draw_polygon(points, 6, ALLEGRO_LINE_JOIN_MITER, al_map_rgb(255,255,255), 1, 1);
}

void Graphics::
drawTiles(Board * board_)
{

}

void Graphics::
drawPlayer(Player * player_) // debería chequear si es el oponente y en base a eso muestra en el display
{
	if (player_->getType() == "player")
	{

	}
}

void Graphics::
drawButtons(Button * buttons_)
{

}

Graphics::
~Graphics()
{
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
}
