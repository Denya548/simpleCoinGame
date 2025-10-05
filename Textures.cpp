#include "Textures.hpp"

void Textures::loadTextures(SDL_Renderer* rend, Textures* tex){
	tex->cat = TextureManager::LoadTexture("Textures/Cat.png", rend);
	tex->coin = TextureManager::LoadTexture("Textures/coin.png", rend);
}
