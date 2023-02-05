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
	SDL_RendererFlip playerFlip;
	void move(float p_distance, SDL_Event event);
	void update();
	void isColliding(Entity &p_entity);
	SDL_Texture* getTexture();
	SDL_Rect getPlayerRect();
	bool getCollidingStatus();
private:
	int speed;
	bool xMoving, yMoving;
	float xCoordinate, yCoordinate;
	float xVel, yVel;
	bool colliding;
	float x, y;
	SDL_Rect playerRect;
	SDL_Texture* tex;
};