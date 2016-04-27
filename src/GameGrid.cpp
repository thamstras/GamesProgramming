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

GameGrid::GameGrid(GridTypes gridType, SDL_Renderer * ren, std::string id) : RenderObject(id)
{
	this->renderer = ren;
	// Setup Grid
	type = OUR_GRID;
	gridData = new int[100];
	ships = new Ship*[6];
	
	// Load Player Data
	playerData1 = Scene::getScene().p1Data;
	playerData2 = Scene::getScene().p2Data;

	p1Hits = 0;
	p2Hits = 0;

	p1ShotData = ShotData();
	p2ShotData = ShotData();

	// Draw Local Ships
	ShipData * shipsData = zSortShips(playerData1.ships);
	for (int s = 0; s < 6; s++)
	{
		std::string sid = this->id + "_ship" + std::to_string(s);
		ships[s] = new Ship(ren, sid, shipsData[s].x, shipsData[s].y, shipsData[s].size, shipsData[s].dir, s, 1);
	}

	// Prep Balls
	ourBall = new Ball(ren, glm::vec2(50, 50), glm::vec2(0, 0), 100, this->id + "_ourABall");
	ourBall->bindPlayer(1);

	theirBall = new Ball(ren, glm::vec2(50, 50), glm::vec2(0, 0), 100, this->id + "_thierABall");
	theirBall->bindPlayer(2);

	ourBall->move(550, 550); // Defending position
	theirBall->move(50, 50); // Attacking position

	// register all renders
	for (int s = 0; s < 6; s++)
	{
		Scene::getScene().registerRender(ships[s]);
	}
	Scene::getScene().registerRender(ourBall);
	Scene::getScene().registerRender(theirBall);

	// If HOST, Switch Grid.
	// IF CLIENT, dont.
	if (Scene::getScene().isServer)
		swapGrid();

}

GameGrid::~GameGrid()
{
}

void GameGrid::swapGrid()
{
	std::cout << "SwapGrid()" << std::endl;
	if (type == OUR_GRID)
	{
		type = THEIR_GRID;
		for (int i = 0; i < 6; i++)
		{
			ships[i]->deltaShip(-1000, 0);
		}
		for each (auto shot in shotSrpites)
		{
			shot->moveSprite(shot->getXPos() - 1000, shot->getYPos());
		}
		ourBall->move(550, 550);
		theirBall->move(50, 50);
	}
	else {
		type = OUR_GRID;
		for (int i = 0; i < 6; i++)
		{
			ships[i]->deltaShip(1000, 0);
		}
		for each (auto shot in shotSrpites)
		{
			shot->moveSprite(shot->getXPos() + 1000, shot->getYPos());
		}
		ourBall->move(50, 50);
		theirBall->move(550, 550);
	}
}

void GameGrid::update(double simLength)
{
	Scene::getScene().p1PosX = ourBall->phys->_position.x;
	Scene::getScene().p1PosY = ourBall->phys->_position.y;
	Scene::getScene().p2PosX = theirBall->phys->_position.x;
	Scene::getScene().p2PosY = theirBall->phys->_position.y;
	if (type == OUR_GRID)
		Scene::getScene().ourTurn = false;
	else
		Scene::getScene().ourTurn = true;
	if (type == OUR_GRID)
	{
		if (Scene::getScene().p2Fire)
		{
			int droneX = theirBall->sprite->getXPos();
			int droneY = theirBall->sprite->getYPos();
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
				std::cout << "P2 hit!" << std::endl;
				//ship->hit(gridX, gridY);
				if (p2ShotData.getState(gridX, gridY) != 0)
				{
					p2Hits++;
					p2ShotData.addHit(gridX, gridY);
				}
				Scene::getScene().lastShotHit = true;
				if (p2Hits >= maxHits)
				{
					Scene::getScene().loadScene(SCENE_P2_WIN);
				}
				StaticSprite* shot = new StaticSprite("hitshot", renderer, this->id + "_shot");
				shot->moveSprite(gridX * 60, gridY * 60);
				Scene::getScene().registerRender(shot);
				shotSrpites.push_back(shot);
			}
			else {
				p2ShotData.addMiss(gridX, gridY);
				std::cout << "P2 Missed!" << std::endl;
				Scene::getScene().lastShotHit = false;
				StaticSprite* shot = new StaticSprite("missshot", renderer, this->id + "_shot");
				shot->moveSprite(gridX * 60, gridY * 60);
				Scene::getScene().registerRender(shot);
				shotSrpites.push_back(shot);
			}
			swapGrid();

		}
	}
	else {
		if (Scene::getScene().p1Fire)
		{
			int droneX = ourBall->sprite->getXPos() + 30;
			int droneY = ourBall->sprite->getYPos() + 30;
			int gridX = droneX / Scene::getScene().gridWidth;
			int gridY = droneY / Scene::getScene().gridHeight;
			int grid = gridY * 10 + gridX;
			bool hit = false;
			buildGrid(false);
			if (gridData[grid] != 0) 
				hit = true; //wtf is this for?
			if (hit)
			{
				if (p1ShotData.getState(gridX, gridY) == 0)
				{
					p1Hits++;
					p1ShotData.addHit(gridX, gridY);
				}
				if (p1Hits >= maxHits)
				{
					Scene::getScene().loadScene(SCENE_P1_WIN);
				}
				std::cout << "P1 hit something!" << std::endl;
				StaticSprite* shot = new StaticSprite("hitshot", renderer, this->id + "_shot");
				shot->moveSprite(gridX * 60, gridY * 60);
				Scene::getScene().registerRender(shot);
				shotSrpites.push_back(shot);
				swapGrid();
				return;
			}
			else {
				p1ShotData.addMiss(gridX, gridY);
				std::cout << "P1 missed!" << std::endl;
				StaticSprite* shot = new StaticSprite("missshot", renderer, this->id + "_shot");
				shot->moveSprite(gridX * 60, gridY * 60);
				Scene::getScene().registerRender(shot);
				shotSrpites.push_back(shot);
				swapGrid();
				return;
			}
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
		placeOnGrid(shipData[s].x, shipData[s].y, shipData[s].size, shipData[s].dir, s+1);
	}
}
