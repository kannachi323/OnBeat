#include "Game.h"

Game::Game() : _window(nullptr), _renderer(nullptr), _sm(nullptr) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init video");
        return;
    }
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init ttf");
    }
    initVideo();
    initStyles();
}

Game::~Game() { 
    TTF_CloseFont(_font);   
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::initStyles() {
    
    _font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 24);
    if (!_font) {
        std::cout << "error opening font" << std::endl;
    }
}


void Game::initAudio() {
   
}

void Game::initVideo() {
    _window = SDL_CreateWindow("OnBeat", 800, 600, 0);
    if (!_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating window: %s", SDL_GetError());
        return;
    }

    _renderer = SDL_CreateRenderer(_window, NULL);
    if (!_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating renderer: %s", SDL_GetError());
        SDL_DestroyWindow(_window);
        return;
    }

}

void Game::runGame() {
    _sm = &ScreenManager::getInstance();
    if (!_sm) {
        std::cerr << "ScreenManager is not initialized!" << std::endl;
        return;
    }
    
    std::cout << "About to create Main Menu" << std::endl;
    Screen *mainMenu = new MainMenu(_window, _renderer);
    if (!mainMenu) {
        std::cerr << "Failed to allocate memory for MainMenu" << std::endl;
        return;
    }

    std::cout << "Main Menu created" << std::endl;
    _sm->pushScreen(mainMenu);
    std::cout << "Main Menu pushed" << std::endl;
    


    SDL_Event event;
    bool running = true;
    Screen *currentScreen = nullptr;
    while (running) {
        currentScreen = _sm->getCurrentScreen();
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                std::cout << "Quitting" << std::endl;
                running = false;
                break;
            }
            
            currentScreen->handleInput(event);
            
            
        }

        // Render the current screen
        _sm->showScreen();
        std::cout << "Showing Screen" << std::endl;

    }
    
    std::cout << "About to delete ScreenManager" << std::endl;
    
   
}
