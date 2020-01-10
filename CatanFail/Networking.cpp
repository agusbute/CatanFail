#pragma once


#include <string>



/* Timeout medido en minutos */
#define NETWORKING_TIMEOUT 150

using namespace std;

class CatanNetworking : public Observer {
public:

	/*
	* Estados de funcionamiento del CatanNetworking
	*/
	static const char* StateString[18];

	enum States : unsigned int {
		DISCONNECTED, LISTENING, WAIT_SYNC, SYNC, IDLE, NET_ERROR,
		LISTEN_BANK, LISTEN_BUILDING, LISTEN_DICES, LISTEN_END, LISTEN_OFFER, LISTEN_QUIT,
		TELL_BANK, TELL_BUILDING, TELL_DICES, TELL_END, TELL_OFFER, TELL_QUIT, CLOSED
	};

	/*
	* CatanNetworking
	* Se construye el CatanNetworking con una referencia
	* del juego para acceder a su informacion, ademas por ser observer.
	*/
	CatanNetworking(CatanGame& _game);
	~CatanNetworking();

	/*
	* run
	* Actualiza estado del socket y revisa mensajes,
	* ejecutando el protocolo y estado networking actual
	*/
	void run(void);

	/*
	* update
	* Es notificado de una actualizacion de el CatanGame
	* con lo cual busca eventos y ejecuta el protocolo o
	* estado actual networking para ello.
	*/
	void update(void);

	/*
	* start
	* Reinicia al estado disconnected y
	* corre el cambio de estado.
	*/
	void start(void);
	void reset(void);

	/*
	* Devuelve identificador del estado de networking
	* ya segun su id, o un string representativo del estado
	*/
	CatanNetworking::States getNetworkingState(void);
	const char* getNetworkingString(void);

	/*
	* getState
	* Devuelve el estado actual de Networking
	*/
	NetworkingState* getState(void);

	/*
	* info
	* Devuelve el mensaje de Networking, si lo hubiera.
	*/
	string info(void);
	void setInfo(string _info);

	/*
	* good
	* Devuelve true si Networking carece de errores al momento.
	*/
	bool good(void);

	/*
	* changeState
	* Cambia el estado del Networking
	*/
	void changeState(NetworkingState* state, string _info = "");
	void changeState(CatanNetworking::States state, string _info = "");

	/*
	* setError
	* Configura un estado de error en el Networking
	*/
	void setError(string msg);
	void setError(const char* msg);

	/*
	* getEventPacket
	* Crea un paquete de datos a partir de un Evento del juego
	*/
	NetworkPacket* getEventPacket(CatanEvent* event);

	/* Getters paara los NetworkingStates */
	CatanGame& getGame(void);
	NetworkSocket*& getSocket(void);
	string getIp(void);
	unsigned int getPort(void);

	void setIp(string ip);
	void setPort(unsigned int port);
	void setSocket(NetworkSocket* socket);

private:

	/*
	* verifyStatus
	* Verifica el estado actual de Networking, en caso de estar
	* en estado de error, levanta excepcion para indicar error en la
	* utilizacion de Networking.
	*/
	void verifyStatus(void) const;

private:
	string ip;
	unsigned int port;
	NetworkingState* currState;
	bool status;
	string msg;
	NetworkSocket* socket;
	CatanGame& game;

	map<CatanNetworking::States, NetworkingState*> states;
};