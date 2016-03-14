#include "Sound.h"


Sound::Sound()
{
	std::cout << "Sound Init" << std::endl;
}

Sound::~Sound()
{
	std::cout << "Sound Destroyed" << std::endl;
}

void Sound::initSound()
{
	int mixFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
	int mixInit = Mix_Init(mixFlags);
	if ((mixInit & mixFlags) != mixFlags)
	{
		std::cout << "Error Loading SDL_mixer: " << Mix_GetError() << std::endl;
		//cleanExit(1);
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cout << "Error opening Audio: " << Mix_GetError() << std::endl;
		//cleanExit(1);
	}
}

void Sound::loadSounds()
{
	music = Mix_LoadMUS("./assets/music.mp3");
	if (music == NULL)
	{
		std::cout << "Error loading Music. Music will not play." << std::endl;
	}
	/*Mix_Chunk* sound = Mix_LoadWAV("./assets/falling.wav");
	if (sound == NULL)
	{
		std::cout << "Error loading Falling. Sound will not play." << std::endl;
	}
	Mix_Chunk* sound2 = Mix_LoadWAV("./assets/explosion.wav");
	if (sound2 == NULL)
	{
		std::cout << "Error loading Explosion. Sound will not play." << std::endl;
	}*/
}

int Sound::loadSound(std::string path, std::string name)
{
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	if (sound == NULL)
	{
		std::cout << "Error loading Falling. Sound will not play." << std::endl;
		return -1;
	}
	chunkMap.insert(std::pair<std::string, Mix_Chunk*>(name, sound));
	return 0;
}

int Sound::playSound(std::string name)
{
	Mix_Chunk* chunk = chunkMap.at(name);
	if (chunk == NULL)
	{
		std::cout << "ERROR! tried to play nonloaded sound: " << name << std::endl;
		return -1;
	}
	Mix_PlayChannel(-1, chunk, 0);
	return 0;
}
