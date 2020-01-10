// aparentemente esto es literalmente la interfaz gráfica, tiene que crear pantalla principal de input, tablero, botones, etc.

#include "Graphics.h"

Graphics::
Graphics(Board* board_, Player* player_, Player* opponent_, Input* input_, Button* buttons_) // probablemente despues se modifique buttons
{
	this->board = board_;
	this->player = player_;
	this->opponent = opponent_;
	this->input = input_;
	this->buttons = buttons_;

	this->Hexes = new ALLEGRO_BITMAP * [TOTAL_RESOURCES + 1];
	this->Frames = new ALLEGRO_BITMAP * [SEA_FRAME_TILES];

	if (al_init_primitives_addon() && al_init_image_addon())
	{
		setfirstGraphics();
		
		Hexes[DESERT1] = al_load_bitmap("Files/Hexes/DESERT.png");
		Hexes[BRICK1] = al_load_bitmap("Files/Hexes/BRICK.png");
		Hexes[GRAIN1] = al_load_bitmap("Files/Hexes/GRAIN.png");
		Hexes[LUMBER1] = al_load_bitmap("Files/Hexes/LUMBER.png");
		Hexes[ORE1] = al_load_bitmap("Files/Hexes/ORE.png");
		Hexes[WOOL1] = al_load_bitmap("Files/Hexes/WOOL.png");

		Frames[ANY_PORT] = al_load_bitmap("Files/SeaFrames/ANY_PORT.png");
		Frames[BRICK_PORT] = al_load_bitmap("Files/SeaFrames/BRICK_PORT.png");
		Frames[WOOD_PORT] = al_load_bitmap("Files/SeaFrames/WOOD_PORT.png");
		Frames[WOOL_PORT] = al_load_bitmap("Files/SeaFrames/WOOL_PORT.png");
		Frames[STONE_PORT] = al_load_bitmap("Files/SeaFrames/STONE_PORT.png");
		Frames[GRAIN_PORT] = al_load_bitmap("Files/SeaFrames/GRAIN_PORT.png");
	}
	else
	{
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
		al_shutdown_font_addon();
	}
}

void Graphics::
setfirstGraphics()	// display de inicio - nombre e ip
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	player->setName((input->getInputName())); // ya setea en player

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	input->getInputIP(); // consultar con bute

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
}

void Graphics::
setGraphicsGame()
{
	drawBoard();
	drawTiles(board);
	drawPlayer(player);
	drawPlayer(opponent);
	drawButtons(buttons);
	al_flip_display();
}

void Graphics::
drawBoard(void)
{
	const float points[12] = { WIDTH * 0.35, HEIGHT * 0.15, WIDTH * 0.65, HEIGHT * 0.15, WIDTH * 0.775, HEIGHT * 0.5, WIDTH * 0.65, HEIGHT * 0.85, WIDTH * 0.35, HEIGHT * 0.85, WIDTH * 0.225, HEIGHT * 0.5 };
	al_draw_polygon(points, 6, ALLEGRO_LINE_JOIN_MITER, al_map_rgb(255, 255, 255), 1, 1);

	for (int i = 0; i < SEA_FRAME_TILES; i++)
	{
		float middle_x = al_get_bitmap_width(Frames[i]) / 2.0;
		float middle_y = al_get_bitmap_height(Frames[i]) / 2.0;

		float x_scale = (0.3*WIDTH)/ al_get_bitmap_width(Frames[i]);
		float y_scale = x_scale;
		
		float angle = ToRadians(((i * 60.0) + 180.0));

		float dx = 0, dy = 0;
		//depende de que posicion sea es donde se dibuja
		switch (board->all_the_sea_frames[i].getPositionInMap())
		{
			case '0':
			{
				dx = 0.45 * WIDTH; //OK!
				dy = 0.15 * HEIGHT; //OK!
			}break;
			case '1':
			{
				dx = 0.686 * WIDTH;
				dy = 0.263 * HEIGHT;
			}break;
			case '2':
			{
				dx = 0.736 * WIDTH;
				dy = 0.619 * HEIGHT;
			}break;
			case '3':
			{
				dx = 0.549 * WIDTH; //OK!
				dy = 0.8586 * HEIGHT; //OK!
			}break;
			case '4':
			{
				dx = 0.312 * WIDTH;
				dy = 0.7429 * HEIGHT;
			}break;
			case '5':
			{
				dx = 0.265 * WIDTH;
				dy = 0.39 * HEIGHT;
			}break;
			default: break;
		}

		int img = 0;
		//el puerto define que imagen es
		switch (board->all_the_sea_frames[i].getPorts().port1.port)
		{
			case ports::ANY:
			{
				img = ANY_PORT;
			}break;
			case ports::BRICK:
			{
				img = BRICK_PORT;
			}break;
			case ports::GRAIN:
			{
				img = GRAIN_PORT;
			}break;
			case ports::LUMBER:
			{
				img = WOOD_PORT;
			}break;
			case ports::ORE:
			{
				img = STONE_PORT;
			}break;
			case ports::WOOL:
			{
				img = WOOL_PORT;
			}break;
			default:
			{

			}break;
		}

		al_draw_scaled_rotated_bitmap(Frames[img], middle_x, middle_y, dx, dy, x_scale, y_scale, angle, NULL);
		
	}

	for (int i = 0; i < TERRAIN_HEXES; i++)
	{
		float middle_x = HEX_WIDTH / 2.0;
		float middle_y = HEX_HEIGHT / 2.0;

		float x_scale = 102.5 / HEX_WIDTH;
		float y_scale = 112.5 / HEX_HEIGHT;

		float dx = 0, dy = 0;
		//depende de que posicion sea es donde se dibuja
		switch (board->all_the_hexes[i].getPositionInMap())
		{
		case 'A':
		{
			dx = 0.5 * WIDTH - 103.0;
			dy = 0.15 * HEIGHT + 0.295 * FRAME_HEIGHT;
		}break;
		case 'B':
		{
			dx = 0.5 * WIDTH;
			dy = 0.15 * HEIGHT + 0.295 * FRAME_HEIGHT;
		}break;
		case 'C':
		{
			dx = 0.5 * WIDTH + 103.0;
			dy = 0.15 * HEIGHT + 0.295 * FRAME_HEIGHT;
		}break;
		case 'D':
		{
			dx = ((0.5 * WIDTH - 2.0 * 102.5) + (0.5 * WIDTH - 103.0)) / 2.0;
			dy = ((0.15 * HEIGHT + 0.295 * FRAME_HEIGHT) + (0.5 * HEIGHT + 3.0)) / 2.0;
		}break;
		case 'E':
		{
			dx = ((0.5 * WIDTH - 103.0) + 0.5 * WIDTH) / 2.0;
			dy = ((0.15 * HEIGHT + 0.295 * FRAME_HEIGHT) + (0.5 * HEIGHT + 3.0)) / 2.0;
		}break;
		case 'F':
		{
			dx = (0.5 * WIDTH + (0.5 * WIDTH + 103.0)) / 2.0;
			dy = ((0.15 * HEIGHT + 0.295 * FRAME_HEIGHT) + (0.5 * HEIGHT + 3.0)) / 2.0;
		}break;
		case 'G':
		{
			dx = ((0.5 * WIDTH + 103.0) + (0.5 * WIDTH + 2.0 * 102.5)) / 2.0;
			dy = ((0.15 * HEIGHT + 0.295 * FRAME_HEIGHT) + (0.5 * HEIGHT + 3.0)) / 2.0;
		}break;
		case 'H':
		{
			dx = 0.5 * WIDTH - 2.0 * 102.5;
			dy = 0.5 * HEIGHT + 3.0;
		}break;
		case 'I':
		{
			dx = 0.5 * WIDTH - 103.0;
			dy = 0.5 * HEIGHT + 3.0;
		}break;
		case 'J':
		{
			dx = 0.5 * WIDTH;
			dy = 0.5 * HEIGHT + 3.0;
		}break;
		case 'K':
		{
			dx = 0.5 * WIDTH + 103.0;
			dy = 0.5 * HEIGHT + 3.0;
		}break;
		case 'L':
		{
			dx = 0.5 * WIDTH + 2.0 * 102.5;
			dy = 0.5 * HEIGHT + 3.0;
		}break;
		case 'M':
		{
			dx = ((0.5 * WIDTH - 2.0 * 102.5) + (0.5 * WIDTH - 103.0)) / 2.0;
			dy = ((0.5 * HEIGHT + 3.0) + (0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT))) / 2.0;
		}break;
		case 'N':
		{
			dx = ((0.5 * WIDTH - 103.0) + 0.5 * WIDTH) / 2.0;
			dy = ((0.5 * HEIGHT + 3.0) + (0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT))) / 2.0;
		}break;
		case 'O':
		{
			dx = (0.5 * WIDTH + (0.5 * WIDTH + 103.0)) / 2.0;
			dy = ((0.5 * HEIGHT + 3.0) + (0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT))) / 2.0;
		}break;
		case 'P':
		{
			dx = ((0.5 * WIDTH + 103.0) + (0.5 * WIDTH + 2.0 * 102.5)) / 2.0;
			dy = ((0.5 * HEIGHT + 3.0) + (0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT))) / 2.0;
		}break;
		case 'Q':
		{
			dx = 0.5 * WIDTH - 103.0;
			dy = 0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT);
		}break;
		case 'R':
		{
			dx = 0.5 * WIDTH;
			dy = 0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT);
		}break;
		case 'S':
		{
			dx = 0.5 * WIDTH + 103.0;
			dy = 0.8586 * HEIGHT - 1 * (0.295 * FRAME_HEIGHT);
		}break;
		default: break;
		}

		int img = 0;
		//el recurso define que imagen es
		switch (board->all_the_hexes[i].getResource())
		{
		case DESERT:
		{
			img = DESERT1;
		}break;
		case ORE:
		{
			img = ORE1;
		}break;
		case GRAIN:
		{
			img = GRAIN1;
		}break;
		case LUMBER:
		{
			img = LUMBER1;
		}break;
		case WOOL:
		{
			img = WOOL1;
		}break;
		case BRICK:
		{
			img = BRICK1;
		}break;
		default:
		{

		}break;
		}

		al_draw_scaled_rotated_bitmap(Hexes[img], middle_x, middle_y, dx, dy, x_scale, y_scale, 0.0, NULL);

		al_draw_circle(dx, dy, 15, al_map_rgb(0, 0, 0), 3.0);
		al_draw_filled_circle(dx, dy, 15, al_map_rgb(255, 253, 208));
		string number = "";
		number += to_string(board->all_the_hexes[i].getToken());
		al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), dx - 5.0, dy - 8.0, ALLEGRO_ALIGN_LEFT, number.c_str());
		al_flip_display();
	}
}

void Graphics::
drawTiles(Board* board_)
{

}

void Graphics::
drawPlayer(Player* player_) // debería chequear si es el oponente y en base a eso muestra en el display
{
	if (player_->getType() == "player")
	{

	}
}

void Graphics::
drawButtons(Button* buttons_)
{

}

Graphics::
~Graphics()
{
	delete[] this->Hexes;
	delete[] this->Frames;
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
}
