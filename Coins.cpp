#include "Coins.hpp"

void Coin::render(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* destR){
	SDL_RenderCopy(rend, tex, NULL, destR);
};
