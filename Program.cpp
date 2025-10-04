#include "Program.hpp"

using namespace std;

SDL_Event event;
int mousePos[2];
Textures textures;
Pets pet;

void Program::init(const char *title, int posX, int posY, int width, int height, bool fullscrean){
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		windows[0] = SDL_CreateWindow(title, posX, posY, width, height, 0);
		windows[1] = SDL_CreateWindow(title, posX, posY, width, height, 0);
		renderer[0] = SDL_CreateRenderer(windows[0], -1, 0);
		renderer[1] = SDL_CreateRenderer(windows[1], -1, 0);
		isRunning = true;
		frame = 0;
		
		SDL_HideWindow(windows[1]);

		Textures::loadTextures(renderer[0], &textures);	
	}
}

Uint32 mouseState;

void Program::update(){
	mouseState = SDL_GetMouseState(&mousePos[0], &mousePos[1]);
	frame++;

	pet.update();
}

void Program::handleEvents()
{
    while(SDL_PollEvent(&event)){
		if(event.type == SDL_MOUSEMOTION && event.motion.windowID == SDL_GetWindowID(windows[1])){
			//current window
		}
        switch (event.type)
        {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_q:
						isRunning = false;
						break;
					case SDLK_s:
						SDL_HideWindow(windows[1]);
						break;
					case SDLK_w:
						SDL_ShowWindow(windows[1]);
						break;
					default:
        				break;
				}
				break;

			case SDL_QUIT:
            	isRunning = false;
            	break;
        }
    };
}

SDL_Rect destR = {0, 0, 100, 100}; 

void Program::render(){
	SDL_SetRenderDrawColor(renderer[0], 32, 128 + 64, 32, 0);
	SDL_RenderClear(renderer[0]);

	SDL_SetRenderDrawColor(renderer[1], 64, 128 + 64, 64, 0);
	SDL_RenderClear(renderer[1]);
	//-------------------------------
	SDL_RenderCopy(renderer[0], textures.cat, NULL, &destR);

	//-------------------------------
	SDL_RenderPresent(renderer[0]);
	SDL_RenderPresent(renderer[1]);
}

void Program::clean(){
    SDL_DestroyWindow(windows[0]);
    SDL_DestroyWindow(windows[1]);
    SDL_DestroyRenderer(renderer[0]);
    SDL_DestroyRenderer(renderer[1]);
    SDL_Quit();
 }

//g++ Program.cpp main.cpp TextureManager.cpp Texture.cpp Pets.cpp -o main -lSDL2 -lSDL2_image
