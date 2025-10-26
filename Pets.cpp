#include "Pets.hpp"

void Pets::update(){
	float len = Functions::length(posX, posY, endPos[0], endPos[1]);
//	printf("%d", int(len));
//	printf("\n");

	if(movement){
		if(len < 2 + speed){ // +speed ???
			if(endPos[0] != homePos[0] && endPos[1] != homePos[1]){
				attack = true;
			}
			movement = false;

			posX = endPos[0];
			posY = endPos[1];
		}
		else{
			attack = false;

			posX += ((endPos[0] - posX) / len) * speed;	
			posY += ((endPos[1] - posY) / len) * speed;	
			destR.x = posX;	
			destR.y = posY;
		}	
	}

	if(attack){
		if(*coinMoney > 0){
			if(SDL_GetTicks() - tempDelay > delay){
				*coinMoney = *coinMoney - strength;
				tempDelay = SDL_GetTicks();
				
				Program::money += strength * coinMultiply;
			}
		}
		else{
			Program::money += Program::money * moneyMultiply;

			attack = false;
			movement = true;
			endPos[0] = homePos[0];
			endPos[1] = homePos[1];
		}
		
	}
};
