#include "WindowManager.h"

WindowManager WindowManager::_windowManager;

WindowManager* WindowManager::get() {
    return &_windowManager;
}

void WindowManager::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init video");
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    _window = SDL_CreateWindow("OnBeat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_FULLSCREEN);
    if (!_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating window: %s", SDL_GetError());
        return;
    }
}

void WindowManager::cleanUp() {
    SDL_DestroyWindow(_window);
}

void WindowManager::getWindow(SDL_Window** window) {
    *window = _window;
}

void WindowManager::getWindowSize(int* w, int* h) {
    SDL_GetWindowSize(_window, w, h);
}

void WindowManager::toggleFullscreen() {
    if (SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen(_window, 0);
    } 
}

