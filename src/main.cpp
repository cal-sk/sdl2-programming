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


/* 
NOTES: CREATE LOGIC TO STOP THE PLAYER AFTER COLLISIONS, MAYBE RAYCAST FUNCTIONS?
        CREATE TILEMAP SYSTEM AND ADD COLLISION LOOPS

*/

RenderWindow window("Topdown Roguelike", WIDTH, HEIGHT);

/* Delta Time */
Uint64 lastTick = 0;
Uint64 currentTick = SDL_GetPerformanceCounter();
double deltaTime = 0;

/* 2D ARRAY FOR THE WALLS */
Entity** walls = (Entity**)malloc(sizeof(Entity*) * 4);
SDL_RendererFlip playerFlip = SDL_FLIP_NONE;

/* LOAD TEXTURES HERE */

SDL_Texture* wall_texture = window.loadTexture("res/tiles.png");
SDL_Texture* world_background = window.loadTexture("res/world_background.png");
SDL_Texture* player_texture = window.loadTexture("res/player.png");

/* DEFINE ENTITIES AND PLAYER HERE */
Player player(128, 128, player_texture, SCALE);

Entity background = Entity(0,0, world_background, 8);

SDL_Event event;

bool gameRunning = true;

// createwalls function

void createWalls()
{
  // LOOP FOR 2D DYNAMICALLY ALLOCATED ARRAY - i=0 is left i=1 is right i=2 is top i =3
  for (int i=0; i < 4; i++)
  {
    // LEFT AND RIGHT WALLS
    if (i==0 || i==1)
    {
      // SUBTRACT 1 FOR CORNERS
      // allocate space for the amount of tiles around the edge
      walls[i] = (Entity*)malloc(sizeof(Entity) * (HEIGHT/TILEHEIGHT - 1));

      for (int l=0; l < (HEIGHT/TILEHEIGHT); l++)
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
}

// de-initialization function

void deInit()
{
  for (int i=0; i < 4; i++)
  {
    free(walls[i]);
  }
  free(walls);
  
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
    player.move(TILEHEIGHT, event);
  }
}

// graphics function
 
void graphics()
{

  window.render(background, 10);

    // RENDER MEMBERS OF THE WALL ARRAY
  for (int i = 0; i < 4; i++)
  {
    // render left and right walls
    if (i == 0 || i == 1)
    {
      for (int l=0; l < HEIGHT/TILEHEIGHT; l++)
      {
      
        window.render(walls[i][l], 1);
      }
    }
    // render top and bottom walls
    if (i == 2 || i == 3)
      for (int l=0; l < HEIGHT/TILEHEIGHT; l++)
      {
        window.render(walls[i][l], 1);
      } 
  }
  window.render_player(player, 1, player.playerFlip);
}

// collision function

void checkCollisions()
{
  // loop through list of tiles to check for collisions  
  for (int i=0; i<4; i++)
  {
    // loop through each tile of each wall
    for (int l=0; l< HEIGHT/TILEHEIGHT; l++)
    {
      // check collisions 
      player.isColliding(walls[i][l]);
      // debug code
      if (player.getCollidingStatus() == true)
      {

        // extra code for debugging
        std::cout << "row: " << i+1 << std::endl;
        std::cout << "tile: " << l << std::endl;
        std::cout << walls[i][l].GetY() << ", " << walls[i][l].GetX() << std::endl;
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
  createWalls();


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
    if (deltaTime < 1000/60)
    {
      SDL_Delay(1000/60 - deltaTime);
    }

  }

/* clean up and quit after game loop boolean is false */

  /* FREE ALL ALLOCATED MEMORY HERE */
  deInit();

  return 0;


}