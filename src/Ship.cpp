#include "Ship.h"

Ship::Ship(SDL_Renderer* ren, std::string id, int X, int Y, int type, int dir)
{
	this->id = id;
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
		path = ".\assets\shipblueprint-2.png";
		path2 = ".\assets\shipblueprint-2r.png";
		break;
	case 3:
		length = 3;
		path = ".\assets\shipblueprint-3.png";
		path2 = ".\assets\shipblueprint-3r.png";
		break;
	case 4:
		length = 4;
		path = ".\assets\shipblueprint-4.png";
		path2 = ".\assets\shipblueprint-4r.png";
		break;
	case 5:
		length = 5;
		path = ".\assets\shipblueprint-5.png";
		path2 = ".\assets\shipblueprint-5r.png";
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

bool Ship::hit(int X, int Y)
{
	if (X >= left && X <= right)
		if (Y >= top && Y <= bottom)
		{
			// TODO: Add Explosion
			// TODO: Add Destroyed section/smoke at hit
			hits++;
			if (hits = size)
			{
				// TODO: Destroyed!
				destroyed = true;
			}
			return true;
		}
	return false;
}
