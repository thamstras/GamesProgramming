#include "StaticSprite.h"



StaticSprite::StaticSprite(std::string imagePath, SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		//cleanExit(1);
	}

	this->_w = surface->w;
	this->_h = surface->h;

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
	//TODO: NYI
}


StaticSprite::~StaticSprite()
{
	SDL_DestroyTexture(this->_tex);
}

void StaticSprite::render(SDL_Renderer* ren)
{
	SDL_Rect rect = { _x, _y, _w * _scaleX, _h*_scaleY };
	SDL_RenderCopy(ren, this->_tex, NULL, &rect);
}
