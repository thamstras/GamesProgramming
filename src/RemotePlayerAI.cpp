#include "RemotePlayerAI.h"
#include "CommonIncludes.h"
#include "Scene.h"


RemotePlayerAI::RemotePlayerAI()
{
	playerX = 0;
	playerY = 0;
	ourX = 0;
	ourY = 0;
	turn = 0;
	lastshothit = false;

	targetX = 0;
	targetY = 0;
	shotX = 0;
	shotY = 0;
	mode = 0;
	oldMode = 0;
	shipDir = 0;
	lastTurn = 0;

	for (int i = 0; i < 100; i++)
		shotData[i] = 0;
}


RemotePlayerAI::~RemotePlayerAI()
{
}

bool RemotePlayerAI::connect()
{
	// TODO: AI Init here.
	return true; // AI not remote. Always connects.
}

bool RemotePlayerAI::getReady()
{
	// { size, x, y, dir }
	data = PlayerData();
	data.ships[0] = { 2, 1, 1, 1 };
	data.ships[1] = { 2, 3, 1, 0 };
	data.ships[2] = { 3, 1, 4, 0 };
	data.ships[3] = { 3, 1, 6, 0 };
	data.ships[4] = { 4, 7, 2, 1 };
	data.ships[5] = { 5, 2, 8, 0 };
	return true;
}

void RemotePlayerAI::update()
{
	// TODO: AI goes here
	this->fire = false;
	this->axis_X = 0.0f;
	this->axis_Y = 0.0f;
	doAI();
	//std::cout << "AI DEBUG: mode: " << mode << " turn: " << turn << " targetX: " << targetX << " targetY: " << targetY << " posX: " << ourX << " posY: " << ourY << std::endl;
}

void RemotePlayerAI::sendState(float axis_x, float axis_y, bool fire, bool hostTurn, bool lastShotHit)
{
	// AI not remote. Does nothing.
	if (hostTurn)
	{
		turn = 1;
	}
	else {
		turn = 0;
	}
	lastshothit = lastShotHit;
}

void RemotePlayerAI::sendGrid(PlayerData data)
{
	// AI not remote. Does nothing.
}

void RemotePlayerAI::sendPhys(float hostX, float hostY, float clientX, float clientY)
{
	playerX = (hostX + 15) / 60;
	playerY = (hostY + 15) / 60;

	ourX = (clientX + 15) / 60;
	ourY = (clientY + 15) / 60;
}

PlayerData RemotePlayerAI::getGrid()
{
	// TODO: 
	return data;
}

void RemotePlayerAI::newTarget()
{
	switch (mode)
	{
	case 0:
		for (int i = 1; i < 100; i += 2)
		{
			if (shotData[i] == 0)
			{
				targetY = i / 10;
				targetX = i % 10;
				break;
			}
		}
		break;
	case 1:
		switch (shipDir)
		{
		case 0:
		{
			int i = targetY * 10 + targetX;
			if (shotData[i + 1] == 2 || shotData[i - 1] == 2)
			{
				shipDir = 2;
				newTarget();
				break;
			}
			if (shotData[i + 10] == 2 || shotData[i - 10] == 2)
			{
				shipDir = 1;
				newTarget();
				break;
			}
			if (shotData[i + 1] == 0 && i <= 98)
			{
				targetY = (i + 1) / 10;
				targetX = (i + 1) % 10;
				break;
			}
			if (shotData[i - 1] == 0 && i >= 1)
			{
				targetY = (i - 1) / 10;
				targetX = (i % 1) % 10;
				break;
			}
			if (shotData[i + 10] == 0 && i <= 89)
			{
				targetY = (i + 10) / 10;
				targetX = (i + 10) % 10;
				break;
			}
			if (shotData[i - 10] == 0 && i >= 10)
			{
				targetY = (i - 10) / 10;
				targetX = (i % 10) / 10;
				break;
			}
			mode = 0; //We somehow have a single isolated hit surrounded by misses. Fallback.
			newTarget();
			break; 
		}
		case 1:
			break;
		case 2:
			break;
		}
		break;
	case 3:
		targetX = playerX;
		targetY = playerY;
		break;
	default:
		std::cout << "ERROR IN AI: INVALID MODE. UNDEFINED BEHAVIOUR WILL OCCUR" << std::endl;
		break;

	}
}

void RemotePlayerAI::doAI()
{
	if (turn != lastTurn)
	{
		if (turn == 0)
		{
			if (lastshothit)
			{
				shotData[shotY * 10 + shotX] = 2;
			}
			else {
				shotData[shotY * 10 + shotX] = 1;
			}
			mode = oldMode;
			newTarget();
		}
		if (turn == 1)
		{
			oldMode = mode;
			mode = 3;
			newTarget();
		}
	}
	lastTurn = turn;
	if (mode == 3)
	{
		newTarget();
	}
	else {
		if (ourX > targetX)
		{
			axis_X = -1.0f;
		}
		else {
			axis_X = 1.0f;
		}
		if (ourY > targetY)
		{
			axis_Y = -1.0f;
		}
		else {
			axis_Y = 1.0f;
		}
		if (ourX == targetX && ourY == targetY)
		{
			fire = true;
			shotX = targetX;
			shotY = targetY;
		}
		else {
			fire = false;
		}
	}
}
