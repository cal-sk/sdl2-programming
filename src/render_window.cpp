#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

#include <render_window.hpp>
#include <entity.hpp>


// render the window
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
// check null values
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL){
        std::cout << "Error with window" << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
}

// texture loading
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;

    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL){
        std::cout << "Error loading texture " << IMG_GetError() << std::endl;
    }
    return texture;
}

// render textures
void RenderWindow::render(Entity &p_entity, int scale)
{
    // 
    SDL_Rect src;
    src.x = p_entity.getTileRect().x;   
    src.y = p_entity.getTileRect().y;
    src.w = p_entity.getTileRect().w;
    src.h = p_entity.getTileRect().h;
    
    //
    SDL_Rect dst;
    dst.x = p_entity.GetX();
    dst.y = p_entity.GetY();
    dst.w = p_entity.getTileRect().w * scale;
    dst.h = p_entity.getTileRect().h * scale;

    // render the texture to the screen
    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

// render the player
void RenderWindow::render_player(Player &p_player, int scale, SDL_RendererFlip flip)
{
    // 
    SDL_Rect src;
    src.x = p_player.getPlayerRect().x;   
    src.y = p_player.getPlayerRect().y;
    src.w = p_player.getPlayerRect().w;
    src.h = p_player.getPlayerRect().h;
    
    //
    SDL_Rect dst;
    dst.x = p_player.GetX();
    dst.y = p_player.GetY();
    dst.w = p_player.getPlayerRect().w * scale;
    dst.h = p_player.getPlayerRect().h * scale;

    // render the texture to the screen
    // use render copy ex to flip the texture 
    SDL_RenderCopyEx(renderer, p_player.getTexture(), &src, &dst,0, NULL, flip);
}
// clear renderer
void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

// display the renderer to window
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

// prevents memory leaks or other issues after the window is closed
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}