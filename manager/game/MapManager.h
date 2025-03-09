#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> 

struct MapConfig {
    const char* FILE_NAME;
    const char* MAP_ID;
    uint8_t BPM;
    uint8_t DIFFICULTY;
    const char* MAPPER;
    const char* TITLE;
    const char* ARTIST;
    const char* LENGTH;
};

class MapManager {
public:
    MapManager();
    ~MapManager();
    MapConfig* loadMap(const char* fileName);
    int createMap(MapConfig* mapConfig);
    std::vector<MapConfig*> getMaps();
    void printMap(MapConfig* mapConfig);

private:
    FILE* _mapFp; // the current map we're looking at

    MapConfig* _mapConfig; // current map we're looking at

    std::vector<MapConfig*> _maps; // a list of all the maps in disk
};