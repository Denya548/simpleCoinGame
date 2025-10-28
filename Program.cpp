#include "Program.hpp"

using namespace std;

int Program::money = 10000;

int Inventory::tailSize = 60;
int Inventory::size = 10;
int Inventory::rowSize = 9;

int currentWindow = 0;

SDL_Event event;
TTF_Font* font;
Textures textures;
Textures textures2;

int mousePos[2];
Uint32 mouseState;

const int coinsNum = 99; 
Coin coins[coinsNum];

vector<Pets *> pets; //pets pool
vector<Pets> myPets(10); // pets in inventry

//TEXT RENDER
void renderText(SDL_Renderer* rend, TTF_Font* font, string text, int posX, int posY){ //GG later need to rewrite this code UNLACK
//SDL_Color color = {255, 255, 255};
	SDL_Rect textRect;

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend, textSurface);

	textRect.x = posX;
	textRect.y = posY;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(rend, textTexture, NULL, &textRect);
}

// stats bar position
int petsStatsPosX = 10;
int petsStatsPosY = 10;
Pets lastPet;
int lastTail = 0;

//GUI RENDER
void renderUI(SDL_Renderer* rend[]){
	SDL_SetRenderDrawColor(rend[0], 255, 255, 255, 0);
	SDL_SetRenderDrawColor(rend[1], 0, 255, 255, 0);

	//TOP RECT
	SDL_Rect rect = {0, 0, 1080 / 2, 120};
	SDL_RenderDrawRect(rend[0], &rect);
	//1
	rect = {0, 0, 1080 / 2, 240};
	SDL_RenderDrawRect(rend[1], &rect);
	//text
	renderText(rend[1], font, "Inventory", 10, 10);
	//pets stats
	//if(lastPet != NULL){
		renderText(rend[1], font, "strength: " + to_string(lastPet.strength), petsStatsPosX, petsStatsPosY + 24);
		renderText(rend[1], font, "multiply: " + to_string(int((lastPet.coinMultiply - 1) * 100)) + " %", petsStatsPosX, petsStatsPosY + 24 * 2);
		renderText(rend[1], font, "speed: " + to_string(lastPet.speed), petsStatsPosX, petsStatsPosY + 24 * 3);
		/*renderText(rend[1], font, "multiply: " + to_string(int((pets.coinMultiply - 1) * 100)) + " %", pets.destR.x, pets.destR.y + 84 + 24);
		renderText(rend[1], font, "delay: " + to_string(pets.delay) + " m/s", pets.destR.x, pets.destR.y + 84 + 24 * 2);
		renderText(rend[1], font, "speed: " + to_string(pets.speed), pets.destR.x, pets.destR.y + 84 + 24 * 3);
		renderText(rend[1], font, "Money multiply: " + to_string(int((pets.moneyMultiply) * 100)) + " %", pets.destR.x, pets.destR.y + 84 + 24 * 4);
		*/
	//}

	//BOTTOM RECT
	rect = {0, 1920 / 2 - 120, 1080 / 2, 120};
	SDL_RenderDrawRect(rend[0], &rect);

	//RENDER INVENTORY
	rect = {0, 240, Inventory::tailSize, Inventory::tailSize};
	int currentColumns = 0;
	int currentRow = 0;
	int maxColumns = Inventory::rowSize;
	for(int i = 0; i < myPets.size(); i++){
		SDL_RenderDrawRect(rend[1], &rect);

		//choised tail
		if(i == lastTail){
			SDL_RenderFillRect(rend[1], &rect);
		}

		//tails
		SDL_RenderCopy(rend[1], myPets[i].texture, NULL, &rect);
		if(currentWindow == 1 && rect.x < mousePos[0] && mousePos[0] < rect.x + rect.w &&
				rect.y < mousePos[1] && mousePos[1] < rect.y + rect.h){
			SDL_RenderCopy(rend[1], myPets[i].texture, NULL, &rect);
			lastPet = myPets[i]; 
			lastTail = i; 

			if(mouseState == 1){ //equck pet
				pets[0] = &myPets[i];	
			}
		}

		//next colums
		currentColumns += 1;
		if(currentColumns >= maxColumns){
			currentColumns = 0;
			currentRow += 1;
		}
		rect = {Inventory::tailSize * currentColumns, 240 + Inventory::tailSize * currentRow, Inventory::tailSize, Inventory::tailSize};
	}
}

//INIT
void Program::init(const char *title, int posX, int posY, int width, int height, bool fullscrean){
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		windows[0] = SDL_CreateWindow(title, posX, posY, width, height, 0);
		windows[1] = SDL_CreateWindow(title, posX, posY, width, height, 0);
		renderer[0] = SDL_CreateRenderer(windows[0], -1, 0);
		renderer[1] = SDL_CreateRenderer(windows[1], -1, 0);

		isRunning = true;
		frame = 0;
		
		SDL_HideWindow(windows[1]);
		textures.loadTextures(renderer[0], &textures);	
		textures2.loadTextures(renderer[1], &textures2);	

		srand(time(NULL));
	
		//TEXT	
		TTF_Init();
		font = TTF_OpenFont("text.ttf", 24);

		//---------------------------
		for(int i = 0; i < 10; i++){
			myPets[i].texture = textures2.pets[i];
			myPets[i].ID = i;
		}

		pets.push_back(&myPets[3]);
		/*dog.movement = true;
		dog.homePos[0] += 128;
		dog.endPos[0] += 128;
		dog.speed -= 1;
		*/


		for(int i = 0; i < coinsNum; i++){
			coins[i].destR.x = 64 + (rand() % (1080 / 2 - 128 - 64));
			coins[i].destR.y = 120 + (rand() % (1920 / 2 - 240 - 64));
		}

		myPets[3].strength = 10;
		myPets[3].speed = 10;
	}
}


//UPDATE
void Program::update(){
	mouseState = SDL_GetMouseState(&mousePos[0], &mousePos[1]);
	frame++;
	//printf("%d\n", currentWindow);

	//INPUT UPDATE
	if(mouseState == 1){		// IF MOUSE POS == COIN POS ITS RETURN TRUE
		if(currentWindow == 0){	
			//Inventory::size--;
			for(int i = 0; i < coinsNum; i++){
				if(coins[i].clickCheck(mousePos)){
					for(int p = 0; p < pets.size(); p++){ 
						pets[p]->endPos[0] = coins[i].destR.x - 64 + 128 * p;
						pets[p]->endPos[1] = coins[i].destR.y;

						pets[p]->movement = true;
						pets[p]->coinMoney = &coins[i].money;
					}
				}
			}
		}
		else if(currentWindow == 1){
			//2
		}
	}
	
	//OBJECTS UPDATE
	for(int i = 0; i < pets.size(); i++){
		pets[i]->update();
	}

	for(int i = 0; i < coinsNum; i++){
		coins[i].update(coins);
	}
}

//RENDER
void Program::render(){
	SDL_SetRenderDrawColor(renderer[0], 0, 0, 0, 0);
	SDL_RenderClear(renderer[0]);
	SDL_SetRenderDrawColor(renderer[1], 0, 0, 0, 0);
	SDL_RenderClear(renderer[1]);

	//-------------------------------
	//UI
	renderUI(renderer);
	//money
	renderText(renderer[0], font, "Money:  " + to_string(Program::money) + " coins", 4, 4);
	//time
	renderText(renderer[0], font, "Time:  " + to_string(SDL_GetTicks() / 1000) + " sec", 4, 4 + 24);
	
	//OBJECTS

	//coins	
	for(int i = 0; i < coinsNum; i++){
		if(coins[i].money > 0){
			coins[i].render(renderer[0], textures.coin, &coins[i].destR);
			renderText(renderer[0], font, to_string(coins[i].money), coins[i].destR.x, coins[i].destR.y - 24);
		}
	}

	//pets
	for(int i = 0; i < pets.size(); i++){
		SDL_RenderCopy(renderer[0], textures.pets[pets[i]->ID], NULL, &pets[i]->destR); //with ID beacouse renderers diferets
	}

	//-------------------------------
	SDL_RenderPresent(renderer[0]);
	SDL_RenderPresent(renderer[1]);
}

//CLEAR
void Program::clean(){
    SDL_DestroyWindow(windows[0]);
    SDL_DestroyWindow(windows[1]);
    SDL_DestroyRenderer(renderer[0]);
    SDL_DestroyRenderer(renderer[1]);

	TTF_CloseFont(font);
	TTF_Quit();

    SDL_Quit();
 }

//INPUT
void Program::handleEvents()
{
    while(SDL_PollEvent(&event)){
		if(event.type == SDL_MOUSEMOTION){
			if(event.motion.windowID == SDL_GetWindowID(windows[0])){
				currentWindow = 0;
			}
			if(event.motion.windowID == SDL_GetWindowID(windows[1])){
				currentWindow = 1;
			}
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
						//coins[0].money = 100 + (rand() % 5) * 10;
						break;
					case SDLK_e:
						Program::money = 0;
						break;
					case SDLK_w:
						/*pets[0].endPos[0] = pets[0].homePos[0];
						pets[0].endPos[1] = pets[0].homePos[1];
						pets[0].attack = false;
						pets[0].movement = true;
						*/
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

//g++ Program.cpp main.cpp TextureManager.cpp Textures.cpp Pets.cpp Coins.cpp Functions.cpp -o main -lSDL2 -lSDL2_image -lSDL2_ttf
