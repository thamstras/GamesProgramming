#include "TextSprite.h"

TextSprite::TextSprite(std::string font, int size, std::string string, SDL_Renderer* ren, std::string id) : RenderObject(id)
{
	this->_font = TTF_OpenFont(font.c_str(), size);
	if (_font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		//cleanExit(1);
	}
	this->_x = 10;
	this->_y = 10;
	this->_height = size;
	this->_width = size * string.length();
	this->_string = string;
	this->_colour = { 255, 255, 255 };
	SDL_Surface* surf = TTF_RenderText_Solid(_font, string.c_str(), _colour);
	this->_tex = SDL_CreateTextureFromSurface(ren, surf);
}

TextSprite::TextSprite(const TextSprite & other) : RenderObject(other)
{
	if (this != &other)
	{
		std::cout << "TextSprite(const TextSprite & other) called. THIS IS BAD!";
		this->_x = other._x;
		this->_y = other._y;
		this->_width = other._width;
		this->_height = other._height;
		this->_scale = other._scale;
		this->_string = other._string;
		this->_tex = other._tex;
		this->_font = other._font;
		this->_colour = other._colour;
	}
}

TextSprite::~TextSprite()
{
	std::cout << "Destroying " << id << std::endl;
	TTF_CloseFont(this->_font);
	SDL_DestroyTexture(this->_tex);
}

void TextSprite::update(double simLength)
{
	// Does Nothing
}

void TextSprite::render(SDL_Renderer* ren)
{
	SDL_Rect rect = { _x, _y, _width*_scale, _height*_scale };
	SDL_RenderCopy(ren, _tex, NULL, &rect);
}

void TextSprite::setString(std::string s, SDL_Renderer* ren)
{
	SDL_Surface* surf = TTF_RenderText_Solid(_font, s.c_str(), _colour);
	this->_tex = SDL_CreateTextureFromSurface(ren, surf);
}

void TextSprite::moveString(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

void TextSprite::setScale(float scale)
{
	this->_scale = scale;
}

SDL_Rect TextSprite::getBoundingBox()
{
	SDL_Rect rect = { _x, _y, _width*_scale, _height*_scale };
	return rect;
}
