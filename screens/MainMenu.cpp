#include "MainMenu.h"

MainMenu MainMenu::_mainMenu;

MainMenu* MainMenu::get() {
    return &_mainMenu;
}

void MainMenu::enter() {
    AssetManager *am = AssetManager::get();
    am->loadTexture("bg", "media/dark_bg.jpg");

    AudioManager *audioManager = AudioManager::get();
    audioManager->playMusic("media/jashin.mp3");
}

void MainMenu::exit() {
    AssetManager *am = AssetManager::get();
    am->cleanUp();

    AudioManager *audioManager = AudioManager::get();
    audioManager->stopMusic();
}


void MainMenu::handleInput(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            //we should get to an exit state
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                _nextScreen = MapSelect::get();
            }
    
    }
}

void MainMenu::update(Screen** nextScreen) {
    if (_nextScreen != nullptr) {
        *nextScreen = _nextScreen;
        _nextScreen = nullptr;
    }

    //do other update stuff
}

void MainMenu::render() {
    


}

