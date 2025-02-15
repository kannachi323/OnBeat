#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "NotesManager.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CIRCLE_RADIUS = 30;
const int SPEED = 3; // Speed of movement
static Mix_Chunk *g_wave = nullptr;

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontal distance from center
            int dy = radius - h; // Vertical distance from center
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void createMap() {
    NotesManagerConfig nmcf = {"example.nm", 120, 9};
    NotesManager nm(&nmcf);
   
    Note note = {LANE_2, LEFT, QUARTER, 0};  // Start with the first quarter note at timestamp 0
    for (uint8_t i = 0; i < 4; ++i) {
        nm.addNote(note);
        note.timestamp = nm.getNextNoteTimestamp();
    }

    // 8 Eighth Notes
    note = {LANE_4, RIGHT, EIGHTH, note.timestamp};  // Start with the first eighth note at the last timestamp
    for (uint8_t i = 0; i < 8; ++i) {
        nm.addNote(note);
        note.timestamp = nm.getNextNoteTimestamp();
    }

    // 16 Sixteenth Notes
    note = {LANE_2, LEFT, TRIPLET, note.timestamp};  // Start with the first sixteenth note at the last timestamp
    for (uint8_t i = 0; i < 12; ++i) {
        nm.addNote(note);
        note.timestamp = nm.getNextNoteTimestamp();
    } 
    note = {LANE_1, LEFT, SIXTEENTH, note.timestamp};
    for (uint8_t i = 0; i < 16; ++i) {
        nm.addNote(note);
        note.timestamp = nm.getNextNoteTimestamp();
    }
    //downbeat
    nm.addNote(note);
    
    nm.saveNotesFile();

    nm.readNotesFile();
    nm.printNotes();
    nm.playNotes();    
}

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
    int width, height;
    
    createMap();
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init video");
        return 2;
    }

    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with init ttf");
    }
    if (!SDL_CreateWindowAndRenderer("OnBeat", 800, 600, 0, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "issues with render and window");
        return 3;
    }

    SDL_GetWindowSize(window, &width, &height);
    
    TTF_Font* font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 24);
    if (!font) {
        std::cout << "error opening font" << std::endl;
    }
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Score: \0", 0, textColor);
    if (!textSurface) {
        std::cout << "something went wrong with rendering text" << std::endl;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    
    float textWidth, textHeight;
    SDL_GetTextureSize(textTexture, &textWidth, &textHeight);
    // render a simple white line down the middle of the screen
    bool running = true;
    int x = 0;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, NULL);

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, width / 2, 0, width / 2, height);

        DrawCircle(renderer, x, WINDOW_HEIGHT / 2, CIRCLE_RADIUS);

        SDL_FRect destRect = {800.0f - textWidth / 2, 600.0f - textHeight / 2, textWidth, textHeight};
        SDL_RenderTexture(renderer, textTexture, NULL, &destRect);

        x += SPEED;
        if (x - CIRCLE_RADIUS > WINDOW_WIDTH) {
            x = -CIRCLE_RADIUS; // Reset position when off-screen
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);


    }
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
