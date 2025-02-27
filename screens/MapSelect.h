#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../manager/game/MapManager.h"
#include "Screen.h"
#include "../manager/resources/AssetManager.h"
#include "../manager/resources/AudioManager.h"
#include "MainMenu.h"

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

    std::vector<MapConfig*> _mapsConfigs;
    
};

