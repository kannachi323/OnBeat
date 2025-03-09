#pragma once
#include <SDL.h>
#include <iostream>

/*
Allows easy access to the get our current window and its properties.
Instead of passing in reference to window we can just call these class funcs to get props
*/

class WindowManager {
    public:
        static WindowManager* get();
        void init();
        void cleanUp();
        void getWindow(SDL_Window** window);
        void getWindowSize(int* w, int* h);
        void toggleFullscreen();
    
    private:
        static WindowManager _windowManager;
        SDL_Window* _window;
};