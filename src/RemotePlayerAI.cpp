#include "RemotePlayerAI.h"



RemotePlayerAI::RemotePlayerAI()
{
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
	// TODO: Build Grid
	return false;
}

void RemotePlayerAI::update()
{
	// TODO: AI goes here
}

void RemotePlayerAI::sendState(float axis_x, float axis_y, bool fire)
{
	// AI not remote. Does nothing.
}

void RemotePlayerAI::sendGrid(PlayerData data)
{
	// AI not remote. Does nothing.
}

PlayerData RemotePlayerAI::getGrid()
{
	// TODO: 
	return PlayerData();
}
