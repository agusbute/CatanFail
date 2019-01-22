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

class Graphics
{
	public:
		
		Graphics();
		~Graphics();
		
		void setGraphics(Board * board_, Player * player_, Player * opponent_);
		
		string getPlayerName();
		
		void updateDisplay();
	
	private:
		
		Player * player;
		Player * opponent;
		Board * board;
		Input * input;

};