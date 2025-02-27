#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <filesystem>
#include <memory>
#include "manager/resources/AudioManager.h"
#include "manager/resources/AssetManager.h"
#include "manager/graphics/RenderManager.h"
#include "manager/game/MapManager.h"
#include "manager/game/NotesManager.h"
#include "screens/MapGrid.h"


class Game {
public:
    Game();
    ~Game();
    void initVideo();
    void initRenderer();
    void initAudio();
    void initMaps();
    void initAssets();
    void initScreens();
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

