#include "RemotePlayerAI.h"
#include "CommonIncludes.h"
#include "Scene.h"


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
	data = Scene::getScene().p1Data; // Cheekey copy the human
	return true;
}

void RemotePlayerAI::update()
{
	// TODO: AI goes here
	this->fire = true;
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
	return data;
}
