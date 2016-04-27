#include "Ship.h"

Ship::Ship(SDL_Renderer* ren, std::string id, int X, int Y, int type, int dir, int n, int p) : RenderObject(id)
{
	this->n = n;
	this->p = p;
	top = Y;
	left = X;
	destroyed = false;
	int length;
	std::string path;
	std::string path2;
	switch (type)
	{
	case 2:
		length = 2;
		path = "shipblueprint-2";
		path2 = "shipblueprint-2r";
		break;
	case 3:
		length = 3;
		path = "shipblueprint-3";
		path2 = "shipblueprint-3r";
		break;
	case 4:
		length = 4;
		path = "shipblueprint-4";
		path2 = "shipblueprint-4r";
		break;
	case 5:
		length = 5;
		path = "shipblueprint-5";
		path2 = "shipblueprint-5r";
		break;
	default:
		break;
	}
	size = length;
	hits = 0;
	sprite = new SwapSprite(path, path2, ren, this->id + "_sprite");
	if (dir == 0) 
	{
		bottom = Y;
		right = X + length;
	}
	else
	{
		sprite->swap(); 
		bottom = Y + length;
		right = X;
	}
	sprite->moveSprite(X*60, Y*60);
	Scene::getScene().registerRender(sprite);

	// TODO: Load Destruction

}


Ship::~Ship()
{
}

void Ship::update(double simLength)
{
}

void Ship::render(SDL_Renderer * ren)
{
}

void Ship::deltaShip(int deltaX, int deltaY)
{
	sprite->moveSprite(sprite->getX() + deltaX, sprite->getY() + deltaY);
	// TODO: This is a likely source of bugs.
}

bool Ship::hit(int X, int Y)
{
	if (X >= left && X <= right)
		if (Y >= top && Y <= bottom)
		{
			// TODO: Add Explosion
			// TODO: Add Destroyed section/smoke at hit

			//Update PlayerData
			int hitSection;
			PlayerData& pData = Scene::getScene().p1Data;
			switch (p)
			{
			case 1:
				pData = Scene::getScene().p1Data;
				break;
			case 2:
				pData = Scene::getScene().p2Data;
				break;
			default:
				pData = Scene::getScene().p1Data;
				break;
			}
			switch (hitSection)
			{
			case 1:
				//pData.ships[n].d1 = true;
				break;
			case 2:
				//pData.ships[n].d2 = true;
				break;
			case 3:
				//pData.ships[n].d3 = true;
				break;
			case 4:
				//pData.ships[n].d4 = true;
				break;
			case 5:
				//pData.ships[n].d5 = true;
				break;
			default:
				break;
			}
			hits++;
			if (hits = size)
			{
				// TODO: Destroyed!
				//pData.ships[n].destroyed = true;
				destroyed = true;
			}
			return true;
		}
	return false;
}
