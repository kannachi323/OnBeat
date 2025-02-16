#include "AudioManager.h"


AudioManager AudioManager::_audioManager;

AudioManager* AudioManager::get() {
    return &_audioManager;
}

void AudioManager::init() {
    
}

void AudioManager::playMusic(const std::string& filePath){
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music: " << filePath << std::endl;
        return;
    }
    Mix_PlayMusic(music, -1);
}

void AudioManager::playSound(const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        std::cerr << "Failed to load sound: " << filePath << std::endl;
        return;
    }
    Mix_PlayChannel(-1, sound, 0);
}

void AudioManager::stopMusic() {

}

void AudioManager::pauseMusic() {}

void AudioManager::resumeMusic() {}

void AudioManager::setVolume(float volume) {}

void AudioManager::free() {}



