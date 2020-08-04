#pragma once

#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <windows.h>

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


#define BRICK1 0
#define GRAIN1 1
#define ORE1 2
#define LUMBER1 3
#define WOOL1 4
#define DESERT1 5

#define NUM2 0
#define NUM3 1
#define NUM4 2
#define NUM5 3
#define NUM6 4
#define NUM8 5
#define NUM9 6
#define NUM10 7
#define NUM11 8
#define NUM12 9
#define EMPTY 10
#define ROBBER 11

#define TOKENS 12

#define FRAME_WIDTH 810
#define FRAME_HEIGHT 240

#define HEX_WIDTH 221
#define HEX_HEIGHT 257

#define TOTALDICE 6

#define PLAYER 0
#define OPPONENT 1


typedef enum bmp_flag { BUILD, BUTTONS, ROADS, NODES };

typedef struct
{
	int x;
	int y = 1000;
}disp_coord;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}rgb_click;

class Graphics
{
	public:

		Graphics(Board * board_, Player * player_, Player * opponent_, Input * input_);
		~Graphics();
		
		void setfirstGraphics(); // display que pide nombre e ip
		void setGraphicsGame(); // display con el tablero y todo eso
		
		//animaciones de botones
		void tradeClicked();
		void passClicked();
		void buildClicked();
		void exitClicked();

		rgb_click getClickRGB(mouse_coords click_);

		void setClickBMP(bmp_flag flag);

		void updateDisplay();
	
	private:
		
		Player * player;
		Player * opponent;
		Board * board;
		Input * input;

		ALLEGRO_BITMAP* Color_Nodes;
		ALLEGRO_BITMAP* Color_Roads;
		ALLEGRO_BITMAP* Color_Buttons1;
		ALLEGRO_BITMAP* Build_Buttons;
		ALLEGRO_BITMAP* Click_BMP;

		ALLEGRO_BITMAP** Hexes;
		ALLEGRO_BITMAP** Frames;
		ALLEGRO_BITMAP** Tokens;

		ALLEGRO_BITMAP** Dices;
		ALLEGRO_BITMAP** ResourceCards;

		ALLEGRO_BITMAP** Houses;
		ALLEGRO_BITMAP** Settlements;
		ALLEGRO_BITMAP** Roads;

		ALLEGRO_BITMAP* ButtonMain;
		ALLEGRO_BITMAP* ButtonClick;

		disp_coord player_roads[TOTAL_ROADS];
		disp_coord opponent_roads[TOTAL_ROADS];
		disp_coord player_settlements[TOTAL_SETTLEMENTS];
		disp_coord opponent_settlement[TOTAL_SETTLEMENTS];
		disp_coord player_cities[TOTAL_CITIES];
		disp_coord opponent_cities[TOTAL_CITIES];

		void drawBoard(void);
		void drawBoardComponents();
		void drawButtons(); // esto se redibuja para efectos
		void drawBuildButtons();
		void drawPlayer();
		void drawOpponent();
		void drawCards(); //dibuja las cartas con contador (se usa solo para el player)
		void boardComponentsCount(Player* player_); // casas y caminos con contadores (no sobre el tablero)
		void drawBoardComps(); //lo que va sobre el tablero (casas y  caminos)
		void drawRobber();
		void drawDices(dices_t dices);
		void drawDices(unsigned int dice1, unsigned int dice2);
		void showMessage(); 
		
		string getPlayerName();
};