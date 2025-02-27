#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Screen.h"
#include "../manager/resources/AssetManager.h"
#include "../manager/resources/AudioManager.h"
#include "../manager/graphics/RenderManager.h"
#include "../manager/game/MapManager.h"
#include "../manager/game/NotesManager.h"

class MapGrid : public Screen {
    public: 
        static MapGrid* get();
    
        void handleInput(SDL_Event event) override;
        void update(Screen **nextScreen) override;
        void render() override;
        void enter() override;
        void exit() override;
    
    private:
        static MapGrid _mapGrid;
        
        AudioManager* _audioManager;
        AssetManager* _assetManager;
        RenderManager* _renderManager;
        NotesManager* _notesManager;
    
        //some render processes
        void renderGrid(int width, int height);
        void renderScore(int width, int height);
        void renderNotes();
       
        Screen *_nextScreen;

        uint16_t _startTime;
        
};