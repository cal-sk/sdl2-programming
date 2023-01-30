#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <entity.hpp>

class Player
{
public:
	Player(float p_x, float p_y, SDL_Texture* p_tex, int scale);
	float GetX();
	float GetY();
	void move(int p_moveDir, float p_distance);
	void update();
	void isColliding(Entity &p_entity);
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
	bool getCollidingStatus();
private:
	bool colliding;
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};