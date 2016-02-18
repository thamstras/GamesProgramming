#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderObject.h"

class TextSprite : public RenderObject
{
public:
	TextSprite(std::string font, int size, std::string string, SDL_Renderer* ren);
	~TextSprite();
	void update(double simLength);
	void render(SDL_Renderer* ren);
	void setString(std::string s, SDL_Renderer* ren);
	void moveString(int x, int y);
	void setScale(float scale);

private:
	int _x;
	int _y;
	int _width;
	int _height;
	float _scale;
	std::string _string;
	SDL_Texture* _tex;
	TTF_Font* _font;
	SDL_Color _colour;
};

