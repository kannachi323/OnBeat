#include "MapManager.h"

MapManager::MapManager() : _mapConfig(nullptr), _mapFp(nullptr) {
    _mapConfig = (MapConfig*)malloc(sizeof(MapConfig));
}

MapManager::~MapManager() {}

MapConfig* MapManager::loadMap(const char* fileName) {
    _mapFp = fopen(fileName, "rb");
    if (!_mapFp) {
        std::cout << "Error: Could not open map config" << std::endl; 
        return nullptr;
    }

    MapConfig* newMapConfig = (MapConfig*)malloc(sizeof(MapConfig));

    //read only meta data
    if (fread(newMapConfig, sizeof(MapConfig), 1, _mapFp)) {
        _maps.push_back(newMapConfig);
        _mapConfig = newMapConfig;  
    }

    fclose(_mapFp);
    _mapFp = nullptr;

    return _mapConfig;
}

int MapManager::createMap(MapConfig* mapConfig) {
    _mapFp = fopen(mapConfig->FILE_NAME, "wb");
    if (!_mapFp) {
        std::cout << "Error: Could not create map config" << std::endl; 
        return 0;
    }
    
    //write only meta data
    fwrite(mapConfig, sizeof(MapConfig), 1, _mapFp);
    
    fclose(_mapFp);
    _mapFp = nullptr;

    return 1;
};

std::vector<MapConfig*> MapManager::getMaps() {
    return _maps;
}

void MapManager::printMap(MapConfig* mapConfig) {
    std::cout << "------------------------" << std::endl;
    std::cout << "FILE_NAME: " << mapConfig->FILE_NAME << std::endl;
    std::cout << "MAP_ID: " << mapConfig->MAP_ID << std::endl;
    std::cout << "BPM: " << (int)mapConfig->BPM << std::endl;
    std::cout << "DIFFICULTY: " << (int)mapConfig->DIFFICULTY << std::endl;
    std::cout << "MAPPER: " << mapConfig->MAPPER << std::endl;
    std::cout << "TITLE: " << mapConfig->TITLE << std::endl;
    std::cout << "ARTIST: " << mapConfig->ARTIST << std::endl;
    std::cout << "LENGTH: " << mapConfig->LENGTH << std::endl;
}
