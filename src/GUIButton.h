#pragma once

#include "CommonIncludes.h"
#include "RenderObject.h"
#include "StaticSprite.h"
#include "TextSprite.h"
#include "Scene.h"

class GUIButton : public RenderObject
{
public:
	GUIButton(SDL_Renderer* ren, std::string text, int x, int y, void callback(), std::string ID);
	~GUIButton();

	void update(double simLength);
	void render(SDL_Renderer* ren);
	void moveButton(int x, int y);
private:
	void (*onClick)();
	StaticSprite* sprite;
	TextSprite* text;
	int _x, _y, _width, _height;
};

