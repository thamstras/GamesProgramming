#pragma once
#include "Structs.h"
class RemotePlayer
{
public:
	RemotePlayer();
	virtual ~RemotePlayer();

	virtual bool connect() = 0;
	virtual bool getReady() = 0;
	virtual void update() = 0;
	virtual void sendState(float axis_x, float axis_y, bool fire) = 0;
	virtual void sendGrid(PlayerData data) = 0;
	virtual PlayerData getGrid() = 0;

	float axis_X;
	float axis_Y;
	bool fire;
	
};

