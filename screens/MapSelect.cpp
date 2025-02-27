#include "MapSelect.h"

MapSelect MapSelect::_mapSelect;

MapSelect* MapSelect::get() {
    return &_mapSelect;
}

void MapSelect::enter() {
    AssetManager *am = AssetManager::get();
    am->loadTexture("bg", "media/menu_bg.jpg");
}

void MapSelect::exit() {
    SDL_DestroyTexture(_bg);
    SDL_DestroyTexture(_spriteSheet);
}


void MapSelect::handleInput(SDL_Event event) {
    AudioManager *am =  AudioManager::get();
    switch (event.type) {
        case SDL_QUIT:
            //we should get to an exit state
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_RIGHT) {
                _nextScreen = MainMenu::get();
            }
    }
}

void MapSelect::update(Screen **nextScreen) {
    if (_nextScreen != nullptr) {
        *nextScreen = _nextScreen;
        _nextScreen = nullptr;
    }

    //do other update stuff
}

void MapSelect::render() {

}
