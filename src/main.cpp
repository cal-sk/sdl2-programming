#include <SDL2/SDL.h> // SDL
#include <SDL2_image/SDL_image.h> // SDL_image for rendering textures
#include <iostream>
#include <cstdlib> // for malloc and free

// include header files
#include <render_window.hpp>
#include <entity.hpp>
#include <player.hpp>

// define window height and width
#define WIDTH 640
#define HEIGHT 640
#define SCALE 4
#define TILEWIDTH SCALE * 16
#define TILEHEIGHT SCALE * 16


int main(int argc, char *argv[])
{
// check for intialization errors
  if (SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "SDL failure" << SDL_GetError() << std::endl;
  if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG Init failure" << SDL_GetError() << std::endl;

  RenderWindow window("Topdown Roguelike", WIDTH, HEIGHT);


/* game loop boolean */
  bool gameRunning = true;
  // flip the texture
  SDL_RendererFlip playerFlip = SDL_FLIP_NONE;

/* LOAD TEXTURES HERE */

  SDL_Texture* wall_texture = window.loadTexture("res/bg.png");
  SDL_Texture* world_background = window.loadTexture("res/world_background.png");
  SDL_Texture* player_texture = window.loadTexture("res/player.png");


/* DEFINE ENTITIES AND PLAYER HERE */
  Player player(128, 128, player_texture, SCALE);

  Entity background = Entity(0,0, world_background, 8);

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

    // check for SDL events
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT){
        gameRunning = false;
      }
      // check for key input 
      if (event.type == SDL_KEYDOWN)
      {
        // left movement
        if (SDLK_a == event.key.keysym.sym)
        {
          player.move(1, TILEWIDTH);
          // flip player when looking left
          playerFlip = SDL_FLIP_HORIZONTAL;
        }
        // right movement
        if (SDLK_d == event.key.keysym.sym)
        {
          player.move(0, TILEWIDTH);
          // disable flip when looking
          playerFlip = SDL_FLIP_NONE;
        }
        // up movement
        if (SDLK_w == event.key.keysym.sym)
        {
          player.move(2, TILEWIDTH);
        }
        // down movement
        if (SDLK_s == event.key.keysym.sym)
        {
          player.move(3, TILEWIDTH);
        }
      }
    }
    /*
    if (player.getCollidingStatus() == true)
    {
      std::cout << "Colliding!" << std::endl;
    } else {
      std::cout << "Not Colliding!" << std::endl;
    } */


    // clear the window
    window.clear();

// render entities
    window.render(background, 8);

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
          // check for colliding
          player.isColliding(walls[i][l]);
        }
      }
      // render top and bottom walls
      if (i == 2 || i == 3)
        for (int l=0; l < WIDTH/TILEWIDTH; l++)
        {
          window.render(walls[i][l], 1);
          // check for colliding
          player.isColliding(walls[i][l]);
        } 

    }
    window.render_player(player, 1, playerFlip);
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