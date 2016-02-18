#include "StaticSprite.h"

StaticSprite::StaticSprite(std::string imagePath, SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		//cleanExit(1);
	}

	int w = surface->w;
	int h = surface->h;

	this->_srcRect = { 0, 0, w, h };

	this->_tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (this->_tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		//cleanExit(1);
	}

	_x = 10;
	_y = 10;

	_scaleX = 1.0f;
	_scaleY = 1.0f;
}

StaticSprite::StaticSprite(const StaticSprite & other)
{
	this->_x = other._x;
	this->_y = other._y;
	this->_scaleX = other._scaleX;
	this->_scaleY = other._scaleY;
	this->_srcRect = other._srcRect;
	this->_tex = other._tex;
}


StaticSprite::~StaticSprite()
{
	SDL_DestroyTexture(this->_tex);
}

void StaticSprite::update(double simLength)
{
	// Does Nothing
}

void StaticSprite::render(SDL_Renderer* ren)
{
	SDL_Rect rect = { _x, _y, _srcRect.w * _scaleX, _srcRect.h*_scaleY };
	SDL_RenderCopy(ren, this->_tex, &_srcRect, &rect);
}

int StaticSprite::getXPos()
{
	return _x;
}

int StaticSprite::getYPos()
{
	return _y;
}

float StaticSprite::getXScale()
{
	return _scaleX;
}

float StaticSprite::getYScale()
{
	return _scaleY;
}

void StaticSprite::setSrcRect(SDL_Rect newSrc)
{
	this->_srcRect = newSrc;
}

void StaticSprite::moveSprite(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

void StaticSprite::scaleSprite(float xScale, float yScale)
{
	this->_scaleX = xScale;
	this->_scaleY = yScale;
}