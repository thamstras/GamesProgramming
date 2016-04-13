#pragma once

struct WorldBounds
{
	float minX;
	float minY;
	float maxX;
	float maxY;
};

struct MouseData
{
	float mouseX;
	float mouseY;
	bool leftMouse;
	bool rightMouse;
	bool leftMouseOnce;
	bool rightMouseOnce;
};

struct ShipData
{
	int size;
	int x;
	int y;
	int dir;
};

struct PlayerData
{
	ShipData ships[6];
};
