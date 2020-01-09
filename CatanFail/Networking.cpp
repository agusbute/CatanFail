#include <exception>
/*
const char*
CatanNetwork::StateString[18] = {
	"DISCONNECTED", "LISTENING", "WAIT_SYNC", "SYNC", "IDLE", "NET_ERROR",
	"LISTEN_BANK", "LISTEN_BUILDING", "LISTEN_DICES", "LISTEN_END", "LISTEN_OFFER",
	"LISTEN_QUIT", "TELL_BANK", "TELL_BUILDING", "TELL_DICES", "TELL_END", "TELL_OFFER", "TELL_QUIT"
};

CatanNetwork::
CatanNetworking(CatanGame& _game) : Observer(), game(_game) {
	// Inicializacion 
	this->ip = "";
	this->port = port;
	this->socket = nullptr;
	this->status = true;
	this->msg = "";
	this->currState = nullptr;

	// Creo todos los estados 
	states.clear();
	states = {
		allocate(States::DISCONNECTED, Disconnected, *this),
		allocate(States::LISTENING, Listening, *this),
		allocate(States::IDLE, Idle, *this),
		allocate(States::WAIT_SYNC, WaitSync, *this),
		allocate(States::SYNC, Sync, *this),
		allocate(States::NET_ERROR, NetError, *this)
	};

	// Mensaje de inicio 
	setInfo("[Networking] - Closed -> Esperando ordenes de conexion.");
}

CatanNetwork::
~CatanNetwork(void) {
	if (socket)
		delete socket;
	for (auto state : states) {
		if (state.second) {
			delete state.second;
		}
	}
}

void
CatanNetwork::setIp(string ip) {
	this->ip = ip;
}

void
CatanNetwork::setInfo(string _info) {
	msg = _info;
}

void
CatanNetwork::setPort(unsigned int port) {
	this->port = port;
}

CatanNetwork::States
CatanNetwork::getNetworkState(void) {
	if (currState == nullptr) {
		return CatanNetwork::States::CLOSED;
	}
	else {
		return (CatanNetwork::States)this->currState->getId();
	}
}

const char*
CatanNetwork::getNetworkString(void) {
	return StateString[this->currState->getId()];
}

unsigned int
CatanNetwork::getPort(void) {
	return port;
}

string
CatanNetwork::getIp(void) {
	return ip;
}

NetworkSocket*&
CatanNetwork::getSocket() {
	return socket;
}

void
CatanNetwork::setSocket(NetworkSocket* socket) {
	this->socket = socket;
}

CatanGame&
CatanNetwork::getGame(void) {
	return this->game;
}

NetworkState*
CatanNetwork::getState(void) {
	return currState;
}

string
CatanNetwork::info(void) {
	return msg;
}

bool
CatanNetwork::good(void) {
	return status;
}

void
CatanNetwork::setError(string msg) {
	this->status = false;
	this->msg = msg;
}

void
CatanNetwork::setError(const char* msg) {
	this->status = false;
	this->msg = msg;
}

void
CatanNetwork::verifyStatus(void) const {
	if (!status) {
		throw exception("Networking - verifyStatus - Hubo un error en el estado de Networking, revisar!");
	}
}

void
CatanNetwork::changeState(CatanNetwork::States state, string _info) {
	if (state == States::CLOSED) {
		currState = nullptr;
		msg = _info;
	}
	else {
		changeState(states[state], _info);
	}
}

void
CatanNetwork::changeState(NetworkState* state, string _info) {
	currState = state;
	currState->context();
	currState->resetTime();
	msg = _info;
}

void
CatanNetwork::start(void) {

	// Estado inicial 
	changeState(States::DISCONNECTED, "[Networking] - Disconnected -> Abriendo socket TCP, intentando establecer conexion...");
}

void
CatanNetwork::reset(void) {

	// Estado cerrado 
	changeState(States::CLOSED);

	// Mensaje informativo! 
	setInfo("[Networking] - Closed -> Networking cerrado! A la espera de reconexion.");

	// Reinicio y reinicializo el estado de todas las variables
	// y objetos contenidos por CatanNetworking.
	
	if (socket) {
		delete socket;
		socket = nullptr;
	}
}

void
CatanNetwork::run() {

	// Verifico estado del Networking 
	verifyStatus();

	// Actualizo el socket 
	if (this->socket) {

		// Si esta conectado 
		if (socket->isConnected()) {
			// Corro las colas de emision y recepcion de Tcp
			socket->run();

			// Verifico estado del socket 
			if (!socket->good()) {
				setError(socket->getError());
			}
		}
	}

	// Ejecuto el run del estado 
	if (this->good()) {

		//
		// Verifico estado de error por timeout de la etapa
		// del proceso networking
		//
		if (this->currState->timeoutStatus()) {
			this->currState->run();
		}
		else {
			this->setError("CatanNetworking - El estado de networking ha tenido un error por timeout! Espera demasiado larga...");
			this->changeState(CatanNetworking::NET_ERROR);
		}
	}
}

void
CatanNetwork::update() {
	// Verifico estado del Networking 
	verifyStatus();

	// Hay algun evento? 
	if (game.hasEvents()) {

		// Busco el evento del juego 
		CatanEvent* event = game.getNextEvent();

		// Verifico que sea para mi, y no un echo!
		if (event->getSource() != CatanEvent::Sources::NETWORKING) {

			//
			// Surgieron o puede surgir, eventos que sean de interes para otras partes del programa
			// pero no asi para el Networking, con lo cual, se presupone que los deberia ignorar el programa
			/
			this->currState->update();
		}
	}
}

NetworkPacket*
CatanNetwork::getEventPacket(CatanEvent* event) {

	
	// Para NO PERDERSER... recordar lo siguiente respecto de este metodo.
	// Este METODO representa todos aquellos eventos de CatanGame, que le son
	// de interes al networking para poder correr sus protocolos, ninguna otra cosa debe
	// parsearse, y cualquier cosa que falte, hara inutil el protocolo.
	//
	// Reitero. Conversion de los eventos de CATAN que al networking le son de INTERES
	// en paquete de datos para transmitirlos!
	

	switch (event->getEvent()) {
	case CatanEvent::Events::THROW_DICES:
		return new DicesPacket(*((DicesEvent*)event));
		break;
	case CatanEvent::Events::ROBBER_CARDS:
		return new RobberCardPacket(*((RobberCardEvent*)event));
		break;
	case CatanEvent::Events::ROBBER_MOVE:
		return new RobberMovePacket(*((RobberMoveEvent*)event));
		break;
	case CatanEvent::Events::BUILDING:
		return new BuildingPacket(*((BuildingEvent*)event));
		break;
	case CatanEvent::Events::BANK_TRADE:
		return new BankPacket(*((BankEvent*)event));
		break;
	case CatanEvent::Events::OFFER_TRADE:
		return new OfferPacket(*((OfferEvent*)event));
		break;
	case CatanEvent::Events::CARD_IS:
		return new CardIsPacket(*((CardIsEvent*)event));
		break;
	case CatanEvent::Events::KNIGHT:
		return new KnightPacket(*((KnightEvent*)event));
		break;
	case CatanEvent::Events::MONOPOLY:
		return new MonopolyPacket(*((MonopolyEvent*)event));
		break;
	case CatanEvent::Events::YOP:
		return new YOPPacket(*((YOPEvent*)event));
		break;
	case CatanEvent::Events::DEV_CARD:
		return new NetworkPacket(PacketHeader::DEV_CARD);
		break;
	case CatanEvent::Events::PASS:
		return new NetworkPacket(PacketHeader::PASS);
		break;
	case CatanEvent::Events::QUIT:
		return new NetworkPacket(PacketHeader::QUIT);
		break;
	case CatanEvent::Events::ERROR_EVENT:
		return new NetworkPacket(PacketHeader::HEADER_ERROR);
		break;
	case CatanEvent::Events::PLAY_AGAIN:
		return new NetworkPacket(PacketHeader::PLAY_AGAIN);
		break;
	case CatanEvent::Events::GAME_OVER:
		return new NetworkPacket(PacketHeader::GAME_OVER);
		break;
	case CatanEvent::Events::WON:
		return new NetworkPacket(PacketHeader::I_WON);
		break;
	case CatanEvent::Events::YES:
		return new NetworkPacket(PacketHeader::YES);
		break;
	case CatanEvent::Events::NO:
		return new NetworkPacket(PacketHeader::NO);
		break;
	case CatanEvent::Events::ROAD_BUILDING:
		return new NetworkPacket(PacketHeader::ROAD_BUILDING);
		break;
	}

	return nullptr;
}
*/