#pragma once 
#include "Program.hpp"

struct Textures{
	SDL_Texture* pets[256];
	SDL_Texture* cat;
	SDL_Texture* coin;
	void loadTextures(SDL_Renderer *rend, Textures *tex);
};
