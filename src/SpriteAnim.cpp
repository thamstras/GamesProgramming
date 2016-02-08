#include "SpriteAnim.h"



SpriteAnim::SpriteAnim()
{
	this->nFrames = 0;
	this->frames = new SDL_Rect[0];
}

SpriteAnim::SpriteAnim(int nFrames, SDL_Rect * frames)
{
	this->nFrames = nFrames;
	this->frames = new SDL_Rect[nFrames];
	for (int i = 0; i < nFrames; i++)
	{
		this->frames[i] = frames[i];
	}
}

SpriteAnim::SpriteAnim(const SpriteAnim & other)
{
	this->nFrames = other.nFrames;
	this->frames = new SDL_Rect[other.nFrames];
	for (int i = 0; i < nFrames; i++)
	{
		this->frames[i] = other.frames[i];
	}
}

SpriteAnim::~SpriteAnim()
{
	delete[] frames;
}

SpriteAnim & SpriteAnim::operator=(const SpriteAnim & other)
{
	if (this != &other)
	{
		if (this->nFrames != other.nFrames)
		{
			delete[] frames;
			this->nFrames = other.nFrames;
			this->frames = new SDL_Rect[other.nFrames];
		}
		for (int i = 0; i < nFrames; i++)
		{
			this->frames[i] = other.frames[i];
		}
	}
	return *this;
}
