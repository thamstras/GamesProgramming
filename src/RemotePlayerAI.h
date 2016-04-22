#pragma once
#include "RemotePlayer.h"
class RemotePlayerAI :
	public RemotePlayer
{
public:
	RemotePlayerAI();
	~RemotePlayerAI();

	bool connect();
	bool getReady();
	void update();
	void sendState(float axis_x, float axis_y, bool fire);
	void sendGrid(PlayerData data);
	PlayerData getGrid();
};

