#include "TextRenderer.h"

TextRenderer::TextRenderer(std::string font, int size, std::string string, SDL_Renderer* ren)
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

TextRenderer::~TextRenderer()
{
}

void TextRenderer::render(SDL_Renderer* ren)
{
	SDL_Rect rect = { _x, _y, _width*_scale, _height*_scale };
	SDL_RenderCopy(ren, _tex, NULL, &rect);
}

void TextRenderer::setString(std::string s, SDL_Renderer* ren)
{
	SDL_Surface* surf = TTF_RenderText_Solid(_font, s.c_str(), _colour);
	this->_tex = SDL_CreateTextureFromSurface(ren, surf);
}

void TextRenderer::moveString(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

void TextRenderer::setScale(float scale)
{
	this->_scale = scale;
}
