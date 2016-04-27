#pragma once
#include "CommonIncludes.h"
#include "RenderObject.h"
#include "SwapSprite.h"
#include "Scene.h"
class Ship :
	public RenderObject
{
public:
	Ship(SDL_Renderer* ren, std::string id, int X, int Y, int type, int dir, int n, int p);
	~Ship();

	void update(double simLength);
	void render(SDL_Renderer* ren);

	void deltaShip(int deltaX, int deltaY);

	bool hit(int X, int Y);
	bool destroyed;
private:
	int top, left, bottom, right, size, hits, n, p;
	SwapSprite* sprite;
};

