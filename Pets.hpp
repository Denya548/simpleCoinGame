#pragma once 
#include "Program.hpp"

struct Pets{
	void update();
	SDL_Texture* texture;
	SDL_Rect destR = {64, 960 - 168 / 2 - 24, 128 / 2, 168 / 2}; //169 its true 

	int homePos[2] = {destR.x, destR.y};
	int endPos[2] = {destR.x, destR.y};
	float posX = destR.x;
	float posY = destR.y;

	int *coinMoney; //???
	int tempDelay = 0;	
	
	float coinMultiply = 1;
	float moneyMultiply = 0;
	int ID = 0; //for textures
	int delay = 1000;	//ms	
	int strength = 1;
	int speed = 5;

	bool movement = false;
	bool attack = false;
};

