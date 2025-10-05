#pragma once 
#include "Program.hpp"

struct Pets{
	SDL_Rect destR = {0, 1920 / 2 - 168 / 2, 128 / 2, 168 / 2}; //169 its true
	int posX;
	int posY;
	void update();
};

