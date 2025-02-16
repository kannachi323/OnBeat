#include "Game.h"

Game::Game() : _window(nullptr), _renderer(nullptr), _currentScreen(nullptr), _nextScreen(nullptr) {
    initVideo();
    initAudio();
    initStyles();
    initAssets();
}

Game::~Game() { 
    TTF_CloseFont(_font);   
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::initStyles() {
    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init ttf");
    }
    _font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 24);
    if (!_font) {
        std::cout << "error opening font" << std::endl;
    }
}


void Game::initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 64) < 0) {
        std::cerr << "Failed to initialize SDL_mixer" << std::endl;
        return;
    }
   AudioManager *audioManager = AudioManager::get();
   audioManager->init();
}

void Game::initVideo() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init video");
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    _window = SDL_CreateWindow("OnBeat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating window: %s", SDL_GetError());
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating renderer: %s", SDL_GetError());
        SDL_DestroyWindow(_window);
        return;
    }
}

void Game::initAssets() {
    AssetManager *am = AssetManager::get();
    am->init(_window, _renderer);
}

void Game::changeScreen() {
    _currentScreen->exit();
    _nextScreen->enter();
    _currentScreen = _nextScreen;
    _nextScreen = nullptr;
}

void Game::runGame() {
    _currentScreen = MainMenu::get();
    if (_currentScreen == nullptr) {
        std::cout << "nigga" << std::endl;
        return;
    }
    _currentScreen->enter();

    while (_currentScreen != nullptr) {
        while (SDL_PollEvent(&_event)) {
            _currentScreen->handleInput(_event);
            if (_event.type == SDL_QUIT) {
                _currentScreen = nullptr;
            }
        }

        _currentScreen->update(&_nextScreen);

        
        if( _nextScreen != nullptr) {
            changeScreen();
        }

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

        
        
        SDL_RenderClear(_renderer);

        std::cout << "got after reset" << std::endl;

        _currentScreen->render();

        std::cout << "got it to render" << std::endl;

        SDL_RenderPresent(_renderer);
    }
     
   
}
