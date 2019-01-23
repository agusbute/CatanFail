#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <iostream>

// medidas del display
#define WIDTH 640
#define HEIGHT 480
#define MOUSE_LEFT_BOTTON 1

enum AL_ERROR { INIT_ERROR, DIS_ERROR, NONE};

typedef struct
{
	int pos_x;
	int pos_y;
}mouse_coords;

class Input
{
	public:
		Input();
		void evDispatcher(void);
		bool exitGame(void);
		~Input();

	private:
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_DISPLAY * display;
		ALLEGRO_EVENT event;
		
		mouse_coords mouse_position;
		
		bool exit_game;
		AL_ERROR error;
};
