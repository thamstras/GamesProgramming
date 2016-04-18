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
	bool destroyed = false;
	bool d1 = false;
	bool d2 = false;
	bool d3 = false;
	bool d4 = false;
	bool d5 = false;

};

class ShotData
{
public:
	int* data;
	ShotData()
	{
		data = new int[100];
		for (int i = 0; i < 100; i++)
		{
			data[i] = 0;
		}
	}
	ShotData(const ShotData& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < 100; i++)
			{
				this->data[i] = other.data[i];
			}
		}
	}
	~ShotData()
	{
		delete[] data;
	}
	void addHit(int x, int y)
	{
		if (x > 10 || x < 0)
			return;
		if (y > 10 || y < 0)
			return;
		int n = y * 10 + x;
		data[n] = 2;
	}
	void addMiss(int x, int y)
	{
		if (x > 10 || x < 0)
			return;
		if (y > 10 || y < 0)
			return;
		int n = y * 10 + x;
		data[n] = 1;
	}
	int getState(int x, int y)
	{
		if (x > 10 || x < 0)
			return 0;
		if (y > 10 || y < 0)
			return 0;
		int n = y * 10 + x;
		return data[n];
	}
};

struct PlayerData
{
	ShipData* ships;
	ShotData shotData;
	PlayerData()
	{
		ships = new ShipData[6];
	}

	PlayerData(const PlayerData& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < 6; i++)
			{
				this->ships[i] = other.ships[i];
			}
		}
	}

	~PlayerData()
	{
		delete[] ships;
	}
};
