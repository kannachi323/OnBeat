#pragma once
#include <SDL.h>
#include <SDL_image.h>


class RenderManager {
    public:
        static RenderManager* get();

        void init(SDL_Window* window);
        void cleanUp();
        void getRenderer(SDL_Renderer** renderer);
        void renderLine(int x1, int y1, int x2, int y2);
        void renderRectOutline(int x, int y, int w, int h);
        void renderRectFill(int x, int y, int w, int h);
        void renderCircleOutline(int x, int y, int radius);
        void renderTexture(SDL_Texture *texture, int x, int y, int w, int h);
        
        

    private:
        static RenderManager _rm;
        SDL_Renderer* _renderer;
};