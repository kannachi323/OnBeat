#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "MainMenu.h"
#include "ScreenManager.h"

class Game {
public:
    Game();
    ~Game();
    void initVideo();
    void initAudio();
    void initMaps();
    void initStyles();
    void initScreens();
    void runGame();
    void showScreen();

private:
    TTF_Font *_font;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    ScreenManager *_sm;
};

