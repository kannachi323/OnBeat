#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>


class AssetManager {
public:
    static AssetManager* get();

    void init(SDL_Window *window, SDL_Renderer *renderer);
    void loadTexture(const std::string& key, const std::string& path);
    void renderTexture(const std::string& key, int x, int y, int w, int h);
    void cleanUp();
    

private:
    static AssetManager _am;
    AssetManager() : _window(nullptr), _renderer(nullptr) {}
    ~AssetManager() { cleanUp(); }
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    std::unordered_map<std::string, SDL_Texture*> _textures;

};