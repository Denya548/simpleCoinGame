#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>

#include "TextureManager.hpp"
#include "Camera.hpp"
#include "Textures.hpp"
//#include "Pets.hpp"

struct Program{
	SDL_Renderer *renderer[2];
	SDL_Window *windows[2];
	bool isRunning;
	int width = 1080 / 2;
	int height = 1920 / 2;
	void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	int frame = 0;
};
