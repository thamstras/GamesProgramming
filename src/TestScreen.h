#pragma once

#include "CommonIncludes.h"

#include "RenderObject.h"
#include "AnimatedSprite.h"
#include "StaticSprite.h"
#include "TextSprite.h"
#include "Ball.h"
#include "Scene.h"
#include "GUIButton.h"

class TestScreen : public RenderObject
{
public:
	TestScreen(SDL_Renderer* ren, std::string id);
	~TestScreen();

	void update(double simLength);
	void render(SDL_Renderer* ren);

	StaticSprite* logo;
	AnimatedSprite* man;
	TextSprite* text;
	Ball* ball;
	GUIButton* button;

private:

};