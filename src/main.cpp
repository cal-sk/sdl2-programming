#include <SDL2/SDL.h> // SDL
#include <SDL2_image/SDL_image.h> // SDL_image for rendering textures
#include <iostream>
#include <cstdlib> // for malloc and free

// include header files
#include <render_window.hpp>
#include <entity.hpp>
#include <player.hpp>

// define window SCREEN_HEIGHT and SCREEN_WIDTH
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
#define SCALE 4
#define TILE_W 64
#define TILE_H 64


/* 
NOTES: tilemap logic: look through 2d int array for 1 and 2, count the amount of 1s and 2s and allocate space for them in 2d entity array


*/

RenderWindow window("Topdown Roguelike", SCREEN_WIDTH, SCREEN_HEIGHT);

/* Delta Time */
Uint64 lastTick = 0;
Uint64 currentTick = SDL_GetPerformanceCounter();
double deltaTime = 0;

/* 2D ARRAY FOR THE WALLS */
Entity** tilemap = (Entity**)malloc(sizeof(Entity*) * 10);
int map[10][20] = {
  {1, 1, 1, 1, 1, 1 ,1 ,1 ,1,1,1,1,1,1,1,1,1,1,1,1},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,2,0,0,0,0,0,0,0,2},
  {2, 2, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {2, 0, 0, 0, 0, 0 ,0 ,0 ,0,0,0,0,0,0,0,0,0,0,0,2},
  {1, 1, 1, 1, 1, 1 ,1 ,1 ,1,1,1,1,1,1,1,1,1,1,1,1},
};


/* LOAD TEXTURES HERE */

SDL_Texture* vertical_wall_texture = window.loadTexture("res/vertical_tiles.png");
SDL_Texture* horizontal_wall_texture = window.loadTexture("res/horizontal_tiles.png");
SDL_Texture* world_background = window.loadTexture("res/world_background.png");
SDL_Texture* player_texture = window.loadTexture("res/player.png");

/* DEFINE ENTITIES AND PLAYER HERE */
Player player(320, 320, player_texture, SCALE);

Entity world = Entity(0, 0, world_background, 2000);

SDL_Event event;

bool gameRunning = true;

void initTilemap()
{
  for (int i =0; i<10; i++)
  {
    int count = 0;
    for (int l=0; l<20; l++)
    {
      if (map[i][l] == 1 || map[i][l] == 2 || map[i][l] == 0)
      {
        count++;
      }
    }
    tilemap[i] = (Entity*)malloc(sizeof(Entity) * count);
  }

  for (int i =0; i<10; i++)
  {
    for (int l=0; l<20; l++)
    {
      if (map[i][l] == 1)
      {
        tilemap[i][l] = Entity((l * TILE_H), (i * TILE_H), vertical_wall_texture, SCALE);
      }
      if (map[i][l] == 2)
      {
        tilemap[i][l] = Entity((l * TILE_H), (i * TILE_H), horizontal_wall_texture, SCALE);
      }
      if (map[i][l] == 0)
      {
        tilemap[i][l] = Entity((l * TILE_H), (i * TILE_H), vertical_wall_texture, SCALE);
      }
    }
  }
}


// de-initialization function

void deInit()
{
  
  for (int i=0; i< 10; i++)
  {
    free(tilemap[i]);
  } 
  free(tilemap);
  window.cleanUp();
  SDL_Quit();
}

// movement function

void movement(SDL_Event event)
{
  // check for SDL events
  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT){
      gameRunning = false;
    }
    // check for key input 
    player.move(TILE_H, event);
  }
}

// graphics function
 
void graphics()
{

  window.render(world, 1);

  for (int i=0; i<10; i++)
  {
    
    for (int l=0; l < 20; l++)
    {
      if (map[i][l] != 0)
      {
        window.render(tilemap[i][l], 1);
      }
    } 
  } 
  window.render_player(player, 1, player.playerFlip);
}

// collision function

void checkCollisions()
{
  for (int i=0; i<10; i++)
  {
    
    for (int l=0; l < 20; l++)
    {
      if (map[i][l] != 0)
      {
        player.isColliding(tilemap[i][l]);
        if (player.getCollidingStatus() == true)
        {
          std::cout << i * 64 << ", " << l * 64 << std::endl;
        }
      }
    } 
  }

}


int main(int argc, char *argv[])
{
// check for intialization errors
  if (SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "SDL failure" << SDL_GetError() << std::endl;
  if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG Init failure" << SDL_GetError() << std::endl;

// create the walls
  // createWalls();
  initTilemap();


/* MAIN GAME LOOP */
  while (gameRunning)
  {
    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );
    // check for movement
    movement(event);
    player.update();


    // clear the window
    window.clear();

    checkCollisions();

/* RENDER ENTITIES HERE */

    graphics();

    window.display();
    if (deltaTime < 1000/48)
    {
      SDL_Delay(1000/48 - deltaTime);
    }

  }

/* clean up and quit after game loop boolean is false */

  /* FREE ALL ALLOCATED MEMORY HERE */
  deInit();

  return 0;


}