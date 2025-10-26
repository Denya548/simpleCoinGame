#include "Coins.hpp"

void Coin::render(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* destR){
	SDL_RenderCopy(rend, tex, NULL, destR);
};

bool Coin::clickCheck(int mousePos[2]){
	if(mousePos[0] > destR.x && mousePos[0] < destR.x + destR.w && 
		mousePos[1] > destR.y && mousePos[1] < destR.y + destR.h){
		return true;
	}
	else{
		return false;
	}
};

void Coin::update(Coin c[]){
	if(money < 1 && cd){
		tempDelay = SDL_GetTicks();	
		cd = false;
	}
	if(money < 1 && SDL_GetTicks() - tempDelay > delay){
		money = 10 + rand() % 30;
		
		destR.x = 64 + (rand() % (1080 / 2 - 128));
		destR.y = 120 + (rand() % (1920 / 2 - 240));

		tempDelay = SDL_GetTicks();	
		cd = true;
	}
};
