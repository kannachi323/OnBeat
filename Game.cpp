#include "Game.h"

Game::Game() : _window(nullptr), _renderer(nullptr), _currentScreen(nullptr), _nextScreen(nullptr) {
    initVideo();
    initRenderer();
    initAudio();
    initAssets();
    initMaps();
}

Game::~Game() { 
    //TODO: clean up all resources through their respective managers
    if (_currentScreen != nullptr) {
        _currentScreen->exit();
    }
    if (_nextScreen != nullptr) {
        _nextScreen->exit();
    }
    AssetManager *am = AssetManager::get();
    am->cleanUp();
    AudioManager *audioManager = AudioManager::get();
    audioManager->cleanUp();
    TTF_CloseFont(_font);   
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
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
    WindowManager *windowManager = WindowManager::get();
    windowManager->init();
    windowManager->getWindow(&_window);
}

void Game::initRenderer() {
    RenderManager *renderManager = RenderManager::get();
    renderManager->init(_window);
    renderManager->getRenderer(&_renderer);
}

void Game::initAssets() {
    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init ttf");
    }
    AssetManager *am = AssetManager::get();
    
    am->init(_window, _renderer);

    am->loadFont("arial", "media/Arial.ttf", 24);
}

void Game::initMaps() {
    
}

void Game::changeScreen() {
    _currentScreen->exit();
    _nextScreen->enter();
    _currentScreen = _nextScreen;
    _nextScreen = nullptr;
}

void Game::runGame() {
    _currentScreen = MapGrid::get();
    if (_currentScreen == nullptr) {
        std::cout << "no screen available" << std::endl;
        return;
    }
    _currentScreen->enter();

    while (_currentScreen != nullptr) {
        while (SDL_PollEvent(&_event)) {
            _currentScreen->handleInput(_event);
            if (_event.type == SDL_QUIT) {
                _currentScreen = nullptr;
                std::cout << "quit" << std::endl;
                break;
            }
        }

        _currentScreen->update(&_nextScreen);

        
        if( _nextScreen != nullptr) {
            changeScreen();
        }

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

        
        
        SDL_RenderClear(_renderer);


        _currentScreen->render();


        SDL_RenderPresent(_renderer);
    }
}
