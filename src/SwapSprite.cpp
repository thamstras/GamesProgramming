#include "SwapSprite.h"

SwapSprite::SwapSprite(std::string imagePath1, std::string imagePath2, SDL_Renderer * ren, std::string id)
{
	this->id = id;
	spriteA = new StaticSprite(imagePath1, ren, this->id + "_A");
	spriteB = new StaticSprite(imagePath2, ren, this->id + "_B");
}

SwapSprite::~SwapSprite()
{
	delete spriteA;
	delete spriteB;
}

void SwapSprite::swap()
{
	selectedSpriteA = !selectedSpriteA;
}

void SwapSprite::update(double simLength)
{
	spriteA->update(simLength);
	spriteB->update(simLength);
}

void SwapSprite::render(SDL_Renderer * ren)
{
	if (selectedSpriteA)
	{
		spriteA->render(ren);
	}
	else {
		spriteB->render(ren);
	}
}

void SwapSprite::moveSprite(int x, int y)
{
	spriteA->moveSprite(x, y);
	spriteB->moveSprite(x, y);
}

void SwapSprite::scaleSprite(float xScale, float yScale)
{
	spriteA->scaleSprite(xScale, yScale);
	spriteB->scaleSprite(xScale, yScale);
}
