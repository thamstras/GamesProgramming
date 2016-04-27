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
			this->data = new int[100];
			for (int i = 0; i < 100; i++)
			{
				this->data[i] = other.data[i];
			}
		}
	}
	ShotData& operator=(const ShotData& rhs)
	{
		if (this != &rhs)
		{
			for (int i = 0; i < 100; i++)
			{
				this->data[i] = rhs.data[i];
			}
		}
		return *this;
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
	PlayerData()
	{
		ships = new ShipData[6];
		for (int i = 0; i < 6; i++)
		{
			ships[i] = { 0, 0, 0, 0 };
		}
	}

	PlayerData(const PlayerData& other)
	{
		ships = new ShipData[6];
		for (int i = 0; i < 6; i++)
		{
			ships[i] = { 0, 0, 0, 0 };
		}
		for (int i = 0; i < 6; i++)
		{
			this->ships[i] = other.ships[i];
		}
	}

	PlayerData& operator=(const PlayerData& rhs)
	{
		if (this != &rhs)
		{
			for (int i = 0; i < 6; i++)
			{
				this->ships[i] = rhs.ships[i];
			}
		}
		return *this;
	}

	~PlayerData()
	{
		delete[] ships;
	}
};
