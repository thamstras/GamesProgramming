#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "SpriteAnim.h"
#include "StaticSprite.h"

using std::string;



class AnimatedSprite : public StaticSprite
{
public:
	AnimatedSprite(std::string path, SDL_Renderer* ren, std::string id);
	AnimatedSprite(const AnimatedSprite& other);
	AnimatedSprite& operator=(const AnimatedSprite& other);
	~AnimatedSprite();

	void update(double simLength);
	void render(SDL_Renderer *renderer);
	int createAnimFrame(int left, int top, int width, int height);
	int createAnim(int * frames, int nFrames);
	void setFrameRate(int frameRate);
	void playAnim(int amim);

private:
	int _frameRate;
	std::vector<SDL_Rect> _frameList;
	std::vector<SpriteAnim> _animList;
	int _currAnim;
	int _animFrame;
	int _currFrame;
	double _animTime;
};

