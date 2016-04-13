#include "GameGrid.h"

GameGrid::GameGrid(GridTypes gridType)
{
	type = gridType;
	
	gridData = new int[100];
	
	ships = new Ship*[6];

	switch (gridType)
	{
	case OUR_GRID:
		// TODO: Get our ships and draw them
		playerData = Scene::getScene().p1Data;
		break;
	case THEIR_GRID:
		// TODO: Get our shot history and disply it.
		playerData = Scene::getScene().p2Data;
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
	if (type == THEIR_GRID)
	{
		MouseData mouse = Scene::getScene().mouseData;
		if (mouse.leftMouseOnce)
		{
			int droneX = ourBall->sprite->getXPos();
			int droneY = ourBall->sprite->getYPos();
			int gridX = droneX / Scene::getScene().gridWidth;
			int gridY = droneY / Scene::getScene().gridHeight;
			int grid = gridY * 10 + gridX;
			Ship* ship;
			switch (gridData[grid])
			{
			case 0:	//Miss
				ship = nullptr;
				break;
			case 1: //Hit
				ship = ships[0];
				break;
			case 2:
				ship = ships[1];
				break;
			case 3:
				ship = ships[2];
				break;
			case 4:
				ship = ships[3];
				break;
			case 5:
				ship = ships[4];
				break;
			case 6:
				ship = ships[5];
				break;
			default: //Error
				break;
			}
			if (ship != nullptr)
			{
				if (ship->hit(gridX, gridY));
				{
					Scene::getScene().p1Data.shotData.addHit(gridX, gridY);
					// TODO: Scene::getScene().turnover();
					return;
				}
			}
			Scene::getScene().p1Data.shotData.addMiss(gridX, gridY);
		}
	}
}

void GameGrid::render(SDL_Renderer * ren)
{
}
