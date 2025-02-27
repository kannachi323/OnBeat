#include "AssetManager.h"

AssetManager AssetManager::_am;

AssetManager* AssetManager::get() {
    return &_am;
}

void AssetManager::init(SDL_Window *window, SDL_Renderer *renderer) {
    _renderer = renderer;
}

void AssetManager::cleanUp() {
    for (auto& texture : _textures) {
        SDL_DestroyTexture(texture.second);
    }
    _textures.clear();
}

void AssetManager::loadFont(const std::string& key, const std::string& path, int size) {
    TTF_Font *font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << path << std::endl;
        return;
    }
    _fonts[key] = font;
    std::cout << "Finished Loading font: " << path << std::endl;
}

void AssetManager::loadFontTexture(const std::string& fontKey, const std::string& textKey,
    const std::string& text, SDL_Color color) {
    
    TTF_Font *font = _fonts[fontKey];

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

    _textures[textKey] = texture;
    SDL_FreeSurface(surface);
    std::cout << "Finished Loading font texture: " << text << std::endl;
}

void AssetManager::loadTexture(const std::string& key, const std::string& path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image: " << path << std::endl;
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

SDL_Texture* AssetManager::getTexture(const std::string& key) {
    return _textures[key];
}
