#include <entity.hpp>
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex, int scale)
:x(p_x), y(p_y), tex(p_tex)
{
	// define the current frame SDL_Rect
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 16 * scale;
	currentFrame.h = 16 * scale;
}

/* GET X POSITION */
float Entity::GetX()
{
	return x;
}

/* GET Y POSITION */
float Entity::GetY()
{
	return y;
}

/* GET TEXTURE */
SDL_Texture* Entity::getTexture()
{
	return tex;
}

/* GET CURRENT FRAME */
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}