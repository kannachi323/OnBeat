#include "Transitions.h"

void fadeTransition(SDL_Renderer* renderer, SDL_Window* window, 
    float fadeSpeed, int fadeDirection, 
    RenderFunc renderFunc, void* context
) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_FRect fadeOverlay = {0, 0, (float)w, (float)h};

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    // Initialize alpha (for fade-in alpha starts at 0, for fade-out at 255)
    float alpha = fadeDirection == 1 ? 0 : 255;

    Uint64 lastTime = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    // Continue until we reach the desired end alpha (0 for fade-out, 255 for fade-in)
    while ((fadeDirection == 1 && alpha < 255) || (fadeDirection == -1 && alpha > 0)) {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        float deltaTime = (currentTime - lastTime) / (float)frequency;

        // Update alpha based on the fade direction
        alpha += fadeSpeed * deltaTime * fadeDirection;

        if (fadeDirection == 1 && alpha > 255) alpha = 255;
        if (fadeDirection == -1 && alpha < 0) alpha = 0;

        lastTime = currentTime;
        
        // Render the fade effect
        SDL_RenderClear(renderer);
        renderFunc(context);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, (Uint8)alpha);
        SDL_RenderFillRect(renderer, &fadeOverlay);
        
        SDL_RenderPresent(renderer);
    }
}