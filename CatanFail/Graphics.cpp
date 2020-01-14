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
	this->Tokens = new ALLEGRO_BITMAP * [TOKENS];

	this->Dices = new ALLEGRO_BITMAP * [TOTALDICE];

	this->ResourceCards = new ALLEGRO_BITMAP * [TOTAL_RESOURCES];

	this->Houses = new ALLEGRO_BITMAP * [2];
	this->Settlements = new ALLEGRO_BITMAP* [2];
	this->Roads = new ALLEGRO_BITMAP * [2];


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

	Tokens[NUM2] = al_load_bitmap("Files/Tokens/NUM2.png");
	Tokens[NUM3] = al_load_bitmap("Files/Tokens/NUM3.png");
	Tokens[NUM4] = al_load_bitmap("Files/Tokens/NUM4.png");
	Tokens[NUM5] = al_load_bitmap("Files/Tokens/NUM5.png");
	Tokens[NUM6] = al_load_bitmap("Files/Tokens/NUM6.png");
	Tokens[NUM8] = al_load_bitmap("Files/Tokens/NUM8.png");
	Tokens[NUM9] = al_load_bitmap("Files/Tokens/NUM9.png");
	Tokens[NUM10] = al_load_bitmap("Files/Tokens/NUM10.png");
	Tokens[NUM11] = al_load_bitmap("Files/Tokens/NUM11.png");
	Tokens[NUM12] = al_load_bitmap("Files/Tokens/NUM12.png");
	Tokens[EMPTY] = al_load_bitmap("Files/Tokens/EMPTY.png");
	Tokens[ROBBER] = al_load_bitmap("Files/Tokens/Robber.png");

	Dices[0] = al_load_bitmap("Files/Dices/Dice1.png");
	Dices[1] = al_load_bitmap("Files/Dices/Dice2.png");
	Dices[2] = al_load_bitmap("Files/Dices/Dice3.png");
	Dices[3] = al_load_bitmap("Files/Dices/Dice4.png");
	Dices[4] = al_load_bitmap("Files/Dices/Dice5.png");
	Dices[5] = al_load_bitmap("Files/Dices/Dice6.png");

	ResourceCards[BRICK1] = al_load_bitmap("Files/Cards/BRICK_CARD.png");
	ResourceCards[GRAIN1] = al_load_bitmap("Files/Cards/GRAIN_CARD.png");
	ResourceCards[WOOL1] = al_load_bitmap("Files/Cards/WOOL_CARD.png");
	ResourceCards[LUMBER1] = al_load_bitmap("Files/Cards/LUMBER_CARD.png");
	ResourceCards[ORE1] = al_load_bitmap("Files/Cards/ORE_CARD.png");

	Houses[PLAYER] = al_load_bitmap("Files/BoardPieces/House1.png");
	Houses[OPPONENT] = al_load_bitmap("Files/BoardPieces/House2.png");
	Settlements[PLAYER] = al_load_bitmap("Files/BoardPieces/Settlement1.png");
	Settlements[OPPONENT] = al_load_bitmap("Files/BoardPieces/Settlement2.png");
	Roads[PLAYER] = al_load_bitmap("Files/BoardPieces/Road1.png");
	Roads[OPPONENT] = al_load_bitmap("Files/BoardPieces/Road2.png");

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

	drawPlayer();
	drawOpponent();
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
		
		int img2 = 0;
		//el token define el numero que tiene arriba
		switch (board->all_the_hexes[i].getToken())
		{
			case 2:
			{
				img2 = NUM2;
			}break;
			case 3:
			{
				img2 = NUM3;
			}break;
			case 4:
			{
				img2 = NUM4;
			}break;
			case 5:
			{
				img2 = NUM5;
			}break;
			case 6:
			{
				img2 = NUM6;
			}break;
			case 8:
			{
				img2 = NUM8;
			}break;
			case 9:
			{
				img2 = NUM9;
			}break;
			case 10:
			{
				img2 = NUM10;
			}break;
			case 11:
			{
				img2 = NUM11;
			}break;
			case 12:
			{
				img2 = NUM12;
			}break;
			default: 
			{
				img2 = EMPTY;
			}break;
		}
		
		al_draw_scaled_rotated_bitmap(Tokens[img2], al_get_bitmap_width(Tokens[img2]) / 2.0, al_get_bitmap_height(Tokens[img2]) / 2.0, dx, dy, 1.0 / 4.0, 1.0 / 4.0, 0.0, NULL);

		if (board->all_the_hexes[i].hasRobber())
		{
			al_draw_scaled_rotated_bitmap(Tokens[ROBBER], al_get_bitmap_width(Tokens[img2]) / 2.0, al_get_bitmap_height(Tokens[img2]) / 2.0, dx, dy, 1.0 / 16.885, 1.0 / 16.885, 0.0, NULL);
		}

		al_flip_display();
	}
}

void Graphics::
drawPlayer()
{
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.05 * WIDTH, 0.05 * HEIGHT, ALLEGRO_ALIGN_LEFT, player->getName().c_str());
	drawCards();
	
	float cx_road = al_get_bitmap_width(Roads[PLAYER]) / 2.0;
	float cy_road = al_get_bitmap_height(Roads[PLAYER]) / 2.0;

	float cx_city = al_get_bitmap_width(Settlements[PLAYER]) / 2.0;
	float cy_city = al_get_bitmap_height(Settlements[PLAYER]) / 2.0;

	float cx_settlement = al_get_bitmap_width(Houses[PLAYER]) / 2.0;
	float cy_settlement = al_get_bitmap_height(Houses[PLAYER]) / 2.0;

	al_draw_scaled_rotated_bitmap(Roads[PLAYER], cx_road, cy_road, 0.06 * WIDTH, 0.925 * HEIGHT, 0.15, 0.15, 0.0, NULL);
	al_draw_filled_circle(0.06 * WIDTH, 0.86 * HEIGHT, 10, al_map_rgb(255, 243, 154));
	al_draw_circle(0.06 * WIDTH, 0.86 * HEIGHT, 10, al_map_rgb(0, 0, 0), 3);
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.06 * WIDTH - 5.0, 0.86 * HEIGHT - 9.0, ALLEGRO_ALIGN_LEFT, to_string(TOTAL_ROADS - player->getRoadsBuilt()).c_str());

	al_draw_scaled_rotated_bitmap(Settlements[PLAYER], cx_city, cy_city, 0.06 * WIDTH + 0.5 * (cx_settlement + cx_city), 0.925 * HEIGHT, 0.15, 0.15, 0.0, NULL);
	al_draw_filled_circle(0.06 * WIDTH + 0.5 * (cx_settlement + cx_city), 0.86 * HEIGHT, 10, al_map_rgb(255, 243, 154));
	al_draw_circle(0.06 * WIDTH + 0.5 * (cx_settlement + cx_city), 0.86 * HEIGHT, 10, al_map_rgb(0, 0, 0), 3);
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.06 * WIDTH + 0.5 * (cx_settlement + cx_city) - 5.0, 0.86 * HEIGHT - 9.0, ALLEGRO_ALIGN_LEFT, to_string(TOTAL_CITIES - player->getCitiesBuilt()).c_str());

	al_draw_scaled_rotated_bitmap(Houses[PLAYER], cx_settlement, cy_settlement, 0.06 * WIDTH + cx_settlement * 0.5, 0.925 * HEIGHT, 0.15, 0.15, 0.0, NULL);
	al_draw_filled_circle(0.06 * WIDTH + cx_settlement * 0.5, 0.86 * HEIGHT, 10, al_map_rgb(255, 243, 154));
	al_draw_circle(0.06 * WIDTH + cx_settlement * 0.5, 0.86 * HEIGHT, 10, al_map_rgb(0, 0, 0), 3);
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.06 * WIDTH + cx_settlement * 0.5 - 5.0, 0.86 * HEIGHT - 9.0, ALLEGRO_ALIGN_LEFT, to_string(TOTAL_SETTLEMENTS - player->getSettlementsBuilt()).c_str());
}

void Graphics::
drawOpponent()
{
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.775 * WIDTH, 0.75 * HEIGHT, ALLEGRO_ALIGN_LEFT, opponent->getName().c_str());

	float cx_road = al_get_bitmap_width(Roads[OPPONENT]) / 2.0;
	float cy_road = al_get_bitmap_height(Roads[OPPONENT]) / 2.0;

	float cx_city = al_get_bitmap_width(Settlements[OPPONENT]) / 2.0;
	float cy_city = al_get_bitmap_height(Settlements[OPPONENT]) / 2.0;

	float cx_settlement = al_get_bitmap_width(Houses[OPPONENT]) / 2.0;
	float cy_settlement = al_get_bitmap_height(Houses[OPPONENT]) / 2.0;

	al_draw_scaled_rotated_bitmap(Roads[OPPONENT], cx_road, cy_road, 0.75 * WIDTH, 0.925 * HEIGHT, 0.15, 0.15, 0.0, NULL);
	al_draw_filled_circle(0.75 * WIDTH, 0.86 * HEIGHT, 10, al_map_rgb(255, 243, 154));
	al_draw_circle(0.75 * WIDTH, 0.86 * HEIGHT, 10, al_map_rgb(0, 0, 0), 3);
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.75 * WIDTH - 5.0, 0.86 * HEIGHT - 9.0, ALLEGRO_ALIGN_LEFT, to_string(TOTAL_ROADS - opponent->getRoadsBuilt()).c_str());

	al_draw_scaled_rotated_bitmap(Settlements[OPPONENT], cx_city, cy_city, 0.75 * WIDTH + 0.5 * (cx_settlement + cx_city), 0.925 * HEIGHT, 0.15, 0.15, 0.0, NULL);
	al_draw_filled_circle(0.75 * WIDTH + 0.5 * (cx_settlement + cx_city), 0.86 * HEIGHT, 10, al_map_rgb(255, 243, 154));
	al_draw_circle(0.75 * WIDTH + 0.5 * (cx_settlement + cx_city), 0.86 * HEIGHT, 10, al_map_rgb(0, 0, 0), 3);
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.75 * WIDTH + 0.5 * (cx_settlement + cx_city) - 5.0, 0.86 * HEIGHT - 9.0, ALLEGRO_ALIGN_LEFT, to_string(TOTAL_CITIES - opponent->getCitiesBuilt()).c_str());

	al_draw_scaled_rotated_bitmap(Houses[OPPONENT], cx_settlement, cy_settlement, 0.75 * WIDTH + cx_settlement * 0.5, 0.925 * HEIGHT, 0.15, 0.15, 0.0, NULL);
	al_draw_filled_circle(0.75 * WIDTH + cx_settlement * 0.5, 0.86 * HEIGHT, 10, al_map_rgb(255, 243, 154));
	al_draw_circle(0.75 * WIDTH + cx_settlement * 0.5, 0.86 * HEIGHT, 10, al_map_rgb(0, 0, 0), 3);
	al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), 0.75 * WIDTH + cx_settlement * 0.5 - 5.0, 0.86 * HEIGHT - 9.0, ALLEGRO_ALIGN_LEFT, to_string(TOTAL_SETTLEMENTS - opponent->getSettlementsBuilt()).c_str());

	al_flip_display();
}

void Graphics::
drawCards()
{
	float cx = al_get_bitmap_width(ResourceCards[0]) / 2.0;
	float cy = al_get_bitmap_height(ResourceCards[0]) / 2.0;

	float dx = 0.06 * WIDTH;
	float dy = 0.2 * HEIGHT;
	
	string number = "";
	
	for (int i = 0; i < 5; i++)
	{
		al_draw_scaled_rotated_bitmap(ResourceCards[i], cx, cy, dx, dy + i * cx * 1.25, 0.4, 0.4, 0.0, NULL);
		al_draw_filled_circle(dx + cx * 0.6, dy + i * cx * 1.25, 10, al_map_rgb(255, 243, 154));
		al_draw_circle(dx + cx * 0.6, dy + i * cx * 1.25, 10, al_map_rgb(0, 0, 0), 3);
		switch (i)
		{
		case ORE1:
		{
			al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), dx + cx * 0.6 - 5.0, dy + i * cx * 1.25 - 9.0, ALLEGRO_ALIGN_LEFT, to_string(player->getResourceCards().ore).c_str());
		}break;
		case GRAIN1:
		{
			al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), dx + cx * 0.6 - 5.0, dy + i * cx * 1.25 - 9.0, ALLEGRO_ALIGN_LEFT, to_string(player->getResourceCards().grain).c_str());
		}break;
		case WOOL1:
		{
			al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), dx + cx * 0.6 - 5.0, dy + i * cx * 1.25 - 9.0, ALLEGRO_ALIGN_LEFT, to_string(player->getResourceCards().wool).c_str());
		}break;
		case LUMBER1:
		{
			al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), dx + cx * 0.6 - 5.0, dy + i * cx * 1.25 - 9.0, ALLEGRO_ALIGN_LEFT, to_string(player->getResourceCards().lumber).c_str());
		}break;
		case BRICK1:
		{
			al_draw_text(input->getFont(), al_map_rgb(0, 0, 0), dx + cx * 0.6 - 5.0, dy + i * cx * 1.25 - 9.0, ALLEGRO_ALIGN_LEFT, to_string(player->getResourceCards().brick).c_str());
		}break;
		default:break;
		}
	}
	al_flip_display();
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
	delete[] this->Tokens;
	delete[] this->Dices;
	delete[] this->ResourceCards;
	delete[] this->Houses;
	delete[] this->Settlements;
	delete[] this->Roads;
	al_shutdown_primitives_addon();
	
	al_shutdown_font_addon();
}

void Graphics::
drawDices(dices_t dices)
{
	drawDices(dices.first_dice, dices.second_dice);
}
void Graphics::
drawDices(unsigned int dice1, unsigned int dice2)
{
	float dx1, dy1, dx2, dy2;

	dx1 = 0.85 * WIDTH - 5.0 - al_get_bitmap_width(Dices[dice1 - 1]) / 2.0;
	dx2 = 0.85 * WIDTH + 5.0 + al_get_bitmap_width(Dices[dice1 - 1]) / 2.0;

	dy1 = 0.15 * HEIGHT;
	dy2 = dy1;
	
	al_draw_scaled_rotated_bitmap(Dices[dice1 - 1], al_get_bitmap_width(Dices[dice1 - 1]) / 2.0, al_get_bitmap_height(Dices[dice1 - 1]) / 2.0, dx1, dy1, 1.0 / 2.0, 1.0 / 2.0, 0.0, NULL);
	al_draw_scaled_rotated_bitmap(Dices[dice2 - 1], al_get_bitmap_width(Dices[dice2 - 1]) / 2.0, al_get_bitmap_height(Dices[dice2 - 1]) / 2.0, dx2, dy2, 1.0 / 2.0, 1.0 / 2.0, 0.0, NULL);
}