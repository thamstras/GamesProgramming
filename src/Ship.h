#pragma once
#include "CommonIncludes.h"
#include "RenderObject.h"
#include "SwapSprite.h"
class Ship :
	public RenderObject
{
public:
	Ship(SDL_Renderer* ren, std::string id, int X, int Y, int type, int dir);
	~Ship();

	void update(double simLength);
	void render(SDL_Renderer* ren);

	bool hit(int X, int Y);
	bool destroyed;
private:
	int top, left, bottom, right, size, hits;
	SwapSprite* sprite;
};

