#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>
#include <iostream>

class Metronome
{
public:
	int ticks;
	std::string tempo;
	

	Metronome(int t) {
		ticks = t;
		tempo = "Trying to create metronome...";
	}
	

	void sendMsg();
	float trackBPM();
	void playMetronome(int n, Mix_Chunk* c);
	
	
};

