#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BoardComponent.h"

using namespace :: std;

class SeaFrameTiles : public BoardComponent
{
	public:
		SeaFrameTiles(char position_in_map = 0);


	private:
		int harbor; //???????
};