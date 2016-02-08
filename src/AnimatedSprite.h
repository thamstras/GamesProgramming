#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "SpriteAnim.h"

using std::string;



class AnimatedSprite
{
public:
	AnimatedSprite(SDL_Texture* tex);
	AnimatedSprite(const AnimatedSprite& other);
	AnimatedSprite& operator=(const AnimatedSprite& other);
	~AnimatedSprite();

	void update(double simLength);
	void render(SDL_Renderer *renderer);
	int createAnimFrame(int left, int top, int width, int height);
	int createAnim(int * frames, int nFrames);
	void setFrameRate(int frameRate);
	void playAnim(int amim);
	void moveSprite(int x, int y);
	void scaleSprite(float xScale, float yScale);

private:
	

	int _x;
	int _y;
	float _scaleX;
	float _scaleY;
	int _frameRate;
	SDL_Texture *_tex;
	std::vector<SDL_Rect> _frameList;
	std::vector<SpriteAnim> _animList;
	int _currAnim;
	//float _animProgress;
	int _animFrame;
	int _currFrame;
	SDL_Rect _currFrameRect;
};

