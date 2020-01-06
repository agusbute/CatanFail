#pragma once

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>

#include "Board.h"
#include "Player.h"
#include "Input.h"
#include "Button.h"

class Graphics
{
	public:
		
		Graphics(Board * board_, Player * player_, Player * opponent_, Button * buttons_);
		~Graphics();
		
		void setGraphics(Board * board_, Player * player_, Player * opponent_, Button * buttons_);
		
		void updateDisplay();
	
	private:
		
		Player * player;
		Player * opponent;
		Board * board;
		Input * input;
		Button * buttons; // esto puede que cambie

		void drawBoard(Board * board_); // borde		\__ estos dos no se deberían
		void drawTiles(Board * board_); // interior		/   redibujar porque no cambian en toda la partida
		void drawPlayer(Player * player_);
		void drawButtons(Button * buttons_); // esto se redibuja para efectos
		// drawDices
		// showMsg
		// drawRobber
		// drawBoardComp (casas/caminos)

		string getPlayerName();
};