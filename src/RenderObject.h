#pragma once

#include <SDL2/SDL.h>
#include <string>
class RenderObject
{
public:
	RenderObject();
	virtual ~RenderObject();
	virtual void update(double simLength) = 0;
	virtual void render(SDL_Renderer* ren) = 0;
	std::string id;
};

