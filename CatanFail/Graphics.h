#pragma once

#include <iostream>
#include <math.h>
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

# define M_PI           3.14159265358979323846  /* pi */

#define ToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

#define ANY_PORT 0
#define BRICK_PORT 1
#define GRAIN_PORT 2
#define STONE_PORT 3
#define WOOD_PORT 4
#define WOOL_PORT 5

#define DESERT1 0
#define BRICK1 1
#define GRAIN1 2
#define ORE1 3
#define LUMBER1 4
#define WOOL1 5

#define FRAME_WIDTH 810
#define FRAME_HEIGHT 240

#define HEX_WIDTH 221
#define HEX_HEIGHT 257

class Graphics
{
	public:

		Graphics(Board * board_, Player * player_, Player * opponent_, Input * input_, Button * buttons_);
		~Graphics();
		
		void setfirstGraphics(); // display que pide nombre e ip
		void setGraphicsGame(); // display con el tablero y todo eso
		
		void updateDisplay();
	
	private:
		
		Player * player;
		Player * opponent;
		Board * board;
		Input * input;
		Button * buttons;

		ALLEGRO_BITMAP** Hexes;
		ALLEGRO_BITMAP** Frames;

		void drawBoard(void); // borde						\__ estos dos no se deber�an
		void drawTiles(Board * board_); // interior (fijo)	/   redibujar porque no cambian en toda la partida
		void drawBoardComponents();
		void drawButtons(Button* buttons_); // esto se redibuja para efectos
		void drawPlayer(Player * player_);
		void drawCards(Player* player_); //dibuja las cartas con contador (se usa solo para el player)
		void boardComponentsCount(Player* player_); // casas y caminos con contadores (no sobre el tablero)
		void drawBoardComps(); //lo que va sobre el tablero (casas y  caminos)
		void drawRobber();
		void drawDices();
		void showMessage(); 

		string getPlayerName();
};