#pragma once

#include <SDL2/SDL.h>

class SpriteAnim
{
public:
	SpriteAnim();
	SpriteAnim(int nFrames, SDL_Rect *frames);
	SpriteAnim(const SpriteAnim& other);
	~SpriteAnim();
	SpriteAnim& operator=(const SpriteAnim& other);
	int nFrames;
	SDL_Rect *frames;
};

