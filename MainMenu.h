#include "Screen.h"
#include "ScreenManager.h"
#include "MapSelect.h"
#include "Transitions.h"
#include <iostream>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


class MainMenu : public Screen {
public: 
    MainMenu(SDL_Window* window, SDL_Renderer* renderer);
    ~MainMenu();
    void handleInput(SDL_Event event) override;
    void update(float deltaTime) override;
    void render() override;
    void enter() override;
    void exit() override;
    bool isInTransition() override;

    static void renderFunc(void *context) {
        MainMenu* menu = static_cast<MainMenu*>(context);
        menu->Background();
    }

private:
    void Background();

    
    SDL_Texture *_bg;
    SDL_Texture *_spriteSheet;
    SDL_Renderer *_renderer;
    SDL_Window *_window;

    bool _isInTransition;
    bool _isEntering;
    
};

