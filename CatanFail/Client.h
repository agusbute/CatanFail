#pragma once
#include "boost/asio.hpp"
#include <iostream>
#include "SocketControl.h"
#define PORT "13225"
using namespace std;


class client: NetworkSocket
{
public:
	client();
	~client();

protected:

};