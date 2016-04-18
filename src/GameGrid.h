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

class GameGrid : public RenderObject
{
public:
	GameGrid(GridTypes gridType, SDL_Renderer * ren, std::string id);
	~GameGrid();

	void update(double simLength);
	void render(SDL_Renderer* ren);

private:
	PlayerData playerData;
	GridTypes type;
	Ball* ourBall;
	Ball* theirBall;
	Ship** ships;
	StaticSprite** shotSprites;
	int n_shots;
	int* gridData;
};