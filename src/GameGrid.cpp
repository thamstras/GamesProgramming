#include "GameGrid.h"
#include "glm\glm.hpp"

// TODO: On THEIR turn ship data not stored correctly.
//       This means can't hit them.

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
	this->id = id;
	type = gridType;
	
	gridData = new int[100];
	
	ships = new Ship*[6];

	PlayerData& p1Data = Scene::getScene().p1Data;
	ShipData * shipsData = zSortShips(p1Data.ships);
	
	glm::vec2 ourPos;
	glm::vec2 theirPos;
	
	switch (gridType)
	{
	case OUR_GRID:
		for (int s = 0; s < 6; s++)
		{
			std::string sid = this->id + "_ship" + std::to_string(s);
			ships[s] = new Ship(ren, sid, shipsData[s].x, shipsData[s].y, shipsData[s].size, shipsData[s].dir, s, 1);
			Scene::getScene().registerRender(ships[s]);
		}
		ourPos = glm::vec2(10, 10);
		theirPos = glm::vec2(90, 90);

		break;
	case THEIR_GRID:
		for (int x = 1; x <= 10; x++)
		{
			for (int y = 1; y <= 10; y++)
			{
				if (p1Data.shotData.getState(x, y) != 0)
					n_shots++;
			}
		}
		shotSprites = new StaticSprite*[n_shots];
		for (int x = 1; x <= 10; x++)
		{
			for (int y = 1; y <= 10; y++)
			{
				switch (p1Data.shotData.getState(x, y))
				{
				case 0: //No Shot
					// TODO: Sprites
					break;
				case 1: //Miss
					break;
				case 2: //Hit
					break;
				default: //Error
					break;
				}
			}
		}
		ourPos = glm::vec2(90, 90);
		theirPos = glm::vec2(10, 10);
		break;
	default:
		// PANIC
		break;
	}

	ourBall = new Ball(ren, ourPos, glm::vec2(0, 0), 100.0f, this->id + "_ourBall");
	theirBall = new Ball(ren, theirPos, glm::vec2(0, 0), 100.0f, this->id + "_theirBall");
	ourBall->bindPlayer(1);
	theirBall->bindPlayer(2);

	Scene::getScene().registerRender(ourBall);
	Scene::getScene().registerRender(theirBall);


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
