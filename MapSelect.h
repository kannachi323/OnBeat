#pragma once
#include "Screen.h"
#include "AssetManager.h"
#include "MainMenu.h"
#include <iostream>
#include <functional>
#include <SDL.h>
#include <SDL_image.h>


class MapSelect : public Screen {
public: 
    static MapSelect* get();

    void handleInput(SDL_Event event) override;
    void update(Screen **nextScreen) override;
    void render() override;
    void enter() override;
    void exit() override;

private:
    static MapSelect _mapSelect;

    
    //some render processes
    void Background();
   

    SDL_Texture *_bg;
    SDL_Texture *_spriteSheet;
    SDL_Renderer *_renderer;
    SDL_Window *_window;
    Screen *_nextScreen;
    
};

