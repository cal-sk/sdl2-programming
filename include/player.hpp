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
	void update(Entity** tilemap, int map[9][16]);
	bool collide(Entity p_entity);
	void checkCollisionsX(Entity** tilemap, int map[9][16]);
	void checkCollisionsY(Entity** tilemap, int map[9][16]);
	Entity* getHits(Entity** tilemap, int map_l, int map_w, int map[9][16]);
	SDL_Texture* getTexture();
	SDL_Rect getPlayerRect();
private:
	int speed;
	bool xMoving, yMoving;
	float xCoordinate, yCoordinate;
	bool canMoveLeft, canMoveRight, canMoveUp, canMoveDown;
	float xVel, yVel;
	float x, y;
	SDL_Rect playerRect;
	SDL_Texture* tex;
};