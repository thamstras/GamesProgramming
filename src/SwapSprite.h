#pragma once
#include "CommonIncludes.h"
#include "RenderObject.h"
#include "StaticSprite.h"

class SwapSprite : public RenderObject
{
public:
	bool selectedSpriteA = true;

	SwapSprite(std::string imagePath1, std::string imagePath2, SDL_Renderer* ren, std::string id);
	~SwapSprite();

	void swap();

	void update(double simLength);
	void render(SDL_Renderer* ren);

	void moveSprite(int x, int y);
	void scaleSprite(float xScale, float yScale);

	int getX();
	int getY();
private:
	StaticSprite* spriteA;
	StaticSprite* spriteB;
};

