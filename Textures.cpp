#include "Textures.hpp"

void Textures::loadTextures(SDL_Renderer* rend, Textures* tex){
	for(int i = 0; i < 256; i++){
		std::string path = "Textures/" + std::to_string(i + 1) + ".png";
		const char* cpath = path.c_str();
		tex->pets[i] = TextureManager::LoadTexture(cpath, rend);
	}
	tex->cat = TextureManager::LoadTexture("Textures/Cat.png", rend);
	tex->coin = TextureManager::LoadTexture("Textures/coin.png", rend);
}
