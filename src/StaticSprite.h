#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "SpriteAnim.h"

class StaticSprite
{
public:
	StaticSprite(std::string path, SDL_Renderer* ren);
	StaticSprite(const StaticSprite& other);
	~StaticSprite();

	void update(double simLength);
	void render(SDL_Renderer* ren);

	int getXPos();
	int getYPos();
	float getXScale();
	float getYScale();
	void setSrcRect(SDL_Rect newSrc);
	void moveSprite(int x, int y);
	void scaleSprite(float xScale, float yScale);

private:
	int _x;
	int _y;
	float _scaleX;
	float _scaleY;

	SDL_Rect _srcRect;
	SDL_Texture* _tex;
};

