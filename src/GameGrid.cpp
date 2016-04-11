#include "GameGrid.h"

GameGrid::GameGrid(GridTypes gridType)
{
	switch (gridType)
	{
	case OUR_GRID:
		//Get our ships and draw them
		break;
	case THEIR_GRID:
		//Get our shot history and disply it.
		//If their grid doesn't exist make it.
		break;
	default:
		// PANIC
		break;
	}
}

GameGrid::~GameGrid()
{
}

void GameGrid::update(double simLength)
{
	//if (Their_Grid)
	//		if (player firing)
	//			convert player drone pos to grid coords
	//			send shot and get result
}

void GameGrid::render(SDL_Renderer * ren)
{
}
