#include <player.hpp>
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
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
void Player::move(int moveDir, float distance)
{
	// NOTE: Add up and down movement
	if (moveDir == 0)
	{
		x += distance;
	}
	if (moveDir == 1)
	{
		x -= distance;
	
	}
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