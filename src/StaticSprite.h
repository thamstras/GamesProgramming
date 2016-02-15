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

	void render(SDL_Renderer* ren);

private:
	int _x;
	int _y;
	int _w;
	int _h;
	float _scaleX;
	float _scaleY;

	SDL_Texture* _tex;
};

