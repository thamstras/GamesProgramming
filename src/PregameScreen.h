#pragma once

#include "CommonIncludes.h"

#include "RenderObject.h"
#include "AnimatedSprite.h"
#include "StaticSprite.h"
#include "TextSprite.h"
#include "Ball.h"
#include "Scene.h"
#include "GUIButton.h"
#include "SwapSprite.h"

class PregameScreen : public RenderObject
{
public:
	PregameScreen(SDL_Renderer* ren, std::string id);
	~PregameScreen();

	void update(double simLength);
	void render(SDL_Renderer* ren);

private:
	bool done;

	SwapSprite* getCurrentShip();
	int getCurrentShipSize();

	void showDoneButton();

	bool gridOpen(int X, int Y);
	void closeGrid(int X, int Y);
	bool fitsOnGrid(int X, int Y, int size, int direction);
	void placeOnGrid(int X, int Y, int size, int direction);

	StaticSprite* select;

	int gridWidth;
	int gridHeight;

	bool* grid;

	SwapSprite* ship1;
	SwapSprite* ship2;
	SwapSprite* ship3;
	SwapSprite* ship4;
	SwapSprite* ship5;
	SwapSprite* ship6;

	int currentShip;

	GUIButton* doneButton;
};

