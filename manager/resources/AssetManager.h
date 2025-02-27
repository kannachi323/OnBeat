#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../graphics/RenderManager.h"
#include <unordered_map>


class AssetManager {
public:
    static AssetManager* get();

    void init(SDL_Window *window, SDL_Renderer *renderer);
    void cleanUp();
    
    void loadTexture(const std::string& key, const std::string& path);
   
    void loadFont(const std::string& key, const std::string& path, int size);
    void loadFontTexture(const std::string& fontKey, const std::string& textKey, const std::string& text, SDL_Color color);

    SDL_Texture* getTexture(const std::string& key);

private:
    static AssetManager _am;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    std::unordered_map<std::string, SDL_Texture*> _textures;
    std::unordered_map<std::string, TTF_Font*> _fonts;

};