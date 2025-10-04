#pragma once 
#include "Program.hpp"

struct Textures{
	SDL_Texture* cat;
	static void loadTextures(SDL_Renderer *rend, Textures *tex);
};

