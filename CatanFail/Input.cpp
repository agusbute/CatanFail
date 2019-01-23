#pragma once

#include "Input.h"

Input::
Input()
{
	if (al_init())	//inicializo allegro
	{
		error = INIT_ERROR;
	}
	else
	{
		display = al_create_display(WIDTH,HEIGHT);	//creo el display
		if (!display)	//testeo el display
		{
			error = DIS_ERROR;
		}
		else
		{
			event_queue = al_create_event_queue();	//creo la cola de eventos
			al_register_event_source(event_queue, al_get_display_event_source(display));	//registra los eventos del display
			al_install_mouse();	//para usar el mouse
			al_register_event_source(event_queue, al_get_mouse_event_source());	//registra los eventos del mouse
			error = NONE;
		}
	}
}

void Input::
evDispatcher(void)
{
	switch (event.type)
	{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			exit_game = true;
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (event.mouse.button & MOUSE_LEFT_BOTTON)	//si hice click izquierdo
			{
				mouse_position.pos_x = event.mouse.x;
				mouse_position.pos_y = event.mouse.y;
				//acá llama a un metodo de graphics que según la posición del mouse se fija si ahí hay un botón y cual es
			}
			break;
	}
}

bool Input::
exitGame(void)
{
	return this->exit_game;
}

Input::
~Input()
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}

/*

bool exit_game = false;

while(input->exitGame() != true)
{
	all_wait_for_event(event_queue, &event);
	//llamo al dispatcher que hasta ahora solamente tiene eventos del mouse
	//y hago cosas
	al_flip_display();	//refresh del display
}


*/