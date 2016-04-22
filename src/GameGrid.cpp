#include "GameGrid.h"
#include "glm\glm.hpp"

ShipData * zSortShips(ShipData * ships)
{
	ShipData * output = new ShipData[6];
	int i = 0;
	for (int x = 1; x <= 10; x++)
	{
		for (int s = 0; s < 6; s++)
		{
			if (ships[s].x == x)
			{
				output[i] = ships[s];
				i++;
			}
		}
	}
	return output;
}

GameGrid::GameGrid(GridTypes gridType, SDL_Renderer * ren, std::string id)
{
	// Setup Grid
	this->id = id;
	type = gridType;
	gridData = new int[100];
	ships = new Ship*[6];
	
	// Load Player Data
	playerData1 = Scene::getScene().p1Data;
	playerData2 = Scene::getScene().p2Data;

	// Draw Local Ships
	ShipData * shipsData = zSortShips(playerData1.ships);
	for (int s = 0; s < 6; s++)
	{
		std::string sid = this->id + "_ship" + std::to_string(s);
		ships[s] = new Ship(ren, sid, shipsData[s].x, shipsData[s].y, shipsData[s].size, shipsData[s].dir, s, 1);
	}

	// Prep Balls
	// TODO: 

	// register all renders

	// If HOST, no more to do.
	// IF CLIENT, Switch to THIER_GRID.

	// register all renders

}

GameGrid::~GameGrid()
{
}

void GameGrid::swapGrid()
{
	if (type = OUR_GRID)
	{
		type = THEIR_GRID;
		for (int i = 0; i < 6; i++)
		{
			// TODO: 
			//ships[i]->moveShip(ships[i]->getXPos() - 10, ships[i].getYPos());
		}
		for each (auto shot in shotSrpites)
		{
			shot.moveSprite(shot.getXPos() - 10, shot.getYPos);
		}
	}
	else {
		type = OUR_GRID;
		for (int i = 0; i < 6; i++)
		{
			// TODO:
			//ships[i]->moveShip(ships[i]->getXPos() + 10, ships[i].getYPos());
		}
		for each (auto shot in shotSrpites)
		{
			shot.moveSprite(shot.getXPos() + 10, shot.getYPos);
		}
	}
}

void GameGrid::update(double simLength)
{
	/* TODO: Redo
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
	*/
}

void GameGrid::render(SDL_Renderer * ren)
{
}
