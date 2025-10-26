#pragma once 
#include "Program.hpp"

struct Coin{
	SDL_Rect destR = {0, 0, 64, 64};
	int money = 10;

	static void render(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* destR);
	bool clickCheck(int mousePos[2]);
	void update(Coin c[]);

	int tempDelay = 0;
	int delay = 2000;
	bool cd = true;
};
