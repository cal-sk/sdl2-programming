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
    src.x = p_entity.getCurrentFrame().x;   
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;
    
    //
    SDL_Rect dst;
    dst.x = p_entity.GetX();
    dst.y = p_entity.GetY();
    dst.w = p_entity.getCurrentFrame().w * scale;
    dst.h = p_entity.getCurrentFrame().h * scale;

    // render the texture to the screen
    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
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