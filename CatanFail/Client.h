#pragma once
#include "boost/asio.hpp"
#include <iostream>
#include "SocketControl.h"
#define PORT "13225"
using namespace std;


class client: public NetworkSocket
{
public:
	client();
	~client();
	NStatus estado;

protected:

};