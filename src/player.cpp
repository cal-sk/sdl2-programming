#include <player.hpp>
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include <entity.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

Player::Player(float p_x, float p_y, SDL_Texture* p_tex, int scale)
:x(p_x), y(p_y), tex(p_tex)
{
	// define the current frame SDL_Rect
	playerRect.x = 0;
	playerRect.y = 0;
	xVel = 0;
	yVel = 0;
	speed = 16;
	xCoordinate = 0;
	yCoordinate = 0;
	canMoveLeft = true;
	canMoveRight = true;
	playerRect.w = 16 * scale;
	playerRect.h = 16 * scale;
}



// move the player x, to move the destination rect
void Player::move(float p_distance, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && !yMoving && !xMoving)
	{
		SDL_Delay(80);
		// delay between movement
		// left movement
		if (SDLK_a == event.key.keysym.sym && !yMoving && canMoveLeft)
		{	
			std::cout << "movement" << std::endl;
			xCoordinate = x - p_distance;
			if (x > xCoordinate)
			{
				xVel = -speed;
				xMoving = true;
			}

		// flip player when looking left
			playerFlip = SDL_FLIP_NONE;
		}
		// right movement
		if (SDLK_d == event.key.keysym.sym && !yMoving && canMoveRight)
		{
			std::cout << "movement" << std::endl;
			// disable flip when looking
			xCoordinate = x + p_distance;
			if (x < xCoordinate)
			{
				xVel = speed;
				xMoving = true;
			}				
			


			playerFlip = SDL_FLIP_HORIZONTAL;
		}
		// up movement
		if (SDLK_w == event.key.keysym.sym && !xMoving)
		{
			std::cout << "movement" << std::endl;
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
			std::cout << "movement" << std::endl;
			yCoordinate = y + p_distance;
			if (y < yCoordinate)
			{
				yVel = speed;
				yMoving = true;
			}
		}

	}
}

bool Player::collide(Entity p_entity)
{
	float entLeft = p_entity.GetX();
	float entRight = p_entity.GetX() + p_entity.getTileRect().w;
	float entTop = p_entity.GetY();
	float entBottom = p_entity.GetY() + p_entity.getTileRect().h; 

	if (x + playerRect.w <= entLeft || x >= entRight || y >= entBottom || y + playerRect.h <= entTop)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Entity* Player::getHits(Entity** tilemap, int map_l, int map_w, int map[9][16])
{
  int count = 0;
  for (int i=0; i < map_l; i++)
  {
    for (int l=0; l< map_w; l++)
    {
      if (collide(tilemap[i][l]) && map[i][l] != 0)
      {
        count++;
      }
    }
  }
  if (count > 0)
  {
	  Entity* hits = (Entity*)malloc(sizeof(Entity) * count);
	  int hit_count = 0;
	  for (int k=0; k < map_l; k++)
	  {
	    for (int m=0; m< map_w; m++)
	    {
	      if (collide(tilemap[k][m]) && map[k][m] != 0)
	      {
	      	hits[hit_count] = tilemap[k][m];
	        hit_count++;
	        // std::cout << "collision" << std::endl;
	      }
	    }
	  }
	  return hits;
  }
  else{
  	return NULL;
  }
}

void Player::checkCollisionsY(Entity** tilemap, int map[9][16])
{
	Entity* collisions = getHits(tilemap,9,16, map);
	if (collisions != NULL)
	{
		for (int i=0; i < sizeof(*collisions)/sizeof(collisions[0]); i++)
		{
			if (yCoordinate > y) // moving down
			{
				std::cout << "collision logic" << std::endl;
				y = collisions[i].GetY() - collisions[i].getTileRect().h;
				yCoordinate = y;
				canMoveDown = false;
			}
			else if (yCoordinate < y) // moving up
			{
				std::cout << "collision logic" << std::endl;
				y = collisions[i].GetY() + collisions[i].getTileRect().h;
				yCoordinate = y;
				canMoveUp = false;
			}
		}
		free(collisions);
	}
}

void Player::checkCollisionsX(Entity** tilemap, int map[9][16])
{
	Entity* collisions = getHits(tilemap,9,16, map);
	if (collisions != NULL)
	{
		for (int i=0; i < sizeof(*collisions)/sizeof(collisions[0]); i++)
		{
			if (xCoordinate > x) // moving right
			{
				std::cout << "collision logic" << std::endl;
				x = collisions[i].GetX() - collisions[i].getTileRect().w;
				xCoordinate = x;
				canMoveRight = false;
			}
			else if (xCoordinate < x) // moving left
			{
				std::cout << "collision logic" << std::endl;
				x = collisions[i].GetX() + collisions[i].getTileRect().w;
				xCoordinate = x;
				canMoveLeft = false;
			}
		}
		free(collisions);
	}
}

void Player::update(Entity** tilemap, int map[9][16])
{
	
	if (y == yCoordinate)
	{
		yVel = 0;
		yMoving = false;
		canMoveUp = true;
		canMoveDown = true;
	}
	if (x == xCoordinate)
	{
		xVel = 0;
		xMoving = false;
		canMoveLeft = true;
		canMoveRight = true;
	}
	if (y != yCoordinate && !xMoving)
	{
		y += yVel;
		checkCollisionsY(tilemap, map);
	}
	if (x != xCoordinate && !yMoving)
	{
		x += xVel;
		checkCollisionsX(tilemap, map);
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
SDL_Rect Player::getPlayerRect()
{
	return playerRect;
}