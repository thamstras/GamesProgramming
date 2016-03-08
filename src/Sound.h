#pragma once

#include <map>
#include <string>
#include <iostream>

#include <SDL_mixer.h>

class Sound
{
public:
	Sound();
	~Sound();

	void initSound();
	void loadSounds();

	int loadSound(std::string path, std::string name);

private:
	std::map<std::string, Mix_Chunk*> chunkMap;
	Mix_Music* music;
};

