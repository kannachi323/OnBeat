#include "MainMenu.h"

MainMenu::MainMenu(SDL_Window* window, SDL_Renderer* renderer) : _bg(nullptr), _spriteSheet(nullptr), _renderer(renderer),
_window(window), _isInTransition(false) {
    _bg = IMG_LoadTexture(_renderer, "media/bg.jpg");
    if (!_bg) {
        std::cerr << "Failed to load bg" << std::endl;
        return;
    }
    _spriteSheet = IMG_LoadTexture(_renderer, "assets/skins/default");
    
    _isInTransition = true;
    enter();
    _isInTransition = false;
}

MainMenu::~MainMenu() {
    

}

void MainMenu::handleInput(SDL_Event event) {
    if (isInTransition()) return;
    ScreenManager &sm = ScreenManager::getInstance();
    sm.printScreens();
    switch (event.type) {
        case SDL_EVENT_QUIT:
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                
                _isInTransition = true;
                exit();
                _isInTransition = false;
                sm.pushScreen(new MapSelect(_window, _renderer));
            
            }
    
    }
    
}

void MainMenu::update(float deltaTime) {
    std::cout << "Updating Main Menu" << std::endl;
}

void MainMenu::render() {
    if (_isEntering) {
        enter();
        _isEntering = false;
    }
    if (!_isInTransition) {
        SDL_RenderClear(_renderer);

        Background();


        SDL_RenderPresent(_renderer);
    }
}

void MainMenu::enter() {
    _isInTransition = true;
    fadeTransition(_renderer, _window, 200, -1, &MainMenu::renderFunc, this); //1 fade in
    _isInTransition = false;
}

void MainMenu::exit() {
    _isInTransition = true;
    fadeTransition(_renderer, _window, 200, 1, &MainMenu::renderFunc, this); //-1 fade out
    _isInTransition = false;
}

bool MainMenu::isInTransition() {
    return _isInTransition;
}

//Helper Funcs
void MainMenu::Background() {
    SDL_FRect srcRect = {0, 0, 2048, 2048};
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    
    SDL_FRect dstRect = {0, 0, (float)w, (float)h};

    SDL_RenderTexture(_renderer, _bg, &srcRect, &dstRect);
}



