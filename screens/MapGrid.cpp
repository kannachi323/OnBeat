#include "MapGrid.h"

MapGrid MapGrid::_mapGrid;

MapGrid* MapGrid::get() {
    return &_mapGrid;
}

void MapGrid::enter() {
    _assetManager = AssetManager::get();
    _assetManager->loadTexture("dark_bg", "media/dark_bg.jpg");
    _assetManager->loadTexture("hit-circle-fill", "media/hit-circle-fill.png");
    
    SDL_Color color = {255, 255, 255, 255};
    _assetManager->loadFontTexture("arial", "score-label", "Score: 0", color);

    _audioManager = AudioManager::get();
    _audioManager->playMusic("media/jashin.mp3");

    _renderManager = RenderManager::get();

    _notesManager = new NotesManager();
    _notesManager->loadNotes("maps/jashin/jashin.notes");
    std::cout << "Loaded notes" << std::endl;
    _notesManager->printNotes();
}

void MapGrid::exit() {
    _audioManager->stopMusic();
}

void MapGrid::handleInput(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            //we should get to an exit state
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                    _startTime = SDL_GetTicks();
                case SDLK_q:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_w:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_e:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_f:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_p:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_o:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_i:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
                case SDLK_j:
                    if (event.key.repeat == 0) {
                        _audioManager->playSound("media/hit.wav");
                    }
                    break;
            }
            break;
    }
}

void MapGrid::update(Screen** nextScreen) {
    if (_nextScreen != nullptr) {
        *nextScreen = _nextScreen;
        _nextScreen = nullptr;
    }

    //do other update stuff
    
}

void MapGrid::render() {
    renderGrid(800, 600);
    renderScore(800, 600);
    renderNotes();
}

void MapGrid::renderNotes() {
    SDL_Texture* hitCircleFill = _assetManager->getTexture("hit-circle-fill");
    _notesManager->printNotes();
    
}

void MapGrid::renderGrid(int width, int height){
    SDL_Texture* darkBg = _assetManager->getTexture("dark_bg");
    _renderManager->renderTexture(darkBg, 0, 0, width, height);

    int posX = width / 2;

    _renderManager->renderLine(posX, 0, posX, height);

    int spaceY = height / 4;
    for (int posY = height / 8; posY < height; posY += spaceY) {
        _renderManager->renderLine(posX - 20, posY, posX + 20, posY);
    }
}

void MapGrid::renderScore(int width, int height) {
    SDL_Texture* scoreLabel = _assetManager->getTexture("score-label");

    _renderManager->renderRectOutline(width - 75, 0, 64, 32);
    _renderManager->renderTexture(scoreLabel, width - 75, 0, 64, 32);
}