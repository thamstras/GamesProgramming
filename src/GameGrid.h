#pragma once

#include "CommonIncludes.h"
#include "RenderObject.h"
#include "Scene.h"
#include "Ball.h"
#include "Ship.h"

enum GridTypes
{
	OUR_GRID, THEIR_GRID
};

class GameGrid : RenderObject
{
public:
	GameGrid(GridTypes gridType);
	~GameGrid();

	void update(double simLength);
	void render(SDL_Renderer* ren);

private:
	PlayerData playerData;
	GridTypes type;
	Ball* ourBall;
	Ball* theirBall;
	Ship** ships;

	int* gridData;
};