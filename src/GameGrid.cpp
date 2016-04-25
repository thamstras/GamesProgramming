#include "GameGrid.h"
#include "glm\glm.hpp"

ShipData * zSortShips(ShipData * ships)
{
	ShipData * output = new ShipData[6];
	int i = 0;
	for (int x = 0; x < 10; x++)
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
	this->renderer = ren;
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
	ourABall = new Ball(ren, glm::vec2(650, 50), glm::vec2(0, 0), 100, this->id + "_ourABall");
	ourABall->bindPlayer(1);
	ourDBall = new Ball(ren, glm::vec2(50, 50), glm::vec2(0, 0), 100, this->id + "_ourDBall");
	ourDBall->bindPlayer(1);

	theirABall = new Ball(ren, glm::vec2(50, 50), glm::vec2(0, 0), 100, this->id + "_thierABall");
	theirABall->bindPlayer(2);
	theirDBall = new Ball(ren, glm::vec2(650, 50), glm::vec2(0, 0), 100, this->id + "_theirDBall");
	theirDBall->bindPlayer(2);

	// register all renders
	for (int s = 0; s < 6; s++)
	{
		Scene::getScene().registerRender(ships[s]);
	}
	Scene::getScene().registerRender(ourABall);
	Scene::getScene().registerRender(ourDBall);
	Scene::getScene().registerRender(theirABall);
	Scene::getScene().registerRender(theirDBall);

	// If HOST, no more to do.
	// IF CLIENT, Switch to THIER_GRID.
	if (!(Scene::getScene().isServer))
		swapGrid();

}

GameGrid::~GameGrid()
{
}

void GameGrid::swapGrid()
{
	if (type == OUR_GRID)
	{
		type = THEIR_GRID;
		for (int i = 0; i < 6; i++)
		{
			// TODO: 
			//ships[i]->moveShip(ships[i]->getXPos() - 600, ships[i].getYPos());
		}
		for each (auto shot in shotSrpites)
		{
			shot->moveSprite(shot->getXPos() - 600, shot->getYPos());
		}
		ourDBall->disable();
		ourDBall->moveDelta(-600, 0);
		theirABall->disable();
		theirABall->moveDelta(-600, 0);
		ourABall->enable();
		ourABall->moveDelta(-600, 0);
		theirDBall->enable();
		theirDBall->moveDelta(-600, 0);
	}
	else {
		type = OUR_GRID;
		for (int i = 0; i < 6; i++)
		{
			// TODO:
			//ships[i]->moveShip(ships[i]->getXPos() + 600, ships[i].getYPos());
		}
		for each (auto shot in shotSrpites)
		{
			shot->moveSprite(shot->getXPos() + 600, shot->getYPos());
		}
		ourDBall->enable();
		ourDBall->moveDelta(600, 0);
		theirABall->enable();
		theirABall->moveDelta(600, 0);
		ourABall->disable();
		ourABall->moveDelta(600, 0);
		theirDBall->disable();
		theirDBall->moveDelta(600, 0);
	}
}

void GameGrid::update(double simLength)
{
	if (type == OUR_GRID)
	{
		if (Scene::getScene().p2Fire)
		{
			int droneX = theirABall->sprite->getXPos();
			int droneY = theirABall->sprite->getYPos();
			int gridX = droneX / Scene::getScene().gridWidth;
			int gridY = droneY / Scene::getScene().gridHeight;
			int grid = gridY * 10 + gridX;
			buildGrid(true);
			bool hit = false;
			Ship* ship;
			switch (gridData[grid])
			{
			case 0:	//Miss
				ship = nullptr;
				break;
			case 1: //Hit
				ship = ships[0];
				hit = true;
				break;
			case 2:
				ship = ships[1];
				hit = true;
				break;
			case 3:
				ship = ships[2];
				hit = true;
				break;
			case 4:
				ship = ships[3];
				hit = true;
				break;
			case 5:
				ship = ships[4];
				hit = true;
				break;
			case 6:
				ship = ships[5];
				hit = true;
				break;
			default: //Error
				break;
			}
			if (hit)
			{
				ship->hit(gridX, gridY);
			}
			swapGrid();

		}
	}
	else {
		if (Scene::getScene().p1Fire)
		{
			// TODO: P2 Hit Handling
			///*
			int droneX = theirABall->sprite->getXPos();
			int droneY = theirABall->sprite->getYPos();
			int gridX = droneX / Scene::getScene().gridWidth;
			int gridY = droneY / Scene::getScene().gridHeight;
			int grid = gridY * 10 + gridX;
			bool hit = false;
			buildGrid(false);
			if (gridData[grid] != 0)
				hit = true;
			if (hit)
			{
				Scene::getScene().p1Data.shotData.addHit(gridX, gridY);
				StaticSprite* shot = new StaticSprite("hitshot", renderer, this->id + "_shot");
				shot->moveSprite(gridX * 60, gridY * 60);
				shotSrpites.push_back(shot);
				swapGrid();
				return;
			}
			else {
				Scene::getScene().p1Data.shotData.addMiss(gridX, gridY);
				StaticSprite* shot = new StaticSprite("missshot", renderer, this->id + "_shot");
				shot->moveSprite(gridX * 60, gridY * 60);
				shotSrpites.push_back(shot);
				swapGrid();
				return;
			}
			//*/
		}
	}
}

void GameGrid::render(SDL_Renderer * ren)
{
}

void GameGrid::closeGrid(int X, int Y, int s)
{
	if (X > 9 || Y > 9)
		return;
	if (X < 0 || Y < 0)
		return;
	int i = (Y * 10) + X;
	gridData[i] = s;
}

void GameGrid::placeOnGrid(int X, int Y, int size, int direction, int s)
{
	if (direction == 0)
	{
		for (int i = 0; i < size; i++)
		{
			closeGrid(X + i, Y, s);
		}
	}
	else {
		for (int i = 0; i < size; i++)
		{
			closeGrid(X, Y + i, s);
		}
	}
}

void GameGrid::buildGrid(bool local)
{
	for (int i = 0; i < 100; i++)
	{
		gridData[i] = 0;
	}
	PlayerData data;
	if (local)
		data = playerData1;
	else
		data = playerData2;
	ShipData* shipData = data.ships;
	for (int s = 0; s < 6; s++)
	{
		placeOnGrid(shipData[s].x, shipData[s].y, shipData[s].size, shipData[s].dir, s);
	}
}
