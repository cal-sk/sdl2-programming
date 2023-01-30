#include <player.hpp>
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include <entity.hpp>
#include <iostream>

Player::Player(float p_x, float p_y, SDL_Texture* p_tex, int scale)
:x(p_x), y(p_y), tex(p_tex)
{
	// define the current frame SDL_Rect
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 16 * scale;
	currentFrame.h = 16 * scale;
}


// move the player x, to move the destination rect
void Player::move(int p_moveDir, float p_distance)
{
	if (p_moveDir == 0)
	{
		x += p_distance;
	}
	if (p_moveDir == 1)
	{
		x -= p_distance;
	
	}
	if (p_moveDir == 2)
	{
		y -= p_distance;
	}
	if (p_moveDir == 3)
	{
		y += p_distance;
	
	}
}

void Player::isColliding(Entity &p_entity)
{
	int entityX, entityY;
	int entityW, entityH;
	entityX = p_entity.GetX();
	entityY = p_entity.GetY();
	entityW = p_entity.getCurrentFrame().w * 4;
	entityH = p_entity.getCurrentFrame().h * 4;

	// add colliding logic here
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
SDL_Rect Player::getCurrentFrame()
{
	return currentFrame;
}