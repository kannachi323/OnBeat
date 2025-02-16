#include "AssetManager.h"

AssetManager AssetManager::_am;

AssetManager* AssetManager::get() {
    return &_am;
}

void AssetManager::init(SDL_Window *window, SDL_Renderer *renderer) {
    _window = window;
    _renderer = renderer;
}

void AssetManager::loadTexture(const std::string& key, const std::string& path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return;
    }
    if (_renderer == nullptr) {
        std::cerr << "Renderer is null" << std::endl;
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture from surface: " << path << std::endl;
        return;
    }

    _textures[key] = texture;
    SDL_FreeSurface(surface);
    std::cout << "Finished Loading texture: " << path << std::endl;
    return;
}

void AssetManager::renderTexture(const std::string& key, int x, int y, int w, int h) {
    SDL_Texture *texture = _textures[key];
    if (texture == nullptr) {
        std::cerr << "Failed to render texture: " << key << std::endl;
        return;
    }

    SDL_Rect destRect = {x, y, w, h};
    SDL_RenderCopy(_renderer, texture, NULL, &destRect);
    std::cout << "Finished Rendering texture: " << key << std::endl;
}

void AssetManager::cleanUp() {
    for (auto& texture : _textures) {
        SDL_DestroyTexture(texture.second);
    }
    _textures.clear();
}