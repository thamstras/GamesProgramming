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

	void swapGrid();

	void update(double simLength);
	void render(SDL_Renderer* ren);

private:
	PlayerData& playerData1;
	PlayerData& playerData2;

	GridTypes type;

	Ball* ourABall;
	Ball* ourDBall;
	Ball* theirABall;
	Ball* theirDBall;

	Ship** ships;
	std::vector<StaticSprite> shotSrpites;
	int* gridData;
};