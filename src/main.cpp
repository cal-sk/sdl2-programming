#include <SDL2/SDL.h> // SDL
#include <SDL2_image/SDL_image.h> // SDL_image for rendering textures
#include <iostream>
#include <cstdlib> // for malloc and free

// include header files
#include <render_window.hpp>
#include <entity.hpp>

// define window height and width
#define WIDTH 640
#define HEIGHT 512
#define TILEWIDTH 64
#define TILEHEIGHT 64
#define SCALE 4


int main(int argc, char *argv[])
{
// check for intialization errors
  if (SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "SDL failure" << SDL_GetError() << std::endl;
  if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG Init failure" << SDL_GetError() << std::endl;

  RenderWindow window("Window", WIDTH, HEIGHT);


/* game loop boolean */
  bool gameRunning = true;

/* LOAD TEXTURES HERE */

  SDL_Texture* background = window.loadTexture("res/bg.png");


/* DEFINE ENTITIES HERE */

// allocated array for left & right wall
  /* eventually add 2d array for the walls  Entity** walls = (Entity**)malloc(sizeof(Entity*) * 4); */
  Entity** walls = (Entity**)malloc(sizeof(Entity*) * 4);
  // Entity* left_wall = (Entity*)malloc(sizeof(Entity) * HEIGHT/TILEHEIGHT);
  // Entity* right_wall = (Entity*)malloc(sizeof(Entity) * HEIGHT/TILEHEIGHT);

  // LOOP FOR 2D DYNAMICALLY ALLOCATED ARRAY - i=0 is left i=1 is right i=2 is top i =3
  for (int i=0; i < 4; i++)
  {
    std::cout << i << std::endl;
    // LEFT AND RIGHT WALLS
    if (i==0 || i==1)
    {
      walls[i] = (Entity*)malloc(sizeof(Entity) * HEIGHT/TILEHEIGHT);
      for (int l=0; l < HEIGHT/TILEHEIGHT; l++)
      {
        if (i==0)
        {
          walls[i][l] = Entity(0, l * TILEHEIGHT, background, SCALE);
        }
        else if (i==1)
        {
          walls[i][l] = Entity(WIDTH-TILEWIDTH, l * TILEHEIGHT, background, SCALE);
        }
      }
    }
    
    // TOP AND BOTTOM WALLS
    if (i==2 || i==3)
    {
      walls[i] = (Entity*)malloc(sizeof(Entity) * WIDTH/TILEWIDTH);
      std::cout << &walls[i] << std::endl;
      for (int l=0; l < WIDTH/TILEWIDTH; l++)
      {
        if (i==2)
        {
          walls[i][l] = Entity(TILEWIDTH * l, 0, background, SCALE);
        }
        else if (i==3)
        {
          walls[i][l] = Entity(TILEWIDTH * l, HEIGHT-TILEHEIGHT, background, SCALE);
        }
      }
    }

    /* std::cout << i << std::endl;
    left_wall[i] = Entity(0, i*64, background, SCALE);
    right_wall[i] = Entity(WIDTH-TILEWIDTH, i*64, background, SCALE); */
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
    }
    window.clear();

// render entities

    // render through wall array
    for (int i = 0; i < 4; i++)
    {
      // std::cout << i << std::endl;
      // render each entity 
      // window.render(left_wall[i], 1);
      // window.render(right_wall[i], 1);
      if (i == 0 || i == 1)
      {
        for (int l=0; l < HEIGHT/TILEHEIGHT; l++)
        {
          window.render(walls[i][l], 1);
        }
      }

      if (i == 2 || i == 3)
        for (int l=0; l < WIDTH/TILEWIDTH; l++)
        {
          window.render(walls[i][l], 1);
        } 

    }
    window.display();

  }

/* clean up and quit after game loop ends */


  /* FREE ALL ALLOCATED MEMORY */
  // free(left_wall);
  // free(right_wall);

  for (int i=0; i < 4; i++)
  {
    free(walls[i]);
  }
  free(walls);
  
  window.cleanUp();
  SDL_Quit();

  return 0;


}