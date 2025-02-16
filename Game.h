#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "AudioManager.h"
#include "MainMenu.h"
#include "AssetManager.h"

class Game {
public:
    Game();
    ~Game();
    void initVideo();
    void initAudio();
    void initMaps();
    void initStyles();
    void initScreens();
    void initAssets();
    void runGame();
    void changeScreen();
    


private:
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    Screen *_currentScreen;
    Screen *_nextScreen;
};

