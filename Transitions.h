#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef void (*RenderFunc)(void* context);

void fadeTransition(SDL_Renderer* renderer, SDL_Window* window, 
    float fadeSpeed, int fadeDirection,
    RenderFunc renderFunc, void* context
);