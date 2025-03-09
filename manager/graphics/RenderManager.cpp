#include "RenderManager.h"

RenderManager RenderManager::_rm;

RenderManager* RenderManager::get() {
    return &_rm;
}

void RenderManager::init(SDL_Window *window) {
    _renderer = SDL_CreateRenderer(window, -1, 0);
    if (!_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating renderer: %s", SDL_GetError());
        return;
    }
}

void RenderManager::cleanUp() {
  
}

void RenderManager::getRenderer(SDL_Renderer** renderer) {
    *renderer = _renderer;
}

void RenderManager::renderLine(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
};

void RenderManager::renderRectOutline(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(_renderer, &rect);
};

void RenderManager::renderRectFill(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(_renderer, &rect);
};

void RenderManager::renderCircleOutline(int x, int y, int radius) {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(_renderer, x + dx, y + dy);
            }
        }
    }
};

void RenderManager::renderTexture(SDL_Texture *texture, int x, int y, int w, int h) {
    if (texture == nullptr) {
        return;
    }
    SDL_Rect destRect = {x, y, w, h};
    SDL_RenderCopy(_renderer, texture, NULL, &destRect);
}