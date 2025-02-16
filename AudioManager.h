#pragma once
#include <iostream>
#include <string>
#include <SDL_mixer.h>



class AudioManager {
public:
    static AudioManager* get();

    void init();
    void playMusic(const std::string& filePath);
    void playSound(const std::string& filePath);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setVolume(float volume);
    void free();

private:
    static AudioManager _audioManager;
};

