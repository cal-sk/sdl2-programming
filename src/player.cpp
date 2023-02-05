#include <player.hpp>
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include <entity.hpp>
#include <iostream>

Player::Player(float p_x, float p_y, SDL_Texture* p_tex, int scale)
:x(p_x), y(p_y), tex(p_tex)
{
	// define the current frame SDL_Rect
	playerRect.x = 0;
	playerRect.y = 0;
	xVel = 0;
	yVel = 0;
	speed = 4;
	xCoordinate = 0;
	yCoordinate = 0;
	colliding = false;
	playerRect.w = 16 * scale;
	playerRect.h = 16 * scale;
}


// move the player x, to move the destination rect
void Player::move(float p_distance, SDL_Event event)
{
	
	if (event.type == SDL_KEYDOWN && !yMoving && !xMoving)
	{
		// delay between movement
		SDL_Delay(250);
		// left movement
		if (SDLK_a == event.key.keysym.sym && !yMoving)
		{
			xCoordinate = x - p_distance;
			if (x > xCoordinate)
			{
				xVel = -speed;
				xMoving = true;
			}

		// flip player when looking left
			playerFlip = SDL_FLIP_HORIZONTAL;
		}
		// right movement
		if (SDLK_d == event.key.keysym.sym && !yMoving)
		{
			// disable flip when looking
			xCoordinate = x + p_distance;
			if (x < xCoordinate)
			{
				xVel = speed;
				xMoving = true;
			}
			playerFlip = SDL_FLIP_NONE;
		}
		// up movement
		if (SDLK_w == event.key.keysym.sym && !xMoving)
		{
			yCoordinate = y - p_distance;
			if (y > yCoordinate)
			{
				yVel = -speed;
				yMoving = true;
			}
		}
		// down movement
		if (SDLK_s == event.key.keysym.sym && !xMoving)
		{
			yCoordinate = y + p_distance;
			if (y < yCoordinate)
			{
				yVel = speed;
				yMoving = true;
			}
		}

	}
}

void Player::update()
{
	if (y == yCoordinate)
	{
		yVel = 0;
		yMoving = false;
	}
	if (x == xCoordinate)
	{
		xVel = 0;
		xMoving = false;
	}
	if (y != yCoordinate && !xMoving)
	{
		y += yVel;
	}
	if (x != xCoordinate && !yMoving)
	{
		x += xVel;
	}
}

void Player::isColliding(Entity &p_entity)
{
	float entityX, entityY;
	float entityW, entityH;

	// get the X value of the entity being checked
	entityX = p_entity.GetX();
	entityY = p_entity.GetY();

	// get the width of the entity being chekced
	entityW = p_entity.getTileRect().w;
	entityH = p_entity.getTileRect().h;

	// COLLISION MATH
	if (x + playerRect.w + 1 <= entityX || y + playerRect.h + 1 <= entityY || y -1 >= entityY + entityH || x -1 >= entityX + entityW)
	{
		colliding = false;
	}
	else 
	{
		colliding = true;

	}
}

/* GET COLLIDER BOOL */
bool Player::getCollidingStatus()
{
	return colliding;
}

/* GET X POSITION */
float Player::GetX()
{
	return x;
}

/* GET Y POSITION */
float Player::GetY()
{
	return y;
}

/* GET TEXTURE */
SDL_Texture* Player::getTexture()
{
	return tex;
}

/* GET CURRENT FRAME */
SDL_Rect Player::getPlayerRect()
{
	return playerRect;
}