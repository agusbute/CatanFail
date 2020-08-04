#include "Game.h"

Game::
Game(Board* board_, Player* player_, Player* opponent_, Input* input_, Graphics * graphics_, Network * network_)
{
	graphics = graphics_;
	player = player_;
	opponent = opponent_;
	board = board_;
	input = input_;
	network = network_;

	player->setBoard(board);
	opponent->setBoard(board);

	fsm_matrix[PLAYER_STATE][DEFAULT] = &player_default;
	fsm_matrix[PLAYER_STATE][TRADE] = &player_trade;
	fsm_matrix[PLAYER_STATE][DICES_7] = &player_dices_7;
	fsm_matrix[PLAYER_STATE][BUILD] = &player_build;
	fsm_matrix[PLAYER_STATE][PASS] = &player_pass;
	fsm_matrix[PLAYER_STATE][EXIT] = &player_exit;

	fsm_matrix[OPPONENT_STATE][DEFAULT] = &opponent_default;
	fsm_matrix[OPPONENT_STATE][TRADE] = &opponent_trade;
	fsm_matrix[OPPONENT_STATE][DICES_7] = &opponent_dices_7;
	fsm_matrix[OPPONENT_STATE][BUILD] = &opponent_build;
	fsm_matrix[OPPONENT_STATE][PASS] = &opponent_pass;
	fsm_matrix[OPPONENT_STATE][EXIT] = &opponent_exit;

	player_state = PLAYER_STATE;
	turn_state = DEFAULT;

}

Game::
~Game()
{

}

void Game::
play()
{
	/*
	//network->begin recibe el tablero en blanco y el jugador para hacer la conexion
	//decide si es client o server hace el intercambio de data
	//y si somos server crea el tablero y se lo manda al otro jugador
	opponent->setName(network->getOpponentName());//network guarda el nombre del oponente en un string
	*/
	

	while (!input->exitGame())
	{
		this->input->evDispatcher();
		*fsm_matrix[player_state][turn_state]();
	}
	

}

void Game::
createDevelopmentCards(void)
{
	char knight_counter = 0, road_b_counter = 0, victory_counter = 0, monopoly_counter = 0, year_of_p_counter = 0;

	srand(time(NULL));
	char type = rand() % 5 + 1; // 1 = knight, 2 = monopoly, 3 = victory, 4 = road building, 5 = year of plenty

	char i = 0; //contador
	while (i < TOTAL_D_CARDS)
	{
		if (type == 1 && knight_counter < TOTAL_KNIGHT_CARDS)
		{
			development_cards.push(DevelopmentCard(KNIGHT));
			knight_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 2 && monopoly_counter < TOTAL_MONO_CARDS)
		{
			development_cards.push(DevelopmentCard(MONO));
			monopoly_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 3 && victory_counter < TOTAL_V_POINT_CARDS)
		{
			development_cards.push(DevelopmentCard(V_POINT));
			victory_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 4 && road_b_counter < TOTAL_R_BUILDING_CARDS)
		{
			development_cards.push(DevelopmentCard(R_BUILDING));
			road_b_counter++;
			type = rand() % 5 + 1;
		}
		else if (type == 5 && year_of_p_counter < TOTAL_YEAR_OF_P_CARDS)
		{
			development_cards.push(DevelopmentCard(YEAR_OF_P));
			year_of_p_counter++;
			type = rand() % 5 + 1;
		}
	}
}

bool Game::
checkSettlement(settlement_t settlement)
{
	bool ret = false;
	if (board->inNodes(settlement)) //si se introdujo un nodo que no existe, devuelve false
	{
		//si el contrincante o el jugador ya construyeron ahi, no se puede hacer nada, devuelve false
		if (!(opponent->searchBuilding(settlement)) && !(player->searchBuilding(settlement)))
		{
			//busco nodos adyacentes
			coord_t adjacent_nodes[3];
			board->getAdjacentNodes(settlement, adjacent_nodes);

			//si el contrincante o el jugador ya construyeron en los adyacentes, no se puede hacer nada, devuelve false
			if (!(opponent->searchBuilding(adjacent_nodes[0])) && !(player->searchBuilding(adjacent_nodes[0])) &&
				!(opponent->searchBuilding(adjacent_nodes[1])) && !(player->searchBuilding(adjacent_nodes[1])) &&
				!(opponent->searchBuilding(adjacent_nodes[2])) && !(player->searchBuilding(adjacent_nodes[2])))
			{
				//busco calles adyacentes --- EN EL PRIMER TURNO ESTO NO SE TIENE QUE TENER EN CUENTA
				if (!(turnCounter < 3))
				{
					road_t adjacent_roads[3];
					board->getNodeAdjacentRoads(settlement, adjacent_roads);

					//si hay una calle del jugador en las aristas adyacentes(lo que teniendo en cuenta
					//que no puede haber un settlement en los nodos adyacentes significa que hay al menos dos caminos)
					//entonces se puede construir
					if (player->searchRoad(adjacent_roads[0]) ||
						player->searchRoad(adjacent_roads[1]) ||
						player->searchRoad(adjacent_roads[2]))
					{
						ret = true;
					}
				}
				else
				{
					ret = true;
				}

			}
		}
	}
	return ret;
}

bool Game::
checkSettlement(char x, char y, char z)
{
	return checkSettlement({ x, y, z });
}

bool Game::
checkRoad(road_t road)
{
	return checkRoad(road.x, road.y, road.z);
}

bool Game::
checkRoad(char x, char y, char z)
{
	bool ret = false;
	if (board->inEdges({ x, y, z })) //si se introdujo una calle que no existe, chau, false
	{
		if (!(opponent->searchRoad(x, y, z)) && !(player->searchRoad(x, y, z))) //si el contrincante o el jugador ya construyeron ahi, no se puede hacer nada, devuelve false
		{
			//primer turno
			if (turnCounter < 3)
			{
				coord_t adjacent_nodes[2];
				board->getRoadAdjacentNodes({ x, y, z }, adjacent_nodes);
				if (player->searchBuilding(adjacent_nodes[0]) || player->searchBuilding(adjacent_nodes[1]))
				{
					ret = true;
				}
			}
			//resto(a partir de los primeros turnos, todos los settlements tienen calles saliendo de ellos, asi que con fijarse las calles adyacentes es suficiente)
			else
			{
				//buscar calles adyacentes
				road_t adjacent_roads[] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
				board->getAdjacentRoads({ x, y, z }, adjacent_roads);
				for (int i = 0; i < 4; i++)
				{
					ret = (ret || player->searchRoad(adjacent_roads[i]));
				}
			}
		}
	}
	return ret;
}

void Game::
checkMaritimeTrade(Resources my_r_card, Resources the_r_card_i_want, MaritimeTradeType trade)
{
	coord_t node;
	switch (trade)
	{
		case THREE_X_ONE:
		{
			for (int i = 0; i < SEA_FRAME_TILES; i++)
			{
				if (board->all_the_sea_frames[i].getPorts().port1.port == ports::ANY)
				{
					node = board->all_the_sea_frames[i].getPorts().port1.node1;
					if (player->searchBuilding(node))
					{
						player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
						break;
					}
					else
					{
						node = board->all_the_sea_frames[i].getPorts().port1.node2;
						if (player->searchBuilding(node))
						{
							player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
							break;
						}
					}
				}
				else if (board->all_the_sea_frames[i].getPorts().port2.port == ports::ANY)
				{
					node = board->all_the_sea_frames[i].getPorts().port2.node1;
					if (player->searchBuilding(node))
					{
						player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
						break;
					}
					else
					{
						node = board->all_the_sea_frames[i].getPorts().port2.node2;
						if (player->searchBuilding(node))
						{
							player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
							break;
						}
					}
				}
			}
		} break;
	
		case TWO_X_ONE:
		{
			for (int i = 0; i < SEA_FRAME_TILES; i++)
			{
				if (board->all_the_sea_frames[i].getPorts().port1.port == my_r_card)
				{
					node = board->all_the_sea_frames[i].getPorts().port1.node1;
					if (player->searchBuilding(node))
					{
						player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
						break;
					}
					else
					{
						node = board->all_the_sea_frames[i].getPorts().port1.node2;
						if (player->searchBuilding(node))
						{
							player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
							break;
						}
					}
				}
				else if (board->all_the_sea_frames[i].getPorts().port2.port == my_r_card)
				{
					node = board->all_the_sea_frames[i].getPorts().port2.node1;
					if (player->searchBuilding(node))
					{
						player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
						break;
					}
					else
					{
						node = board->all_the_sea_frames[i].getPorts().port2.node2;
						if (player->searchBuilding(node))
						{
							player->maritimeTrade(my_r_card, the_r_card_i_want, trade);
							break;
						}
					}
				}
			}
		}
	
	}
}

bool Game::
checkLongestRoad(char x, char y, char z) //chequear si la calle es mas larga
{
	vector <road_t> roads;
	bool ret;
	if (longestRecursive({ x, y, z }, roads) >= 5)
	{
		if (player->getLongest() > opponent->getLongest())
		{
			ret = true;
		}
	}
	return ret;
}

unsigned int Game::
longestRecursive(road_t road, vector <road_t> &previous_roads, unsigned int length)
{
	unsigned int lengths[] = { 0, 0, 0, 0 };
	unsigned int longest;
	if (road.x != 0 && road.y != 0)		//solo se fija si las calles no son todo cero
	{	
		if (player->searchRoad(road))	//solo sigue si hay una calle construida ahi
		{
			lengths[0]++;
			lengths[1]++;
			lengths[2]++;
			lengths[3]++;
			if (!(inPreviousRoads(road, previous_roads)))		//solo sigue si no paso por esa calle todavia
			{
				previous_roads.push_back(road);
				road_t adjacent_roads[] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
				board->getAdjacentRoads({ road.x, road.y, road.z }, adjacent_roads);

				for (int i = 0; i < 4; i++)
				{
					lengths[i] += longestRecursive(adjacent_roads[i], previous_roads, lengths[i]);
				}
			}
		}
	}
	longest = max(max(lengths[0], lengths[1]), max(lengths[2], lengths[3]));
	return longest;
}

bool Game::
inPreviousRoads(road_t road, vector <road_t> &previous_roads) //devuelve true is road esta en previous_roads
{
	bool ret = false;
	for (int i = 0; i < previous_roads.size(); i++)
	{
		if (road == previous_roads[i])
		{
			ret = true;
			break;
		}
	}
	return ret;
}

bool Game::
moveRobber(TerrainHexes &place_robber_here)
{
	bool keep_searching = true;

	bool can_i = false;
	if ((player->getDiceNumber() == 7) && (!place_robber_here.hasRobber()))	//me aseguro que haya salido el 7 y que el hex que elegí no tenga ya el robber
	{
		for (int i = 0; i < TERRAIN_HEXES, keep_searching == true; i++)
		{
			if (board->all_the_hexes[i].hasRobber())	//me fijo donde está el robber
			{
				board->all_the_hexes[i].setRobber(false);	//lo saco
				keep_searching = false;
			}
		}
		place_robber_here.setRobber(true);	//y lo ubico en la posición que quiero
	}
	return keep_searching;
}

bool Game::
moveRobber(char move_robber_here)
{
	TerrainHexes * hex = (TerrainHexes *)board->getPiece(move_robber_here); //ya se que va a ser un hexagono(el robber no puede ir en pieza de mar

	return moveRobber(*hex);
}

void Game::
incrementTurnCounter()
{
	turnCounter++;
}

unsigned int Game::
getTurnCounter()
{
	return turnCounter;
}

//fsm functions
void Game::
player_default(void) {}
void Game::
opponent_default(void) {}

void Game::
player_trade(void) {}
void Game::
opponent_trade(void) {}

void Game::
player_dices_7(void) {}
void Game::
opponent_dices_7(void) {}

void Game::
player_build(void) {}
void Game::
opponent_build(void) {}

void Game::
player_pass(void) {}
void Game::
opponent_pass(void) {}

void Game::
player_exit(void) {}
void Game::
opponent_exit(void) {}