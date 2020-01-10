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
		/*timer = al_create_timer(1.0 / FPS);
		if (!timer)
		{
			error = TIMER_ERROR;
		}
		else*/
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
					//al_register_event_source(event_queue, al_get_timer_event_source(timer));	//registra los eventos del timer AHORA LO VAMOS A INICIALIZAR EN GRAPHICS!
					
					if (al_install_mouse() && al_install_keyboard() && al_init_image_addon() &&al_init_primitives_addon())	//para usar el mouse y el teclado
					{
						al_register_event_source(event_queue, al_get_mouse_event_source());	//registra los eventos del mouse
						al_register_event_source(event_queue, al_get_keyboard_event_source()); //registra los eventos del teclado
					}
					//al_start_timer(timer);
					al_init_font_addon();
					al_init_ttf_addon();
					error = NONE;
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

string Input::
inputName(void)
{
	/*esto de acá hay que modificar o no se si está bien y yo no se donde poner el archivo*/

	font = al_load_ttf_font("Files/RINGM___.ttf", 15, 0);

	if (font == NULL)
	{
		fprintf(stderr, "Could not load font'.\n");	
	}

	string name = "";
	bool exit = false;
	int i = 0;
	ALLEGRO_BITMAP* Title;
	Title = al_load_bitmap("Files/settlers_title.png");
	al_draw_scaled_rotated_bitmap(Title, al_get_bitmap_width(Title) / 2.0, al_get_bitmap_height(Title) / 2.0, WIDTH * 0.5, HEIGHT * 0.2, (0.3 * WIDTH) / 800, (0.3 * WIDTH) / 800, 0.0, NULL);

	while (exit == false)
	{
		if (i > 254)
		{
			exit = true;
		}
		else if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					name += 'A';
					i++;
					break;

				case ALLEGRO_KEY_B:
					name += 'B';
					i++;
					break;

				case ALLEGRO_KEY_C:
					name += 'C';
					i++;
					break;

				case ALLEGRO_KEY_D:
					name += 'D';
					i++;
					break;

				case ALLEGRO_KEY_E:
					name += 'E';
					i++;
					break;

				case ALLEGRO_KEY_F:
					name += 'F';
					i++;
					break;

				case ALLEGRO_KEY_G:
					name += 'G';
					i++;
					break;

				case ALLEGRO_KEY_H:
					name += 'H';
					i++;
					break;

				case ALLEGRO_KEY_I:
					name += 'I';
					i++;
					break;

				case ALLEGRO_KEY_J:
					name += 'J';
					i++;
					break;

				case ALLEGRO_KEY_K:
					name += 'K';
					i++;
					break;

				case ALLEGRO_KEY_L:
					name += 'L';
					i++;
					break;

				case ALLEGRO_KEY_M:
					name += 'M';
					i++;
					break;

				case ALLEGRO_KEY_N:
					name += 'N';
					i++;
					break;

				case ALLEGRO_KEY_O:
					name += 'O';
					i++;
					break;

				case ALLEGRO_KEY_P:
					name += 'P';
					i++;
					break;

				case ALLEGRO_KEY_Q:
					name += 'Q';
					i++;
					break;

				case ALLEGRO_KEY_R:
					name += 'R';
					i++;
					break;

				case ALLEGRO_KEY_S:
					name += 'S';
					i++;
					break;

				case ALLEGRO_KEY_T:
					name += 'T';
					i++;
					break;

				case ALLEGRO_KEY_U:
					name += 'U';
					i++;
					break;

				case ALLEGRO_KEY_V:
					name += 'V';
					i++;
					break;

				case ALLEGRO_KEY_W:
					name += 'W';
					i++;
					break;

				case ALLEGRO_KEY_X:
					name += 'X';
					i++;
					break;

				case ALLEGRO_KEY_Y:
					name += 'Y';
					i++;
					break;
				case ALLEGRO_KEY_Z:
					name += 'Z';
					i++;
					break;

				case ALLEGRO_KEY_ENTER:
					exit = true;
					break;

				case ALLEGRO_KEY_BACKSPACE:
					if (i > 0)
					{
						name.pop_back();
						i--;
					}
					break;

				default: break;
				}

			}
		}

		/*y acá hay que cambiar el primer parámetro de los al_draw_text por el tipo de font para cada uno*/

		al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH * 0.3, HEIGHT * 0.4, ALLEGRO_ALIGN_LEFT, "What's your name?");
		al_draw_filled_rectangle(WIDTH * 0.3, HEIGHT * 0.45, WIDTH * 0.7, HEIGHT * 0.55, al_map_rgb(255, 255, 255)); // esto está bien
		al_draw_rounded_rectangle(WIDTH * 0.3, HEIGHT * 0.45, WIDTH * 0.7, HEIGHT * 0.55, 10.0, 10.0, al_map_rgb(0, 0, 0), 5.0);
		al_draw_rounded_rectangle(WIDTH * 0.3, HEIGHT * 0.45, WIDTH * 0.7, HEIGHT * 0.55, 10.0, 10.0, al_map_rgb(255, 255, 255), 3.0);
		al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH * 0.33, HEIGHT * 0.48, ALLEGRO_ALIGN_LEFT, name.c_str());
		al_flip_display();
	}
	al_destroy_bitmap(Title);
	return name;
}

string Input::
inputIP(void)
{
	string ip = "";
	bool exit = false;
	unsigned int i = 0;
	
	ALLEGRO_BITMAP* Title;
	Title = al_load_bitmap("Files/settlers_title.png");
	al_draw_scaled_rotated_bitmap(Title, al_get_bitmap_width(Title) / 2.0, al_get_bitmap_height(Title) / 2.0, WIDTH * 0.5, HEIGHT * 0.2, (0.3 * WIDTH) / 800, (0.3 * WIDTH) / 800, 0.0, NULL);

	while (exit == false)
	{
		if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_KEY_DOWN && (i < 15))
			{
				switch (event.keyboard.keycode)
				{
					case ALLEGRO_KEY_0:
						ip += '0';
						i++;
						break;

					case ALLEGRO_KEY_1:
						ip += '1';
						i++;
						break;

					case ALLEGRO_KEY_2:
						ip += '2';
						i++;
						break;

					case ALLEGRO_KEY_3:
						ip += '3';
						i++;
						break;

					case ALLEGRO_KEY_4:
						ip += '4';
						i++;
						break;

					case ALLEGRO_KEY_5:
						ip += '5';
						i++;
						break;

					case ALLEGRO_KEY_6:
						ip += '6';
						i++;
						break;

					case ALLEGRO_KEY_7:
						ip += '7';
						i++;
						break;

					case ALLEGRO_KEY_8:
						ip += '8';
						i++;
						break;

					case ALLEGRO_KEY_9:
						ip += '9';
						i++;
						break;

					case ALLEGRO_KEY_L:
						ip += 'l';
						i++;
						break;

					case ALLEGRO_KEY_O:
						ip += 'o';
						i++;
						break;

					case ALLEGRO_KEY_C:
						ip += 'c';
						i++;
						break;

					case ALLEGRO_KEY_A:
						ip += 'a';
						i++;
						break;

					case ALLEGRO_KEY_H:
						ip += 'h';
						i++;
						break;

					case ALLEGRO_KEY_S:
						ip += 's';
						i++;
						break;

					case ALLEGRO_KEY_T:
						ip += 't';
						i++;
						break;

					case ALLEGRO_KEY_FULLSTOP:
						ip += '.';
						i++;
						break;

					case ALLEGRO_KEY_ENTER:
						exit = true;
						break;

					case ALLEGRO_KEY_BACKSPACE:
						if (i > 0)
						{
							ip.pop_back();
							i--;
						}
						break;
				}

			}
		}

		/*y acá hay que cambiar el primer parámetro de los al_draw_text por el tipo de font para cada uno*/

		al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH * 0.3, HEIGHT * 0.4, ALLEGRO_ALIGN_LEFT, "What's your IP?");
		al_draw_filled_rectangle(WIDTH * 0.3, HEIGHT * 0.45, WIDTH * 0.7, HEIGHT * 0.55, al_map_rgb(255, 255, 255)); // esto está bien
		al_draw_rounded_rectangle(WIDTH * 0.3, HEIGHT * 0.45, WIDTH * 0.7, HEIGHT * 0.55, 10.0, 10.0, al_map_rgb(0, 0, 0), 5.0);
		al_draw_rounded_rectangle(WIDTH * 0.3, HEIGHT * 0.45, WIDTH * 0.7, HEIGHT * 0.55, 10.0, 10.0, al_map_rgb(255, 255, 255), 3.0);
		al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH * 0.33, HEIGHT * 0.48, ALLEGRO_ALIGN_LEFT, ip.c_str());
		al_flip_display();
	}
	al_destroy_bitmap(Title);
	return ip;
}

string Input:: 
getInputName(void)
{
	return inputName();
}

string Input::
getInputIP(void)
{
	return inputIP();
}

ALLEGRO_FONT * Input::
getFont()
{
	return this->font;
}

Input::
~Input()
{
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_shutdown_image_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_font(font);
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

