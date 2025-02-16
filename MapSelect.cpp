#include "MapSelect.h"

MapSelect MapSelect::_mapSelect;

MapSelect* MapSelect::get() {
    return &_mapSelect;
}

void MapSelect::enter() {
    AssetManager *am = AssetManager::get();
    am->loadTexture("bg", "media/dark_bg.jpg");
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
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_q:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_w:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_e:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_f:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_p:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_o:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_i:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
                case SDLK_j:
                    if (event.key.repeat == 0) {
                        am->playSound("media/drum-hitnormal.wav");
                    }
                    break;
            }
            break;
            
    
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
    AssetManager *am = AssetManager::get();
    am->renderTexture("bg", 0, 0, 800, 600);

    //do other render stuff
    std::cout << "Rendering main menu" << std::endl;

}

