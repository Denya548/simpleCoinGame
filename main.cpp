#include "Program.hpp"
Program program;

int main(){
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	Uint32 frameStart;
	int frameTime;
	program.init("PetSimZero", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, program.width, program.height, false);
	
	while(program.isRunning){
		frameStart = SDL_GetTicks();

		program.update();
		program.handleEvents();
		program.render();

		frameTime = SDL_GetTicks() - frameStart;
		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}
	}

	program.clean();
	return(0);
}
