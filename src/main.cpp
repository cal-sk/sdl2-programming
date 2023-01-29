#include <SDL2/SDL.h> // SDL
#include <SDL2_image/SDL_image.h> // SDL_image for rendering textures
#include <iostream>
#include <cstdlib> // for malloc and free

// include header files
#include <render_window.hpp>
#include <entity.hpp>
#include <player.hpp>

// define window height and width
#define WIDTH 1280
#define HEIGHT 1024
#define SCALE 4
#define TILEWIDTH SCALE * 16
#define TILEHEIGHT SCALE * 16


int main(int argc, char *argv[])
{
// check for intialization errors
  if (SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "SDL failure" << SDL_GetError() << std::endl;
  if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG Init failure" << SDL_GetError() << std::endl;

  RenderWindow window("Window", WIDTH, HEIGHT);


/* game loop boolean */
  bool gameRunning = true;

/* LOAD TEXTURES HERE */

  SDL_Texture* wall_texture = window.loadTexture("res/bg.png");
  SDL_Texture* player_texture = window.loadTexture("res/player.png");


/* DEFINE ENTITIES AND PLAYER HERE */
  Player player(128, 128, player_texture, SCALE);

/* 2D ARRAY */
  Entity** walls = (Entity**)malloc(sizeof(Entity*) * 4);

  // LOOP FOR 2D DYNAMICALLY ALLOCATED ARRAY - i=0 is left i=1 is right i=2 is top i =3
  for (int i=0; i < 4; i++)
  {
    std::cout << i << std::endl;
    // LEFT AND RIGHT WALLS
    if (i==0 || i==1)
    {
      // SUBTRACT 1 FOR CORNERS
      // allocate space for the amount of tiles around the edge
      walls[i] = (Entity*)malloc(sizeof(Entity) * (HEIGHT/TILEHEIGHT - 1));

      for (int l=0; l < (HEIGHT/TILEHEIGHT) - 1; l++)
      {
        // left wall
        if (i==0)
        {
          walls[i][l] = Entity(0, (l * TILEHEIGHT) + TILEHEIGHT, wall_texture, SCALE);
        }
        // right wall
        else if (i==1)
        {
          walls[i][l] = Entity(WIDTH-TILEWIDTH, (l * TILEHEIGHT) + TILEHEIGHT, wall_texture, SCALE);
        }
      }
    }
    
    // TOP AND BOTTOM WALLS
    if (i==2 || i==3)
    {
      // allocate space for the amount of tiles around the edge
      walls[i] = (Entity*)malloc(sizeof(Entity) * WIDTH/TILEWIDTH);

      for (int l=0; l < WIDTH/TILEWIDTH; l++)
      {
        // top wall
        if (i==2)
        {
          walls[i][l] = Entity(TILEWIDTH * l, 0, wall_texture, SCALE);
        }
        // bottom wall
        else if (i==3)
        {
          walls[i][l] = Entity(TILEWIDTH * l, HEIGHT-TILEHEIGHT, wall_texture, SCALE);
        }
      }
    }
  }  

  SDL_Event event;

/* MAIN GAME LOOP */
  while (gameRunning)
  {
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT){
        gameRunning = false;
      }
      // check for key input - NOTE: add different key stroke later
      if (event.type == SDL_KEYDOWN)
      {
        player.move(0, TILEWIDTH);
      }
    }
    window.clear();

// render entities

    // render through wall array
    for (int i = 0; i < 4; i++)
    {
      // render left and right walls
      if (i == 0 || i == 1)
      {
        // SUBTRACT 1 FOR CORNERS
        for (int l=0; l < HEIGHT/TILEHEIGHT - 1; l++)
        {
          window.render(walls[i][l], 1);
        }
      }
      // render top and bottom walls
      if (i == 2 || i == 3)
        for (int l=0; l < WIDTH/TILEWIDTH; l++)
        {
          window.render(walls[i][l], 1);
        } 

    }
    window.render_player(player, 1);
    window.display();

  }

/* clean up and quit after game loop boolean is false */

  for (int i=0; i < 4; i++)
  {
    free(walls[i]);
  }
  free(walls);
  
  window.cleanUp();
  SDL_Quit();

  return 0;


}