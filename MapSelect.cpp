#include "MapSelect.h"

MapSelect::MapSelect(SDL_Window* window, SDL_Renderer* renderer) : _bg(nullptr), _spriteSheet(nullptr), _renderer(renderer),
_window(window), _isInTransition(false) {
    _bg = IMG_LoadTexture(_renderer, "media/dark_bg.jpg");
    if (!_bg) {
        std::cerr << "Failed to load bg" << std::endl;
        return;
    }
    _spriteSheet = IMG_LoadTexture(_renderer, "assets/skins/default");
    _isInTransition = true;
    enter();
    _isInTransition = false;
}

MapSelect::~MapSelect() {
    

}

void MapSelect::handleInput(SDL_Event event) {
    if (_isInTransition) return;
    ScreenManager &sm = ScreenManager::getInstance();
    sm.printScreens();
    switch (event.type) {
        case SDL_EVENT_QUIT:
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_RIGHT) {
                _isInTransition = true;
                exit();
                _isInTransition = false;
                sm.popScreen();
            }
    
    }
    
}

void MapSelect::update(float deltaTime) {
    std::cout << "Updating Main Menu" << std::endl;
}

void MapSelect::render() {
    SDL_RenderClear(_renderer);

    Background();


    SDL_RenderPresent(_renderer);
}

void MapSelect::enter() {
    _isInTransition = true;
    fadeTransition(_renderer, _window, 200, -1, &MapSelect::renderFunc, this); 
    _isInTransition = false;
}

void MapSelect::exit() {
    _isInTransition = true;
    fadeTransition(_renderer, _window, 200, 1, &MapSelect::renderFunc, this); 
    _isInTransition = false;
}

bool MapSelect::isInTransition() {
    return _isInTransition;
}

//Helper Funcs
void MapSelect::Background() {
    SDL_FRect srcRect = {0, 0, 2048, 2048};
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    
    SDL_FRect dstRect = {0, 0, (float)w, (float)h};

    SDL_RenderTexture(_renderer, _bg, &srcRect, &dstRect);
}



