#include "StaticSprite.h"

StaticSprite::StaticSprite(std::string imagePath, SDL_Renderer* ren, std::string id) : RenderObject(id)
{
	int * w = new int;
	int * h = new int;
	
	this->_tex = Scene::getScene().textures->getTexture(imagePath);
	SDL_QueryTexture(_tex, NULL, NULL, w, h);

	this->_srcRect = { 0, 0, *w, *h };

	_x = 10;
	_y = 10;

	_scaleX = 1.0f;
	_scaleY = 1.0f;

	delete w;
	delete h;
}

StaticSprite::StaticSprite(const StaticSprite & other) : RenderObject(other)
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
	std::cout << "Destroying " << id << std::endl;
	//SDL_DestroyTexture(this->_tex);
}

StaticSprite & StaticSprite::operator=(const StaticSprite & other)
{
	if (this != &other)
	{
		this->_x = other._x;
		this->_y = other._y;
		this->_scaleX = other._scaleX;
		this->_scaleY = other._scaleY;
		this->_srcRect = other._srcRect;
		this->_tex = other._tex;
	}
	return *this;
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