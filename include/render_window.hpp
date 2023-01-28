#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <entity.hpp>

// use p_ to indicate a parameter

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(Entity &p_entity, int scale);
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};