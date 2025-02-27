#pragma once
#include "Screen.h"
#include "../manager/resources/AssetManager.h"
#include "../manager/resources/AudioManager.h"
#include "MapSelect.h"
#include <iostream>
#include <functional>
#include <SDL.h>
#include <SDL_image.h>


class MainMenu : public Screen {
public: 
    static MainMenu* get();

    void handleInput(SDL_Event event) override;
    void update(Screen **nextScreen) override;
    void render() override;
    void enter() override;
    void exit() override;

private:
    static MainMenu _mainMenu;

    
    //some render processes
    void Background();
   
    Screen *_nextScreen;
    
};

