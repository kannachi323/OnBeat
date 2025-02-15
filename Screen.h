#pragma once
#include <vector>
#include <iostream>
#include <SDL3/SDL.h>
#include <memory>

class Screen {
public: 
    virtual void handleInput(SDL_Event event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual bool isInTransition() = 0;
    
    virtual ~Screen() = default;
};



