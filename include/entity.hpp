#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Entity 
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex, int scale);
	float GetX();
	float GetY();
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

