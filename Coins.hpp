#pragma once 
#include "Program.hpp"

struct Coin{
	SDL_Rect destR = {0, 0, 64, 64};
	int posX;
	int posY;
	static void render(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* destR);
};
