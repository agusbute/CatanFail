#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <iostream>

#include "Button.h"

using namespace std;

// medidas del display
#define WIDTH 1000
#define HEIGHT 600
#define MOUSE_LEFT_BUTTON 1
#define FPS 20

enum AL_ERROR { INIT_ERROR, DIS_ERROR, TIMER_ERROR, EV_Q_ERROR, NONE };

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

	string getInputName(void);
	string getInputIP(void);

	mouse_coords getMouseClick(void);

	ALLEGRO_FONT* getFont();

	~Input();


private:

	Button* Buttons[VISIBLE_BUTTONS + INVISIBLE_BUTTONS];

	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;

	ALLEGRO_FONT* font;

	mouse_coords mouse_position;

	bool exit_game;
	bool redraw;
	AL_ERROR error;

	string inputName(void); // Player debería llamar a esta función para obtener el nombre del jugador
	string inputIP(void);

	void setVisibleButtons(void);
};
