#pragma once

#include "Input.h"

Input::
Input()
{
	if (!al_init())	//inicializo allegro
	{
		error = INIT_ERROR;
	}
	else
	{
		timer = al_create_timer(1.0 / FPS);
		if (!timer)
		{
			error = TIMER_ERROR;
		}
		else
		{
			display = al_create_display(WIDTH, HEIGHT);	//creo el display
			if (!display)	//testeo el display
			{
				error = DIS_ERROR;
			}
			else
			{
				event_queue = al_create_event_queue();	//creo la cola de eventos
				if (!event_queue)
				{
					error = EV_Q_ERROR;
				}
				else
				{
					al_register_event_source(event_queue, al_get_display_event_source(display));	//registra los eventos del display
					al_register_event_source(event_queue, al_get_timer_event_source(timer));	//registra los eventos del timer
					
					if(al_install_mouse() && al_install_keyboard())	//para usar el mouse y el teclado
					{
						al_register_event_source(event_queue, al_get_mouse_event_source());	//registra los eventos del mouse
						al_register_event_source(event_queue, al_get_keyboard_event_source()); //registra los eventos del teclado
					}
					al_start_timer(timer);
					error = NONE;
				}
			}
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
		if (event.mouse.button & MOUSE_LEFT_BUTTON)	//si hice click izquierdo
		{
			mouse_position.pos_x = event.mouse.x;
			mouse_position.pos_y = event.mouse.y;
			//acá llama a un metodo de graphics que según la posición del mouse se fija si ahí hay un botón y cual es
		}
		break;

		case ALLEGRO_EVENT_TIMER:
		redraw = true;
		break;

		default:break;
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
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

/*

bool Input.exit_game = false;
bool Input.redraw = false;

while(input->exitGame() != true)
{
	if(all_get_next_event(event_queue, &event))
	{
			//llamo al 0800 dispatcher
	}

	if(redraw && al_is_event_queue_empty(event_queue) && is_empty_network_evqueue()) //redraw es un bool que es true cuando hay un evento del timer
	{
		al_flip_display();	//refresh del display
		redraw = false;
	}
}


*/

